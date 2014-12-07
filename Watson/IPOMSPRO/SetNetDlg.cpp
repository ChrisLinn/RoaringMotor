// SetNetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPOMSPRO.h"
#include "SetNetDlg.h"
#include "afxdialogex.h"


// CSetNetDlg dialog

IMPLEMENT_DYNAMIC(CSetNetDlg, CDialog)

CSetNetDlg::CSetNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetNetDlg::IDD, pParent)
{

	m_PortNumDS = 8080;
	m_PortNumLC = 8080;


}

CSetNetDlg::~CSetNetDlg()
{


}



void CSetNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORTNUMDS, m_PortNumDS);
	DDV_MinMaxUInt(pDX, m_PortNumDS, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PORTNUMLC, m_PortNumLC);
	DDV_MinMaxUInt(pDX, m_PortNumLC, 0, 65535);
	DDX_Control(pDX, IDC_IPADDRESS1, m_CIPAddress);
}


BEGIN_MESSAGE_MAP(CSetNetDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSetNetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetNetDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSetNetDlg message handlers


void CSetNetDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);	

	m_CIPAddress.GetAddress(dwIP);
//	dwIP=3232236026;						//设置默认的IP地址 192.168.1.250

	CDialog::OnOK();
}


void CSetNetDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
		m_CIPAddress.SetAddress(192,168,1,250);

}
