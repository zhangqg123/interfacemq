// SetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Interface3D.h"
#include "SetDlg.h"
#include "afxdialogex.h"


// CSetDlg �Ի���

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


// CSetDlg ��Ϣ�������


void CSetDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}
