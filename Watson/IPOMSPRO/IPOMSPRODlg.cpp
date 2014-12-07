// IPOMSPRODlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPOMSPRO.h"
#include "IPOMSPRODlg.h"
#include "mmsystem.h"
#include <math.h>
#include "Scope.h"
#include "Variable.h"
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPOMSPRODlg dialog

CIPOMSPRODlg::CIPOMSPRODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPOMSPRODlg::IDD, pParent)

{
	//{{AFX_DATA_INIT(CIPOMSPRODlg)
	m_Q1 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_PortNumber = 0;
	m_TargetPortNumber = 0;
	m_NetFlag=FALSE;
	m_ComFlag=FALSE;
	DebugDataAllow=FALSE;
	DataNetBuffer_CString = _T("");
}
CIPOMSPRODlg::~CIPOMSPRODlg()
{
	if(m_socket)
		closesocket(m_socket);
}


void CIPOMSPRODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPOMSPRODlg)
	DDX_Control(pDX, IDC_RIGHTSTART, m_RightStart);
	DDX_Control(pDX, IDC_LEFTSTART, m_LeftStart);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_SCOPE, m_wndScope);
	DDX_Text(pDX, IDC_EDIT2, m_Q1);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_STATICUPC, m_PictureUPC);
}

BEGIN_MESSAGE_MAP(CIPOMSPRODlg, CDialog)
	//{{AFX_MSG_MAP(CIPOMSPRODlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_LEFTSTART, OnLeftstart)
	ON_BN_CLICKED(IDC_RIGHTSTART, OnRightstart)
	ON_BN_CLICKED(IDC_SETUPCOM, OnSetupcom)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_BUTTON1, OnSaveToTxT)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SETNET, &CIPOMSPRODlg::OnBnClickedSetnet)
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
	ON_MESSAGE(UM_SOCK,OnSock)
	ON_BN_CLICKED(IDC_BUTIMEDOWN, &CIPOMSPRODlg::OnBnClickedButimedown)
	ON_BN_CLICKED(IDC_BUTIMEUP, &CIPOMSPRODlg::OnBnClickedButimeup)
	ON_BN_CLICKED(IDC_BUTIMELEFT, &CIPOMSPRODlg::OnBnClickedButimeleft)
	ON_BN_CLICKED(IDC_BZUTIMERIGHT, &CIPOMSPRODlg::OnBnClickedBzutimeright)
	ON_BN_CLICKED(IDC_BUTMOVLEFT, &CIPOMSPRODlg::OnBnClickedButmovleft)
	ON_BN_CLICKED(IDC_BUTMOVRIGHT, &CIPOMSPRODlg::OnBnClickedButmovright)
	ON_BN_CLICKED(IDC_SCOPEREST, &CIPOMSPRODlg::OnBnClickedScoperest)
	ON_BN_CLICKED(IDC_BUTTONTURNON, &CIPOMSPRODlg::OnBnClickedButtonturnon)
	ON_BN_CLICKED(IDC_BUTTONTURNOFF, &CIPOMSPRODlg::OnBnClickedButtonturnoff)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPOMSPRODlg message handlers

