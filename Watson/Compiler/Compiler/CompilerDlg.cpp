
// CompilerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Compiler.h"
#include "CompilerDlg.h"
#include "afxdialogex.h"
#include "windows.h"
#include "shellapi.h"
#include <locale.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define BUF_SIZE 256
TCHAR szNameIn1[]=TEXT("Global\\DiyIn1");
TCHAR szNameIn2[]=TEXT("Global\\DiyIn2");
TCHAR szNameOut[]=TEXT("Global\\DiyOut");    //指向同一块共享内存的名字
double* DataU,* DataI,* Result;

HANDLE hMapFileIn1,hMapFileIn2,hMapFileOut;
LPCTSTR pBufIn1,pBufIn2,pBufOut;


// CCompilerDlg 对话框
CCompilerDlg::CCompilerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompilerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompilerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCompilerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_QUIT, &CCompilerDlg::OnBnClickedQuit)
	ON_BN_CLICKED(IDC_COMPILE, &CCompilerDlg::OnBnClickedCompile)
	ON_BN_CLICKED(IDC_RUN, &CCompilerDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_RESTORE, &CCompilerDlg::OnBnClickedRestore)
	ON_BN_CLICKED(IDC_RESTORE2, &CCompilerDlg::OnBnClickedRestore2)
END_MESSAGE_MAP()


// CCompilerDlg 消息处理程序

BOOL CCompilerDlg::OnInitDialog()
{
	HANDLE hMapFileIn1,hMapFileIn2,hMapFileOut;
    LPCTSTR pBufIn1,pBufIn2,pBufOut;

    hMapFileIn1 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szNameIn1);                 // name of mapping object

    if (hMapFileIn1 == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBufIn1 = (LPTSTR) MapViewOfFile(hMapFileIn1,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBufIn1 == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFileIn1);

        return 1;
    }
	
    hMapFileIn2 = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szNameIn2);                 // name of mapping object

    if (hMapFileIn2 == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBufIn2 = (LPTSTR) MapViewOfFile(hMapFileIn2,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBufIn2 == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFileIn2);

        return 1;
    }
	
	
    hMapFileOut = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szNameOut);                 // name of mapping object

    if (hMapFileOut == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }
    pBufOut = (LPTSTR) MapViewOfFile(hMapFileOut,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBufOut == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFileOut);

        return 1;
    }

	DataU=(double*)pBufIn1;
	DataI=(double*)pBufIn2;
	Result=(double*)pBufOut;
    //获取共享内存的指针






	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCompilerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCompilerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCompilerDlg::OnBnClickedCompile()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile myFile;
	CFileException fileException;
	CString DiyText;
	//获得EDIT  
	CEdit* pDiyText; 
	pDiyText = (CEdit*) GetDlgItem(IDC_EDIT1); 
	pDiyText-> GetWindowText(DiyText);

	CopyFile((CString)"DiyRaw.txt",(CString)"Diy.c",false);
	
 	if (!myFile.Open(_T("Diy.c"), CFile::modeNoTruncate |  CFile::typeText |  CFile::modeReadWrite, &fileException )){
		MessageBox(_T("代码生成失败，请重试"),_T("编译"),MB_OK);
	}
	myFile.Seek(0,CFile::end);
	myFile.WriteString(DiyText);
	myFile.Seek(0,CFile::end);
	myFile.WriteString((LPCTSTR)"}");

	ShellExecute(NULL,_T("open"),_T("compile.bat"),NULL,NULL,SW_SHOW);

	myFile.Close();
	DiyText.ReleaseBuffer();
}


void CCompilerDlg::OnBnClickedRun()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!Result[1]){
		Result[1]=1;
		ShellExecute(NULL,_T("open"),_T("Diy.exe"),NULL,NULL,SW_HIDE);
	}
}


void CCompilerDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	Result[1]=0;
    UnmapViewOfFile(pBufIn1);
    CloseHandle(hMapFileIn1);
    UnmapViewOfFile(pBufIn2);
    CloseHandle(hMapFileIn2);
    UnmapViewOfFile(pBufOut);
    CloseHandle(hMapFileOut);
	CDialog::OnCancel();
}


void CCompilerDlg::OnBnClickedRestore()
{	
	CStdioFile myFileBackup;
	CFileException fileException;
	CString DiyText,strLine;
	DiyText=strLine="";
	CEdit* pDiyText; 
	pDiyText = (CEdit*) GetDlgItem(IDC_EDIT1); 
	if (!myFileBackup.Open(_T("backup.txt"), CFile::modeNoTruncate |  CFile::typeText |  CFile::modeReadWrite, &fileException )){
		MessageBox(_T("恢复失败，请重试"),_T("恢复"),MB_OK);
	}
	while( myFileBackup.ReadString( strLine ) ){
		DiyText += strLine+_T("\r\n");
	}
	pDiyText-> SetWindowText(DiyText);
	MessageBox(_T("恢复成功！"),_T("恢复"),MB_OK);
	myFileBackup.Close();
	DiyText.ReleaseBuffer();
	strLine.ReleaseBuffer();
}


void CCompilerDlg::OnBnClickedRestore2()
{
	// TODO: Add your control notification handler code here
	CStdioFile myFile;
	CFileException fileException;
	CString DiyText;
	//获得EDIT  
	CEdit* pDiyText; 
	pDiyText = (CEdit*) GetDlgItem(IDC_EDIT1); 
	pDiyText-> GetWindowText(DiyText);

	
 	if (!myFile.Open(_T("backup.txt"), CFile::modeCreate |  CFile::typeText |  CFile::modeReadWrite, &fileException )){
		MessageBox(_T("备份失败，请重试"),_T("备份"),MB_OK);
	}
	myFile.Seek(0,CFile::end);
	myFile.WriteString(DiyText);
	MessageBox(_T("备份成功！"),_T("备份"),MB_OK);

	myFile.Close();
	DiyText.ReleaseBuffer();
}
