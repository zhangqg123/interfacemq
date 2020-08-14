#include "StdAfx.h"
#include "LogFile.h"
#include "locale.h"
#include <shlwapi.h>


UINT  AFX_CDECL WriteLogThread(LPVOID lParam);
CLogFile::CLogFile(void)
{
	//控制线程
	m_IsRun = TRUE;
	m_hThread = NULL;

	//获得路径
	TCHAR  path[MAX_PATH];
	::GetModuleFileName(NULL,path,MAX_PATH);
	m_LogPath.Format(_T("%s"),path);
	int nPos = m_LogPath.ReverseFind('\\');
	m_LogPath = m_LogPath.Mid(0,nPos);
	m_LogPath = m_LogPath + _T("\\Log");

	//如果Log目录不存在，则创建
    if(!PathFileExists(m_LogPath))
	{
       CreateDirectory(m_LogPath,NULL);
	}
}

CLogFile::~CLogFile(void)
{
	Stop();
}

//启动
BOOL CLogFile::Run()
{
    m_IsRun = TRUE;
    //启动线程
	m_hThread = AfxBeginThread(WriteLogThread,(LPVOID)this);
	if(m_hThread == NULL)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CLogFile::Stop()
{
	if(m_IsRun)
	{
		//控制线程
		m_IsRun = FALSE;
		if(::WaitForSingleObject(m_hThread,INFINITE) == WAIT_OBJECT_0)
		{
			m_hThread->ResumeThread();
		}
	}
    return TRUE;
}

//写日志的线程函数
UINT  AFX_CDECL WriteLogThread(LPVOID lParam)
{
	//获得类对象
    CLogFile * pFile = (CLogFile *)lParam;
    CStdioFile logFile;
	CString strTime;
    
	while(pFile->m_IsRun)
	{
		Sleep(RUN_SPLIT_TIME*1000);

		//创建文件
		strTime = CTime::GetCurrentTime().Format(_T("%Y-%m-%d"));
		strTime = pFile->m_LogPath + _T("\\") + strTime + _T(".log");
        try
		{
			if(logFile.Open(strTime,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
			{
				logFile.SeekToEnd();
			}
		}
		catch(CFileException *e)
		{
			
		}

		//获得日志记录的时间
        strTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		if(!pFile->m_bFlagAmq)
		{
			strTime = strTime +  _T("------link remote error\r\n") ;
			logFile.WriteString(strTime);
		}
		
/*		if(pFile->m_bFlagSend)
		{
			char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
			setlocale( LC_CTYPE, "chs");//设定
			logFile.WriteString(pFile->m_csLog);
			pFile->m_bFlagSend = FALSE;
			setlocale( LC_CTYPE, old_locale );
			free( old_locale );//还原区域设定 
			
		}
*/
		if(pFile->m_errorLog)
		{
			char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
			setlocale( LC_CTYPE, "chs");//设定
			logFile.WriteString(pFile->m_csLog);
			pFile->m_errorLog = FALSE;
			setlocale( LC_CTYPE, old_locale );
			free( old_locale );//还原区域设定 
			
		}
		
		//关闭文件
		logFile.Close();
	}
	return 0;
}