BOOL CIPOMSPRODlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CFont * f; 
	f = new CFont; 
	f->CreateFont(40, // nHeight 
	20, // nWidth 
	0, // nEscapement 
	0, // nOrientation 
	FW_BOLD, // nWeight 
	FALSE, // bItalic 
	FALSE, // bUnderline 
	0, // cStrikeOut 
	ANSI_CHARSET, // nCharSet 
	OUT_DEFAULT_PRECIS, // nOutPrecision 
	CLIP_DEFAULT_PRECIS, // nClipPrecision 
	DEFAULT_QUALITY, // nQuality 
	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
	_T("Arial")); // lpszFac 
	GetDlgItem(IDC_MAINTITLE)->SetFont(f); //设置大标题字体
	
	CFont * af; 
	af = new CFont;
	af->CreateFont(16, // nHeight 
	8, // nWidth 
	0, // nEscapement 
	0, // nOrientation 
	FW_BOLD, // nWeight 
	TRUE, // bItalic 
	FALSE, // bUnderline 
	0, // cStrikeOut 
	ANSI_CHARSET, // nCharSet 
	OUT_DEFAULT_PRECIS, // nOutPrecision 
	CLIP_DEFAULT_PRECIS, // nClipPrecision 
	DEFAULT_QUALITY, // nQuality 
	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
	_T("Arial")); // lpszFac 
	GetDlgItem(IDC_ADDTITLE)->SetFont(af); //设置大标题字体
	BMUPC.LoadBitmap(IDB_BITMAPUPC);
	m_PictureUPC.SetBitmap(BMUPC);
	DWORD style1=WS_VISIBLE|WS_CHILD;
	m_LeftStart.EnableWindow(false);
	m_RightStart.EnableWindow(false);
	/*
	if(!myComm.Create(NULL,style1,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
//		AfxMessageBox("创建MSComm控件失败!");
		return -1;
	}
	*/
	m_progress.SetRange(0,80);
	m_progress.SetPos(0);
	m_progress.SetStep(2);

    m_List.InsertColumn(0,"序号");			//向控件中插入列
	m_List.SetColumnWidth(0,40);
	//向控件中插入列
	m_List.InsertColumn(1,"参数1");
	m_List.InsertColumn(2,"参数2");
	m_List.InsertColumn(3,"参数3");
	m_List.InsertColumn(4,"参数4");
	m_List.InsertColumn(5,"参数5");
	m_List.InsertColumn(6,"参数6");
	m_List.InsertColumn(7,"参数7");
	m_List.InsertColumn(8,"参数8");
	m_List.InsertColumn(9,"参数9");
	m_List.InsertColumn(10,"参数10");
	m_List.InsertColumn(11,"参数11");
	m_List.InsertColumn(12,"参数12");
	m_List.InsertColumn(13,"参数13");
	m_List.InsertColumn(14,"参数14");
	m_List.InsertColumn(15,"参数15");
	m_List.InsertColumn(16,"参数16");
	m_List.InsertColumn(17,"参数17");
	m_List.InsertColumn(18,"参数18");
	m_List.InsertColumn(19,"参数19");
	m_List.InsertColumn(20,"参数20");
	m_List.InsertColumn(21,"参数21");
	m_List.InsertColumn(22,"参数22");
	m_List.InsertColumn(23,"参数23");
	m_List.InsertColumn(24,"参数24");
	m_List.InsertColumn(25,"参数25");
	for(int i=1;i<26;i++)					//设置相应列的宽度
	{
		m_List.SetColumnWidth(i,50);
	}
	DWORD style = m_List.GetExtendedStyle();
    m_List.SetExtendedStyle(style | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Contr_Q1="Q1";
	Contr_Q1+=(TCHAR)0x0D;
	Contr_Q3="Q3";
	Contr_Q3+=(TCHAR)0x13;
	Contr_Q3+=(TCHAR)0x14;
	Contr_Q3+=(TCHAR)0x15;
	Contr_Q3+=(TCHAR)0x16;
	Contr_Q3+=(TCHAR)0x17;
	Contr_Q3+=(TCHAR)0x18;
	Contr_Q3+=(TCHAR)0x0D;
	Contr_Q7="Q7";
	Contr_Q7+=(TCHAR)0x0D;
	Contr_Q10="Q10";
	Contr_Q10+=(TCHAR)0x0D;
	Contr_QD0="QD0";
	Contr_QD0+=(TCHAR)0x0D;
	Contr_ON="S";
	Contr_ON+=(TCHAR)0x0D;
	Contr_OFF="T";
	Contr_OFF+=(TCHAR)0x0D;


	int combo=IDC_COMBOCH1;
	for(int kk=0;kk<6;kk++)
	{
		combo=IDC_COMBOCH1+kk;
		((CComboBox*)GetDlgItem(combo))->AddString("0 NULL");
		((CComboBox*)GetDlgItem(combo))->AddString("1 SUPFLAG");
		((CComboBox*)GetDlgItem(combo))->AddString("2 INTFLAG");
		((CComboBox*)GetDlgItem(combo))->AddString("3 PFCFLAG");
		((CComboBox*)GetDlgItem(combo))->AddString("4 EXFLAG");
		((CComboBox*)GetDlgItem(combo))->AddString("5 MULFLAG");
		((CComboBox*)GetDlgItem(combo))->AddString("6 RSVOLT");
		((CComboBox*)GetDlgItem(combo))->AddString("7 STVOLT");
		((CComboBox*)GetDlgItem(combo))->AddString("8 TRVOLT");
		((CComboBox*)GetDlgItem(combo))->AddString("9 BUSPVOLT");
		((CComboBox*)GetDlgItem(combo))->AddString("10 BUSNVOLT");
		((CComboBox*)GetDlgItem(combo))->AddString("11 RLCURRINV");
		((CComboBox*)GetDlgItem(combo))->AddString("12 SLCURRINV");
		((CComboBox*)GetDlgItem(combo))->AddString("13 TLCURRINV");
		((CComboBox*)GetDlgItem(combo))->AddString("14 ROPCURRINV");
		((CComboBox*)GetDlgItem(combo))->AddString("15 SOPCURRINV");
		((CComboBox*)GetDlgItem(combo))->AddString("16 TOPCURRINV");
		((CComboBox*)GetDlgItem(combo))->AddString("17 VDREF");
		((CComboBox*)GetDlgItem(combo))->AddString("18 VQREF");
		((CComboBox*)GetDlgItem(combo))->AddString("19 GET1");
		((CComboBox*)GetDlgItem(combo))->AddString("20 GET2");
		((CComboBox*)GetDlgItem(combo))->AddString("21 GET3");
		((CComboBox*)GetDlgItem(combo))->AddString("22 GET4");
		((CComboBox*)GetDlgItem(combo))->AddString("23 GET5");
		((CComboBox*)GetDlgItem(combo))->AddString("24 GET6");
		
		
	}
		((CComboBox*)GetDlgItem(IDC_COMBOCH1))->SetCurSel(0x13);
		((CComboBox*)GetDlgItem(IDC_COMBOCH2))->SetCurSel(0x14);
		((CComboBox*)GetDlgItem(IDC_COMBOCH3))->SetCurSel(0x15);
		((CComboBox*)GetDlgItem(IDC_COMBOCH4))->SetCurSel(0x16);
		((CComboBox*)GetDlgItem(IDC_COMBOCH5))->SetCurSel(0x17);
		((CComboBox*)GetDlgItem(IDC_COMBOCH6))->SetCurSel(0x18);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIPOMSPRODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPOMSPRODlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIPOMSPRODlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIPOMSPRODlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CString num;
	CString Data[25];
	
	CButton *pButton=(CButton *)GetDlgItem(IDC_CHECK1); 
	Check1 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK2); 
	Check2 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK3); 
	Check3 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK4); 
	Check4 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK5); 
	Check5 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK6); 
	Check6 = pButton->GetCheck();
	if(nIDEvent==1&&nIDEvent!=2)					//1s一次的调试数据处理
	{
		nRow=m_List.GetItemCount();
		num.Format("%d", nRow);
		m_List.InsertItem(nRow,num);
		UpdateData(true);
		if(m_NetFlag)				//网口通信模式
		{		
			if(DebugDataAllow)
			{
				int j = 1;
				while(j<25)
				{
					DataTSh.Format("%d",Debugbuf0[j-1]);
					m_List.SetItemText(nRow,j,DataTSh);
					j++;
					DebugDatalength--;
	
				}
				m_List.EnsureVisible(nRow, FALSE); 		
				DataTSh="";
				DebugDataAllow=FALSE;
			}
			else
			{
				
				int j = 1;
				while(j<25)
				{
					DataTSh="";
					m_List.SetItemText(nRow,j,DataTSh);
					j++;
					DebugDatalength--;
	
				}
				m_List.EnsureVisible(nRow, FALSE); 		
				DataTSh="";
				DebugDataAllow=FALSE;
				
			}
	
			SendData(Contr_Q1);	
//			HANDLE hThread=CreateThread(NULL,0,SaveProc,NULL,0,NULL);
//			CloseHandle(hThread);
		}		
	}

	if(nIDEvent==2&&nIDEvent!=1)					//实时数据波形显示及数据存储处理
	{
/**********************************************
****
****
***********************************************/

		if((m_NetFlag))				//网口通信模式
		{
//			double dTime = ::timeGetTime()/1000.0;
			double dValue[4];	
			m_wndScope.Clear();
			if(Check1==1)
			{	
				for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueA(dTime1,PCh1R[StartchannelPlayPoint+ij]);
					dTime1 += 0.01;
				}
			}
			else
			{
				m_wndScope.ClearA();
				dTime1=0;
			}
			if(Check2==1)
			{
				for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueB(dTime2,PCh2R[StartchannelPlayPoint+ij]);
					dTime2 += 0.01;
				}
			}
			else
			{
				m_wndScope.ClearB();
				dTime2=0;
			}
			if(Check3==1)
			{
				for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueC(dTime3,PCh3R[StartchannelPlayPoint+ij]);
					dTime3 += 0.01;
				}
			}
			else
			{
				m_wndScope.ClearC();
				dTime3=0;
			}
			if(Check4==1)
			{
				for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueD(dTime4,PCh4R[StartchannelPlayPoint+ij]);
					dTime4 += 0.01;
				}
			}
			else
			{
				m_wndScope.ClearD();
				dTime4=0;
			}
			if(Check5==1)
			{
				for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueE(dTime5,PCh5R[StartchannelPlayPoint+ij]);
					dTime5 += 0.01;
				}
			}
			else
			{
				m_wndScope.ClearE();
				dTime5=0;
			}
			if(Check6==1)
			{
				for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueF(dTime6,PCh6R[StartchannelPlayPoint+ij]);
					dTime6 += 0.01;
				}
			}
			else
			{
				m_wndScope.ClearF();
				dTime6=0;
			}

			m_wndScope.UpdateCurve();
			channelPlayPoint = 0;//清零保证重新画图
		}
	}
		if(nIDEvent==3)					
		SendData(Contr_Q3);
		CDialog::OnTimer(nIDEvent);
}

int CIPOMSPRODlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	return 0;
}

void CIPOMSPRODlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);	
	KillTimer(2);
	KillTimer(3);
	if(myComm.GetPortOpen())
		myComm.SetPortOpen(0);
	CDialog::OnClose();
}

void CIPOMSPRODlg::OnLeftstart() 
{
	// TODO: Add your control notification handler code here
	FlagStopStartL=!FlagStopStartL;
	if(FlagStopStartL)
	{	
		SetTimer(1,1000,NULL);//调试用定时器T=1s
	    //通过串口发送一次Q1.....
		DataTSh="";
		SendData(Contr_Q1);
//		SendData(Contr_QD0);
		//>>Stop
		GetDlgItem(IDC_LEFTSTART)->SetWindowText("Stop");
	}
	else
	{
		KillTimer(1);
		//>>Start
		GetDlgItem(IDC_LEFTSTART)->SetWindowText("Start");

	}
	
}

void CIPOMSPRODlg::OnRightstart() 
{
	// TODO: Add your control notification handler code here
	//图形数据传入并且开始绘图程序
	FlagStopStartR=!FlagStopStartR;


	int CH1C,CH2C,CH3C,CH4C,CH5C,CH6C;
	CH1C=((CComboBox*)GetDlgItem(IDC_COMBOCH1))->GetCurSel();
	CH2C=((CComboBox*)GetDlgItem(IDC_COMBOCH2))->GetCurSel();
	CH3C=((CComboBox*)GetDlgItem(IDC_COMBOCH3))->GetCurSel();
	CH4C=((CComboBox*)GetDlgItem(IDC_COMBOCH4))->GetCurSel();
	CH5C=((CComboBox*)GetDlgItem(IDC_COMBOCH5))->GetCurSel();
	CH6C=((CComboBox*)GetDlgItem(IDC_COMBOCH6))->GetCurSel();
	Contr_Q3="Q3";
	Contr_Q3+=(TCHAR)CH1C;
	Contr_Q3+=(TCHAR)CH2C;
	Contr_Q3+=(TCHAR)CH3C;
	Contr_Q3+=(TCHAR)CH4C;
	Contr_Q3+=(TCHAR)CH5C;
	Contr_Q3+=(TCHAR)CH6C;
	Contr_Q3+=(TCHAR)0x0D;
	if(FlagStopStartR)
	{	
		SetTimer(2,1000,NULL);//调试用定时器T=500ms	   
		SendData(Contr_Q3);
		SendData(Contr_Q10);
		SendData(Contr_Q3);
		SendData(Contr_Q10);
		SendData(Contr_Q3);
		SendData(Contr_Q10);
		//>>Stop
		GetDlgItem(IDC_RIGHTSTART)->SetWindowText("Stop");
	}
	else
	{
		SendData(Contr_Q7);
		SendData(Contr_Q7);
		SendData(Contr_Q7);
		KillTimer(2);
		//>>Start
		GetDlgItem(IDC_RIGHTSTART)->SetWindowText("Start");
	}
}

