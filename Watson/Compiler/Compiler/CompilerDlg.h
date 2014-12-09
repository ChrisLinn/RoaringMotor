
// CompilerDlg.h : 头文件
//

#pragma once


// CCompilerDlg 对话框
class CCompilerDlg : public CDialogEx
{
// 构造
public:
	CCompilerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMPILER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedCompile();
	afx_msg void OnBnClickedRun();
};
