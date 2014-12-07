// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPOMSPRO.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetupDlg dialog


SetupDlg::SetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetupDlg)
	m_BaudRate = 3;
	m_Com = 1;
	m_Parity = 0;
	//}}AFX_DATA_INIT
}


void SetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetupDlg)
	DDX_CBIndex(pDX, IDC_COMBO_B, m_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_COM, m_Com);
	DDX_CBIndex(pDX, IIDC_COMBO_P, m_Parity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetupDlg, CDialog)
	//{{AFX_MSG_MAP(SetupDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetupDlg message handlers
