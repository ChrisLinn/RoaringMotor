// IPOMSPRO.h : main header file for the IPOMSPRO application
//

#if !defined(AFX_IPOMSPRO_H__D1DC2490_BF33_4925_B2AE_0079CF687CED__INCLUDED_)
#define AFX_IPOMSPRO_H__D1DC2490_BF33_4925_B2AE_0079CF687CED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPOMSPROApp:
// See IPOMSPRO.cpp for the implementation of this class
//

class CIPOMSPROApp : public CWinApp
{
public:
	CIPOMSPROApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPOMSPROApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPOMSPROApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPOMSPRO_H__D1DC2490_BF33_4925_B2AE_0079CF687CED__INCLUDED_)
