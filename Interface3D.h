
// Interface3D.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CInterface3DApp:
// �йش����ʵ�֣������ Interface3D.cpp
//

class CInterface3DApp : public CWinApp
{
public:
	CInterface3DApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CInterface3DApp theApp;