BEGIN_EVENTSINK_MAP(CIPOMSPRODlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CIPOMSPRODlg)
	ON_EVENT(CIPOMSPRODlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/****************信息接收函数*****************/
void CIPOMSPRODlg::OnOnCommMscomm1() 
{
}

/*****************网络设置函数****************/
void CIPOMSPRODlg::OnBnClickedSetnet()
{
	// TODO: Add your control notification handler code here
	// 以太网网络设置程序
	CString strStatus,strTemp;
	if(mySetNetDlg.DoModal()==IDOK)
	{	
		if(m_socket)
		closesocket(m_socket);
		UpdateData(true);
		InitSocket();
		addrTo.sin_family=AF_INET;
		addrTo.sin_port=htons(mySetNetDlg.m_PortNumDS);
		addrTo.sin_addr.S_un.S_addr=htonl(mySetNetDlg.dwIP);
	}

}

/********串口设置函数********************/
void CIPOMSPRODlg::OnSetupcom() 
{
	if(FlagSend==FALSE)
	{
//		SetTimer(3,20,NULL);
		FlagSend=TRUE;
	}
	else
	{
//		KillTimer(3);
		FlagSend=FALSE;	
	}
	UpdateData();
	if(m_NetFlag==TRUE)
	{
	CString strSend;
	WSABUF wsabuf;
	DWORD dwSend;
	int len;
	GetDlgItemText(IDC_EDIT8,strSend);
	strSend +=(TCHAR)0x0D;//在发送数据后边加回车
	len=strSend.GetLength();
	wsabuf.buf=strSend.GetBuffer(len);
	wsabuf.len=len+1;
//	SetDlgItemText(IDC_EDIT8,"");
	if(SOCKET_ERROR==WSASendTo(m_socket,&wsabuf,1,&dwSend,0,
			(SOCKADDR*)&addrTo,sizeof(SOCKADDR),NULL,NULL))
	{
		MessageBox("发送数据失败！");
		return;
	}
	}
}
/**********发送数据函数************/
void CIPOMSPRODlg::SendData(CString strInput)
{
	int iLenth;
	CByteArray Array1;
	iLenth=strInput.GetLength();
	if(m_NetFlag)
	{
		WSABUF wsabuf;
		DWORD dwSend;
		int len;
		len=strInput.GetLength();
		wsabuf.buf=strInput.GetBuffer(len);
		wsabuf.len=len+1;
		if(SOCKET_ERROR==WSASendTo(m_socket,&wsabuf,1,&dwSend,0,
				(SOCKADDR*)&addrTo,sizeof(SOCKADDR),NULL,NULL))
		{
			MessageBox("发送数据失败！");
			return;
		}
	}
}

void CIPOMSPRODlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);	
	KillTimer(2);
	KillTimer(3);
	/*
	if(myComm.GetPortOpen())
	myComm.SetPortOpen(0);
	*/
	CDialog::OnCancel();
}
/**********保存到TXT文件函数*************/
void CIPOMSPRODlg::OnSaveToTxT() 
{
	// TODO: Add your control notification handler code here
/////////////////////////////////////////////////////////////////////////////////////////////////	
	HANDLE hThread=CreateThread(NULL,0,SaveProc,NULL,0,NULL);
	CloseHandle(hThread);
}

