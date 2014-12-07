#pragma once


// CSetNetDlg dialog

class CSetNetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetNetDlg)

public:
	CSetNetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetNetDlg();

// Dialog Data
	enum { IDD = IDD_DL_SETNET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT m_PortNumDS;
	UINT m_PortNumLC;
	CIPAddressCtrl m_CIPAddress;
	DWORD dwIP;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
