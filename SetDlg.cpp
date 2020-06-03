// SetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Interface3D.h"
#include "SetDlg.h"
#include "afxdialogex.h"


// CSetDlg 对话框

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDlg::IDD, pParent)
	, m_csIP(_T(""))
	, m_csPort(_T(""))
	, m_nTime(0)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_csIP);
	DDX_Text(pDX, IDC_EDIT2, m_csPort);
	DDX_Text(pDX, IDC_EDIT3, m_nTime);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetDlg 消息处理程序


void CSetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialogEx::OnOK();
}
