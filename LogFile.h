#pragma once

#ifndef _LOG_FILE_
#define _LOG_FILE

#include <afxcoll.h>
#include <process.h>
#include <afxmt.h>

//�̶߳೤�¼�дһ����־,��λ����
#define RUN_SPLIT_TIME   3
//
//��־��¼��
//���ߣ�����(shenyi0106@163.com)
//ʱ�䣺2010/4/21
//
class CLogFile
{
public:
	CLogFile(void);
	~CLogFile(void);

	BOOL m_bFlagAmq;
	BOOL m_bFlagSend;
	BOOL m_errorLog;
public:
	//����
	BOOL Run();
	//ֹͣ
	BOOL Stop();
public:
	CWinThread  *m_hThread;
	//�����߳�
	BOOL m_IsRun;
	//LogĿ¼·��
	CString m_LogPath;
	CString m_csLog;
};
#endif