/**********************初始化设置Socket*********************/
bool CIPOMSPRODlg::InitSocket(void)
{
	m_socket=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,0);
	if(INVALID_SOCKET==m_socket)
	{
		MessageBox("创建套接字失败！");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSock.sin_family=AF_INET;
	m_PortNumber=mySetNetDlg.m_PortNumLC;
	addrSock.sin_port=htons(m_PortNumber);
	if(SOCKET_ERROR==bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR)))
	{
		MessageBox("绑定失败！");
		m_NetFlag=FALSE;
		return FALSE;
	}
	if(SOCKET_ERROR==WSAAsyncSelect(m_socket,m_hWnd,UM_SOCK,FD_READ))
	{
		MessageBox("注册网络读取事件失败！");
		m_NetFlag=FALSE;
		return FALSE;
	}
//	MessageBox("网络设置成功");
	m_NetFlag=TRUE;	
	m_ComFlag=FALSE;
	m_LeftStart.EnableWindow(true);
	m_RightStart.EnableWindow(true);
	return TRUE;
}


LRESULT CIPOMSPRODlg::OnSock(WPARAM wParam,LPARAM lParam)
{
	switch(LOWORD(lParam))
	{
	case FD_READ:
	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->sock=m_socket;
	pRecvParam->hwnd=m_hWnd;
	HANDLE hThread=CreateThread(NULL,0,RecvProc,(LPVOID)pRecvParam,0,NULL);
	CloseHandle(hThread);
		break;
	}
	return 1;
}

