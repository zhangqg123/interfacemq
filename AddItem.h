#pragma once
#include "Interface3DDlg.h"

// CAddItem 对话框

class CAddItem : public CDialogEx
{
	DECLARE_DYNAMIC(CAddItem)

public:
	CAddItem(CWnd* pParent = NULL)
	{}// 标准构造函数
	CAddItem(CInterface3DDlg * cdlg,CWnd* pParent = NULL);

	virtual ~CAddItem();

// 对话框数据
	enum { IDD = IDD_DLG_AddITEM };
public:
	CInterface3DDlg *m_pdlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
