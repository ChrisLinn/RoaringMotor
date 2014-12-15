
// CompilerDlg.cpp : ʵ���ļ�
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
TCHAR szNameOut[]=TEXT("Global\\DiyOut");    //ָ��ͬһ�鹲���ڴ������
double* DataU,* DataI,* Result;

HANDLE hMapFileIn1,hMapFileIn2,hMapFileOut;
LPCTSTR pBufIn1,pBufIn2,pBufOut;


// CCompilerDlg �Ի���
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


// CCompilerDlg ��Ϣ�������

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
    //��ȡ�����ڴ��ָ��






	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCompilerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCompilerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCompilerDlg::OnBnClickedCompile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStdioFile myFile;
	CFileException fileException;
	CString DiyText;
	//���EDIT  
	CEdit* pDiyText; 
	pDiyText = (CEdit*) GetDlgItem(IDC_EDIT1); 
	pDiyText-> GetWindowText(DiyText);

	CopyFile((CString)"DiyRaw.txt",(CString)"Diy.c",false);
	
 	if (!myFile.Open(_T("Diy.c"), CFile::modeNoTruncate |  CFile::typeText |  CFile::modeReadWrite, &fileException )){
		MessageBox(_T("��������ʧ�ܣ�������"),_T("����"),MB_OK);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!Result[1]){
		Result[1]=1;
		ShellExecute(NULL,_T("open"),_T("Diy.exe"),NULL,NULL,SW_HIDE);
	}
}


void CCompilerDlg::OnBnClickedQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("�ָ�ʧ�ܣ�������"),_T("�ָ�"),MB_OK);
	}
	while( myFileBackup.ReadString( strLine ) ){
		DiyText += strLine+_T("\r\n");
	}
	pDiyText-> SetWindowText(DiyText);
	MessageBox(_T("�ָ��ɹ���"),_T("�ָ�"),MB_OK);
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
	//���EDIT  
	CEdit* pDiyText; 
	pDiyText = (CEdit*) GetDlgItem(IDC_EDIT1); 
	pDiyText-> GetWindowText(DiyText);

	
 	if (!myFile.Open(_T("backup.txt"), CFile::modeCreate |  CFile::typeText |  CFile::modeReadWrite, &fileException )){
		MessageBox(_T("����ʧ�ܣ�������"),_T("����"),MB_OK);
	}
	myFile.Seek(0,CFile::end);
	myFile.WriteString(DiyText);
	MessageBox(_T("���ݳɹ���"),_T("����"),MB_OK);

	myFile.Close();
	DiyText.ReleaseBuffer();
}
