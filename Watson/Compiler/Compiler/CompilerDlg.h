
// CompilerDlg.h : ͷ�ļ�
//

#pragma once


// CCompilerDlg �Ի���
class CCompilerDlg : public CDialogEx
{
// ����
public:
	CCompilerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMPILER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedCompile();
	afx_msg void OnBnClickedRun();
};
