#if !defined(AFX_SCOPE1_H__20373609_0B81_493C_8F94_B4644298A84F__INCLUDED_)
#define AFX_SCOPE1_H__20373609_0B81_493C_8F94_B4644298A84F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Scope1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScope window
#include <list>
#include <iterator>
//using std::list;
//using std::iterator;	

class CScope : public CStatic
{
// Construction
public:
	CScope();
// Attributes
public:
// Operations
public:
	void SetTitle(CString strTitle);//绘制标题
	void SetValueA(double dValue);//绘制数值区域A
	void SetValueB(double dValue);//绘制数值区域B
	void SetValueC(double dValue);//绘制数值区域A
	void SetValueD(double dValue);//绘制数值区域B
	void SetValueE(double dValue);//绘制数值区域A
	void SetValueF(double dValue);//绘制数值区域B

	void SetValueString(CString strTitle,CString strUnit);//填入数值
	void SetDimT(double newDimT);//时间外部接口函数
	void SetDimy(double newDimY);//幅度外部接口函数
	void SetBase(int nNewABase,int nRange);//绘制基线
	void UpdateCurve();//曲线刷新
	void AddValueA(double dTime,double dValue);//绘制动态曲线A
	void AddValueB(double dTime,double dValue);//绘制动态曲线B
	void AddValueC(double dTime,double dValue);//绘制动态曲线C
	void AddValueD(double dTime,double dValue);//绘制动态曲线D
	void AddValueE(double dTime,double dValue);//绘制动态曲线E
	void AddValueF(double dTime,double dValue);//绘制动态曲线F

	void Clear();//清除函数
//	double newDimT;
	
private:
	int ConvertTimeToAxisX(double dTime);
	int ConvertValueToAxisY(double dValue);
	void DrawValueA(CDC *pDC);
	void DrawValuePanel(CDC *pDC);
	void DrawTitle(CDC *pDC);
	void DrawCurvePanel(CDC *pDC);
	void DrawGrid(CDC *pDC);
	void DrawCurveA(CDC *pDC);
	void DrawCurveB(CDC *pDC);
	void DrawCurveC(CDC *pDC);
	void DrawCurveD(CDC *pDC);
	void DrawCurveE(CDC *pDC);
	void DrawCurveF(CDC *pDC);


	void DrawAxis(CDC *pDC);
	void DrawTrack(CDC *pDC,BOOL bPressed);
	void DrawArrow(CDC *pDC,int nIndex,BOOL bLighted);
private:
	CRect	m_rectCurve;//曲线区域
	CRect	m_rectValue;//数值区域
	CRect   m_rectCurvePanel;//曲线面板区域
	CRect   m_rectValuePanel;//数值面板区域
	CRect   m_rectScroll;//滑块区域

	CRgn	m_rgnCurve;//曲线范围
	CRgn	m_rgnYPlus;//幅度增加按钮范围
	CRgn	m_rgnYMinus;//幅度减少按钮范围
	CRgn	m_rgnTPlus;//时间增加按钮范围
	CRgn	m_rgnTMinus;//时间减少按钮范围
    
	CBrush  m_BkBrush;//黑色画刷
	CBrush  m_PanelBrush;//面板画刷
	CBrush  m_CurveBrush;//曲线画刷

	CPen    m_PenCurveA;//曲线A画笔
	CPen    m_PenCurveB;//曲线B画笔
	CPen    m_PenCurveC;//曲线C画笔
	CPen    m_PenCurveD;//曲线D画笔
	CPen    m_PenCurveE;//曲线C画笔
	CPen    m_PenCurveF;//曲线D画笔

	CPen    m_PenGrid;//表格画笔
	CPen    m_PenBrightLine;//明线画笔
	CPen    m_PenDarkLine;//暗线画笔

	CFont   m_FontTitle;
	CFont   m_FontValue;
	CFont   m_FontAxis;
	CFont   m_FontLabel;
	   


	int		m_Amove;
	int		m_Bmove;
	int		m_Cmove;
	int		m_Dmove;
	int		m_Emove;
	int		m_Fmove;
	int		m_nBase;
	int		m_nRange;
	int     m_nArrowIndex;
	BOOL    m_bPressed ;

	BOOL	m_bDrawing;

	CBitmap m_bitmapTitle;
	CBitmap m_bitmapTrack;


	CString m_strTitle;
	CString m_strValueName;
	CString m_strUnitName;
	std::list<double> m_TimeListA;
	std::list<double> m_ValueListA;
	std::list<double> m_TimeListB;
	std::list<double> m_ValueListB;
	std::list<double> m_TimeListC;
	std::list<double> m_ValueListC;
	std::list<double> m_TimeListD;
	std::list<double> m_ValueListD;
	std::list<double> m_TimeListE;
	std::list<double> m_ValueListE;
	std::list<double> m_TimeListF;
	std::list<double> m_ValueListF;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScope)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ClearB();
	void ClearA();
	void ClearD();
	void ClearC();
	void ClearE();
	void ClearF();

	void Button(int i);
	virtual ~CScope();

	// Generated message map functions
public:
	double  m_dDimT;
	double  m_dDimY;
	double  m_dValue;
protected:
	
	//{{AFX_MSG(CScope)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOPE1_H__20373609_0B81_493C_8F94_B4644298A84F__INCLUDED_)