DWORD WINAPI CIPOMSPRODlg::SaveProc(LPVOID lpParameter)
{
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//当前存在问题数据处理量过大电脑CPU占满，硬盘没有压力以后尝试数据库处理
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	CString sampleArray1,sampleArray2,sampleArray3,sampleArray4,sampleArray5,sampleArray6;
	CString Csvname,m_excelpath;	
	char SSaveData[10];
	unsigned int i;	
	Csvname="SAVE";
	m_excelpath+="D:\\"+Csvname+".csv";
	CStdioFile file;
	sampleArray1="";
	sampleArray2="";
	sampleArray3="";
	sampleArray4="";
	sampleArray5="";
	sampleArray6="";
	sampleArray1="CHANNAL1,";
	for(i=0;i<10000;i++)
		{
			_itoa_s(int(PCh1R[i]),SSaveData,10);
			sampleArray1=sampleArray1+(CString)SSaveData+',';
		}
	sampleArray1+="\r";
		
	sampleArray2="CHANNAL2,";
	for(i=0;i<10000;i++)
		{
			_itoa_s(int(PCh2R[i]),SSaveData,10);
			sampleArray2=sampleArray2+(CString)SSaveData+',';
		}
	sampleArray2+="\r";

	sampleArray3="CHANNAL3,";
	for(i=0;i<10000;i++)
		{
			_itoa_s(int(PCh3R[i]),SSaveData,10);
			sampleArray3=sampleArray3+(CString)SSaveData+',';
		}
	sampleArray3+="\r";

	sampleArray4="CHANNAL4,";
	for(i=0;i<10000;i++)
		{
			_itoa_s(int(PCh4R[i]),SSaveData,10);
			sampleArray4=sampleArray4+(CString)SSaveData+',';
		}
	sampleArray4+="\r";

	sampleArray5="CHANNAL5,";
	for(i=0;i<10000;i++)
		{
			_itoa_s(int(PCh5R[i]),SSaveData,10);
			sampleArray5=sampleArray5+(CString)SSaveData+',';
		}
	sampleArray5+="\r";

	sampleArray6="CHANNAL6,";
	for(i=0;i<10000;i++)
		{
			_itoa_s(int(PCh6R[i]),SSaveData,10);
			sampleArray6=sampleArray6+(CString)SSaveData+',';
		}
	sampleArray6+="\r";

	

	file.Open(m_excelpath,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	file.SeekToEnd();
	file.WriteString(sampleArray1);		

	file.WriteString(sampleArray2);
	file.WriteString(sampleArray3);
	file.WriteString(sampleArray4);
	file.WriteString(sampleArray5);
	file.WriteString(sampleArray6);	

	file.Close();
	return 0;
}


/*数据接收以及数据处理函数，在后台线程实现，由接收到数据后的消息相应函数创建线程调用 */
DWORD WINAPI CIPOMSPRODlg::RecvProc(LPVOID lpParameter)
{

	SOCKET sock=((RECVPARAM*)lpParameter)->sock;
	HWND hwnd=((RECVPARAM*)lpParameter)->hwnd;
	delete lpParameter;	
		WSABUF wsabuf;
		wsabuf.buf= DataReadBuf0;
		wsabuf.len=40000;
		DWORD dwFlag=0;
		SOCKADDR_IN addrFrom;
		int len=sizeof(SOCKADDR);
		CString str;
		if(SOCKET_ERROR!=WSARecvFrom(sock,&wsabuf,1,&NetDatalen,&dwFlag,
						(SOCKADDR*)&addrFrom,&len,NULL,NULL))
		{		
			NetDatabuf=(short int*)DataReadBuf0;
			DWORD i=0;
			DWORD liv_datalen;
			liv_datalen = NetDatalen>>1;



			while(i<liv_datalen)
			{
/////////////////////////////////////////////////////////////////////////////////////////////////
				if(NetDatabuf[i]==0x4EEE)//调试数据标志位
				{
					DebugDatalength = 0;
					i++;
					while((NetDatabuf[i]<0x4000)&&(i<liv_datalen))
					{
						Debugbuf0[DebugDatalength] = NetDatabuf[i];
						i++;
						DebugDatalength++;
					}
					DebugDataAllow=TRUE;
				}
/////////////////////////////////////////////////////////////////////////////////////////////////
				if(NetDatabuf[i]==0x7EEE)//通道数据
				{
					if(NetDatabuf[i+7]==0x7FFF&&(i+6<liv_datalen))
					{
						i++;
						PCh1W[CHNum] = NetDatabuf[i];
						PCh2W[CHNum] = NetDatabuf[i+1];
						PCh3W[CHNum] = NetDatabuf[i+2];
						PCh4W[CHNum] = NetDatabuf[i+3];
						PCh5W[CHNum] = NetDatabuf[i+4];
						PCh6W[CHNum] = NetDatabuf[i+5];
						i+=6;
						CHNum++;	
						if(CHNum>=9600)
						{
 							CHNum=0;	
							PChC=PCh1W;
							PCh1W=PCh1R;
							PCh1R=PChC;
							PChC=PCh2W;
							PCh2W=PCh2R;
							PCh2R=PChC;
							PChC=PCh3W;
							PCh3W=PCh3R;
							PCh3R=PChC;
							PChC=PCh4W;
							PCh4W=PCh4R;
							PCh4R=PChC;
							PChC=PCh5W;
							PCh5W=PCh5R;
							PCh5R=PChC;
							PChC=PCh6W;
							PCh6W=PCh6R;
							PCh6R=PChC;
						}
					}
				}
														
/////////////////////////////////////////////////////////////////////////////////////////////////
				if(NetDatabuf[i]==0x4F00)//数据结束
				{
					break;
					i=i;
					liv_datalen=liv_datalen;	
				}
				i++;
			}
			::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)wsabuf.buf);
		}
	return 0;
}


