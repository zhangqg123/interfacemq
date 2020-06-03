// AddItem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Interface3D.h"
#include "AddItem.h"
#include "afxdialogex.h"


// CAddItem �Ի���

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


// CAddItem ��Ϣ�������


void CAddItem::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString csItem;
	GetDlgItem(IDC_EDT_ITEM)->GetWindowText(csItem);
	if (csItem != "")
	{
		m_pdlg->m_csItem = csItem;
		CDialog::OnOK();
	}
}
