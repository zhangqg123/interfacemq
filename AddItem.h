#pragma once
#include "Interface3DDlg.h"

// CAddItem �Ի���

class CAddItem : public CDialogEx
{
	DECLARE_DYNAMIC(CAddItem)

public:
	CAddItem(CWnd* pParent = NULL)
	{}// ��׼���캯��
	CAddItem(CInterface3DDlg * cdlg,CWnd* pParent = NULL);

	virtual ~CAddItem();

// �Ի�������
	enum { IDD = IDD_DLG_AddITEM };
public:
	CInterface3DDlg *m_pdlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