LRESULT CIPOMSPRODlg::OnRecvData(WPARAM wParam,LPARAM lParam)
{
	/*
		CString str=(char*)lParam;
		DataNetBuffer_CString=str;
		CString strTemp;
		str+="\r\n";
		GetDlgItemText(IDC_EDIT9,strTemp);
		str+=strTemp;
		SetDlgItemText(IDC_EDIT9,str);
	*/
		return 0;
}







void CIPOMSPRODlg::OnBnClickedButimedown()
{
	// TODO: Add your control notification handler code here
	// 变量减小函数
	m_wndScope.Button(0);
}


void CIPOMSPRODlg::OnBnClickedButimeup()
{
	// TODO: Add your control notification handler code here
	// 变量增大函数
	m_wndScope.Button(1);
}


void CIPOMSPRODlg::OnBnClickedButimeleft()
{
	// TODO: Add your control notification handler code here
	// 图形缩紧函数
	m_wndScope.Button(2);	
	midlenthtest = m_wndScope.m_dDimT*1000;
	ReLoadData();
	
}


void CIPOMSPRODlg::OnBnClickedBzutimeright()
{
	// TODO: Add your control notification handler code here
	//图形拉宽函数
	m_wndScope.Button(3);
	midlenthtest = m_wndScope.m_dDimT*1000;
	ReLoadData();
}


