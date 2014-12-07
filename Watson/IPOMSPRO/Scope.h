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
	void SetTitle(CString strTitle);//���Ʊ���
	void SetValueA(double dValue);//������ֵ����A
	void SetValueB(double dValue);//������ֵ����B
	void SetValueC(double dValue);//������ֵ����A
	void SetValueD(double dValue);//������ֵ����B
	void SetValueE(double dValue);//������ֵ����A
	void SetValueF(double dValue);//������ֵ����B

	void SetValueString(CString strTitle,CString strUnit);//������ֵ
	void SetDimT(double newDimT);//ʱ���ⲿ�ӿں���
	void SetDimy(double newDimY);//�����ⲿ�ӿں���
	void SetBase(int nNewABase,int nRange);//���ƻ���
	void UpdateCurve();//����ˢ��
	void AddValueA(double dTime,double dValue);//���ƶ�̬����A
	void AddValueB(double dTime,double dValue);//���ƶ�̬����B
	void AddValueC(double dTime,double dValue);//���ƶ�̬����C
	void AddValueD(double dTime,double dValue);//���ƶ�̬����D
	void AddValueE(double dTime,double dValue);//���ƶ�̬����E
	void AddValueF(double dTime,double dValue);//���ƶ�̬����F

	void Clear();//�������
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
	CRect	m_rectCurve;//��������
	CRect	m_rectValue;//��ֵ����
	CRect   m_rectCurvePanel;//�����������
	CRect   m_rectValuePanel;//��ֵ�������
	CRect   m_rectScroll;//��������

	CRgn	m_rgnCurve;//���߷�Χ
	CRgn	m_rgnYPlus;//�������Ӱ�ť��Χ
	CRgn	m_rgnYMinus;//���ȼ��ٰ�ť��Χ
	CRgn	m_rgnTPlus;//ʱ�����Ӱ�ť��Χ
	CRgn	m_rgnTMinus;//ʱ����ٰ�ť��Χ
    
	CBrush  m_BkBrush;//��ɫ��ˢ
	CBrush  m_PanelBrush;//��廭ˢ
	CBrush  m_CurveBrush;//���߻�ˢ

	CPen    m_PenCurveA;//����A����
	CPen    m_PenCurveB;//����B����
	CPen    m_PenCurveC;//����C����
	CPen    m_PenCurveD;//����D����
	CPen    m_PenCurveE;//����C����
	CPen    m_PenCurveF;//����D����

	CPen    m_PenGrid;//��񻭱�
	CPen    m_PenBrightLine;//���߻���
	CPen    m_PenDarkLine;//���߻���

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
