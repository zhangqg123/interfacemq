// AddItem.cpp : 实现文件
//

#include "stdafx.h"
#include "Interface3D.h"
#include "AddItem.h"
#include "afxdialogex.h"


// CAddItem 对话框

IMPLEMENT_DYNAMIC(CAddItem, CDialogEx)

CAddItem::CAddItem(CInterface3DDlg * cdlg,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddItem::IDD, pParent)
{
	m_pdlg = cdlg;
}

CAddItem::~CAddItem()
{
}

void CAddItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddItem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddItem::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAddItem 消息处理程序


void CAddItem::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csItem;
	GetDlgItem(IDC_EDT_ITEM)->GetWindowText(csItem);
	if (csItem != "")
	{
		m_pdlg->m_csItem = csItem;
		CDialog::OnOK();
	}
}