void CIPOMSPRODlg::OnBnClickedButmovleft()
{
	// TODO: Add your control notification handler code here
	// 图形位置左移函数
	midlenthtest = m_wndScope.m_dDimT*1000;
	float dTimel=0;
	if(StartchannelPlayPoint>30)
	StartchannelPlayPoint-=30;
	ReLoadData();
}


void CIPOMSPRODlg::OnBnClickedButmovright()
{
	// TODO: Add your control notification handler code here
	// 图形位置右移函数
	midlenthtest = m_wndScope.m_dDimT*1000;
	float dTimel=0;
	if(StartchannelPlayPoint<9570)
	StartchannelPlayPoint+=30;
	ReLoadData();

}


void CIPOMSPRODlg::OnBnClickedScoperest()
{
	// TODO: Add your control notification handler code here
	// 示波器复位函数
	StartchannelPlayPoint=200;
	m_wndScope.m_dDimT=1;
	m_wndScope.m_dDimY=5000;
	midlenthtest = m_wndScope.m_dDimT*1000;
	m_wndScope.Clear();
	m_wndScope.Button(2);
	m_wndScope.Button(3);
	ReLoadData();
}


// 重新载入需要显示的数据
void CIPOMSPRODlg::ReLoadData(void)
{
	//


	
	float dTimel1=0;
	float dTimel2=0;
	float dTimel3=0;
	float dTimel4=0;
	float dTimel5=0;
	float dTimel6=0;
	/*
	CButton *pButton=(CButton *)GetDlgItem(IDC_CHECK1); 
	Check1 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK2); 
	Check2 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK3); 
	Check3 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK4); 
	Check4 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK5); 
	Check5 = pButton->GetCheck();
	pButton=(CButton *)GetDlgItem(IDC_CHECK6); 
	Check6 = pButton->GetCheck();
	*/
	m_wndScope.Clear();
	if(Check1==1)
			{
			for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueA(dTimel1,PCh1R[StartchannelPlayPoint+ij]);
					dTimel1 += 0.01;
				}	
			}
			else
			{
				m_wndScope.ClearA();
				dTimel1 = 0;
			}
	if(Check2==1)
			{
			for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueB(dTimel2,PCh2R[StartchannelPlayPoint+ij]);
					dTimel2 += 0.01;
				}	
			}
			else
			{
				m_wndScope.ClearB();
				dTimel2 = 0;
			}

	if(Check3==1)
			{
			for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueC(dTimel3,PCh3R[StartchannelPlayPoint+ij]);
					dTimel3 += 0.01;
				}	
			}
			else
			{
				m_wndScope.ClearC();
				dTimel3 = 0;
			}

	if(Check4==1)
			{
			for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueD(dTimel4,PCh4R[StartchannelPlayPoint+ij]);
					dTimel4 += 0.01;
				}	
			}
			else
			{
				m_wndScope.ClearD();
				dTimel4 = 0;
			}

	if(Check5==1)
			{
			for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueE(dTimel5,PCh5R[StartchannelPlayPoint+ij]);
					dTimel5 += 0.01;
				}	
			}
			else
			{
				m_wndScope.ClearE();
				dTimel5 = 0;
			}

	if(Check6==1)
			{
			for(int ij=0;ij<midlenthtest;ij++)
				{
					m_wndScope.AddValueF(dTimel6,PCh6R[StartchannelPlayPoint+ij]);
					dTimel6 += 0.01;
				}	
			}
			else
			{
				m_wndScope.ClearF();
				dTimel6 = 0;
			}
	m_wndScope.UpdateCurve();	

}


void CIPOMSPRODlg::OnBnClickedButtonturnon()
{
	// TODO: Add your control notification handler code here
	//系统启动程序
	SendData(Contr_ON);
}


void CIPOMSPRODlg::OnBnClickedButtonturnoff()
{
	// TODO: Add your control notification handler code here
	//系统停止程序
	SendData(Contr_OFF);
}


/*
*********************************************************************************************************
*                                                  结束
*********************************************************************************************************
*/


