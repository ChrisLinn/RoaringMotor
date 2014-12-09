// IPOMSPRODlg.h : header file
//

#if !defined(AFX_IPOMSPRODLG_H__1881F7E5_E506_4BE6_A547_D258B2D94B54__INCLUDED_)
#define AFX_IPOMSPRODLG_H__1881F7E5_E506_4BE6_A547_D258B2D94B54__INCLUDED_

#if _MSC_VER > 1000
#pragma once


#define UM_SOCK		WM_USER+1
#define	WM_RECVDATA		WM_USER+2






#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIPOMSPRODlg dialog
#include "Scope.h"
#include"mscomm.h"
#include"SetupDlg.h"
#include"SetNetDlg.h"

//新线程参数传递结构体
struct RECVPARAM
{
	SOCKET sock;
	HWND hwnd;
};

class CIPOMSPRODlg : public CDialog
{
// Construction
public:
	CIPOMSPRODlg(CWnd* pParent = NULL);	// standard constructor
	~CIPOMSPRODlg();
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
	static DWORD WINAPI SaveProc(LPVOID lpParameter);

// Dialog Data
	//{{AFX_DATA(CIPOMSPRODlg)
	enum { IDD = IDD_IPOMSPRO_DIALOG };
	CButton	m_RightStart;
	CButton	m_LeftStart;
	CProgressCtrl	m_progress;
	CListCtrl	m_List;
	CButton	m_button1;
	CScope	m_wndScope;
	int		m_Q1;
	//}}AFX_DATA
	CMSComm myComm;
	SetupDlg mySetupDlg;
	CSetNetDlg mySetNetDlg;
	BYTE myCom;
	CString myBaudRate;
	CString myParity;
	void SendData(CString strInput);			//发送数据函数
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPOMSPRODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPOMSPRODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnLeftstart();
	afx_msg void OnRightstart();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnSetupcom();
	afx_msg void OnExit();
	afx_msg void OnSaveToTxT();
	afx_msg LRESULT OnSock(WPARAM,LPARAM);
	afx_msg LRESULT OnRecvData(WPARAM wParam,LPARAM lParam);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetnet();
private:
	SOCKET m_socket;
public:
	unsigned int m_PortNumber;
	unsigned int m_TargetPortNumber;
	bool m_NetFlag;
	bool m_ComFlag;
	SOCKADDR_IN addrTo;
	// 初始化设置Socket
	bool InitSocket(void);
	CString DataNetBuffer_CString;
	afx_msg void OnBnClickedButimedown();
	afx_msg void OnBnClickedButimeup();
	afx_msg void OnBnClickedButimeleft();
	afx_msg void OnBnClickedBzutimeright();
	afx_msg void OnBnClickedButmovleft();
	afx_msg void OnBnClickedButmovright();
	afx_msg void OnBnClickedScoperest();
	// 重新载入需要显示的数据
	void ReLoadData(void);
	CBitmap BMUPC;
	CStatic m_PictureUPC;
	afx_msg void OnBnClickedButtonturnon();
	afx_msg void OnBnClickedButtonturnoff();
	afx_msg void OnBnClickedDiy();
	afx_msg void OnDestroy();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPOMSPRODLG_H__1881F7E5_E506_4BE6_A547_D258B2D94B54__INCLUDED_)
