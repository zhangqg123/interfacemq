#include "StdAfx.h"
#include "LogFile.h"
#include "locale.h"
#include <shlwapi.h>


UINT  AFX_CDECL WriteLogThread(LPVOID lParam);
CLogFile::CLogFile(void)
{
	//�����߳�
	m_IsRun = TRUE;
	m_hThread = NULL;

	//���·��
	TCHAR  path[MAX_PATH];
	::GetModuleFileName(NULL,path,MAX_PATH);
	m_LogPath.Format(_T("%s"),path);
	int nPos = m_LogPath.ReverseFind('\\');
	m_LogPath = m_LogPath.Mid(0,nPos);
	m_LogPath = m_LogPath + _T("\\Log");

	//���LogĿ¼�����ڣ��򴴽�
    if(!PathFileExists(m_LogPath))
	{
       CreateDirectory(m_LogPath,NULL);
	}
}

CLogFile::~CLogFile(void)
{
	Stop();
}

//����
BOOL CLogFile::Run()
{
    m_IsRun = TRUE;
    //�����߳�
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
		//�����߳�
		m_IsRun = FALSE;
		if(::WaitForSingleObject(m_hThread,INFINITE) == WAIT_OBJECT_0)
		{
			m_hThread->ResumeThread();
		}
	}
    return TRUE;
}

//д��־���̺߳���
UINT  AFX_CDECL WriteLogThread(LPVOID lParam)
{
	//��������
    CLogFile * pFile = (CLogFile *)lParam;
    CStdioFile logFile;
	CString strTime;
    
	while(pFile->m_IsRun)
	{
		Sleep(RUN_SPLIT_TIME*1000);

		//�����ļ�
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

		//�����־��¼��ʱ��
        strTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		if(!pFile->m_bFlagAmq)
		{
			strTime = strTime +  _T("------link remote error\r\n") ;
			logFile.WriteString(strTime);
		}
		
/*		if(pFile->m_bFlagSend)
		{
			char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
			setlocale( LC_CTYPE, "chs");//�趨
			logFile.WriteString(pFile->m_csLog);
			pFile->m_bFlagSend = FALSE;
			setlocale( LC_CTYPE, old_locale );
			free( old_locale );//��ԭ�����趨 
			
		}
*/
		if(pFile->m_errorLog)
		{
			char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
			setlocale( LC_CTYPE, "chs");//�趨
			logFile.WriteString(pFile->m_csLog);
			pFile->m_errorLog = FALSE;
			setlocale( LC_CTYPE, old_locale );
			free( old_locale );//��ԭ�����趨 
			
		}
		
		//�ر��ļ�
		logFile.Close();
	}
	return 0;
}