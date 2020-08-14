#pragma once

#ifndef _LOG_FILE_
#define _LOG_FILE

#include <afxcoll.h>
#include <process.h>
#include <afxmt.h>

//线程多长事件写一次日志,单位是秒
#define RUN_SPLIT_TIME   3
//
//日志记录类
//作者：沈毅(shenyi0106@163.com)
//时间：2010/4/21
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
	//启动
	BOOL Run();
	//停止
	BOOL Stop();
public:
	CWinThread  *m_hThread;
	//控制线程
	BOOL m_IsRun;
	//Log目录路径
	CString m_LogPath;
	CString m_csLog;
};
#endif
