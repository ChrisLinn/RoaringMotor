#if !defined(AFX_SETUPDLG_H__F556D090_2B1E_43F0_8E23_74E25A56A581__INCLUDED_)
#define AFX_SETUPDLG_H__F556D090_2B1E_43F0_8E23_74E25A56A581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetupDlg dialog

class SetupDlg : public CDialog
{
// Construction
public:
	SetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetupDlg)
	enum { IDD = IDD_DIALOG1 };
	int		m_BaudRate;
	int		m_Com;
	int		m_Parity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetupDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__F556D090_2B1E_43F0_8E23_74E25A56A581__INCLUDED_)
