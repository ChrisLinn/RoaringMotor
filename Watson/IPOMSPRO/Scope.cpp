// Scope1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Scope.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
	double newDimT;
/////////////////////////////////////////////////////////////////////////////
// CScope

CScope::CScope()//�����ʼ������
{
	m_Amove=0;
	m_Bmove=0;
	m_Cmove=0;
	m_Dmove=0;
	m_Emove=0;
	m_Fmove=0;


	m_BkBrush.CreateSolidBrush(RGB(0x00,0x00,0x33));
	m_PanelBrush.CreateSolidBrush(RGB(0x22,0x22,0x44));
	m_CurveBrush.CreateSolidBrush(RGB(0x00,0x00,0x00));

	m_PenCurveA.CreatePen(PS_SOLID,2,RGB(255,255,0));
	m_PenCurveB.CreatePen(PS_SOLID,2,RGB(0,255,255));
	m_PenCurveC.CreatePen(PS_SOLID,2,RGB(255,20,147));
	m_PenCurveD.CreatePen(PS_SOLID,2,RGB(0,255,0));

	m_PenCurveE.CreatePen(PS_SOLID,2,RGB(255,0,0));
	m_PenCurveF.CreatePen(PS_SOLID,2,RGB(0,0,255));

	m_PenGrid.CreatePen(PS_SOLID,0,RGB(192,192,192));
	m_PenBrightLine.CreatePen(PS_SOLID,0,RGB(0xff,0xff,0xff));
	m_PenDarkLine.CreatePen(PS_SOLID,0,RGB(0x55,0x55,0x55));

	m_FontTitle.CreateFont(18,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"����");
	m_FontAxis.CreateFont(15,0,0,0,FW_THIN,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
	m_FontValue.CreatePointFont(120,"FixedSys");
	m_FontLabel.CreatePointFont(120,"Times New Roman");

	m_dDimT	= 1;
	m_dDimY	= 5000;
	m_nBase = 20;
	m_nRange = 40;
	m_dValue= 0.0;
	m_nArrowIndex =-1;
	m_bPressed = FALSE;
}

CScope::~CScope()//�������ʱ�ͷ��ڴ�ռ�
{
	if(!m_TimeListA.empty())
		m_TimeListA.clear();
	if(!m_ValueListA.empty())
		m_ValueListA.clear();
	if(!m_TimeListB.empty())
		m_TimeListB.clear();
	if(!m_ValueListB.empty())
		m_ValueListB.clear();
	if(!m_TimeListC.empty())
		m_TimeListC.clear();
	if(!m_ValueListC.empty())
		m_ValueListC.clear();
	if(!m_TimeListD.empty())
		m_TimeListD.clear();
	if(!m_ValueListD.empty())
		m_ValueListD.clear();
	if(!m_TimeListE.empty())
		m_TimeListE.clear();
	if(!m_ValueListE.empty())
		m_ValueListE.clear();
	if(!m_TimeListF.empty())
		m_TimeListF.clear();
	if(!m_ValueListF.empty())
		m_ValueListF.clear();






}


BEGIN_MESSAGE_MAP(CScope, CStatic)//Windows��ӳ��
	//{{AFX_MSG_MAP(CScope)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScope message handlers

BOOL CScope::OnEraseBkgnd(CDC* pDC) //���������������
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;

	GetClientRect(&rect);//��ȡ�û�����
	rect.InflateRect(-0.5,-0.5,-3,-3);//curve panel////curve panelȷ��һ������͹��Ĳ��֣��Ĵ�С��λ�ã���������ľ���ֱ�Ϊ���ϡ��ҡ���
	m_rectCurvePanel = rect;//ȷ���������
	m_rectCurve = rect;//��ʾ���ߡ�����Ͱ�ť
	m_rectCurve.InflateRect(-35,-5,-10,-20);//curve areaȷ����ɫ�����������Ĵ�С

	m_rectValuePanel = rect;//��ʾ��ֵ�������
	m_rectValuePanel.top = rect.bottom+5;//ȷ����ֵ�����϶�λ�ã����������Ϊ���գ�
	m_rectValuePanel.bottom= m_rectValuePanel.top+51;//rectValuePanel createdȷ����ֵ�����¶�λ�ã����Լ����϶�Ϊ���գ�

	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&m_FontLabel);
	CSize size = pDC->GetTextExtent(m_strValueName);//��ȡ�ı���ռ����Ĵ�С
	m_rectValue.left = m_rectValuePanel.left+20+size.cx;//ȷ����ֵ������λ�ã�cxΪ�ı������ȣ�����ֵ������Ϊ���գ�
	m_rectValue.top = m_rectValuePanel.top+(m_rectValuePanel.Height()-size.cy)/2-2;//ȷ����ֵ����϶�λ��
	m_rectValue.bottom = m_rectValue.top+size.cy+4;//ȷ����ֵ����¶�λ�ã�cyΪ�ı�������
	size = pDC->GetTextExtent(m_strUnitName);
	m_rectValue.right = m_rectValuePanel.right - 20 - size.cx;//ȷ����ֵ����Ҷ�λ�ã�����ֵ����Ҷ�Ϊ����Ϊ���գ�
	pDC->SelectObject(pOldFont);//�ͷŵ�ǰ����
///////////////////////////////////////////////ȷ���������λ��ʱ��ԭ������Ļ�����Ͻ�

	if(m_rgnCurve.m_hObject==NULL)
		m_rgnCurve.CreateRectRgn(m_rectCurve.left+2,m_rectCurve.top+2,m_rectCurve.right-2,m_rectCurve.bottom-2);

/*	POINT ptYPlus[3];//�������Ӱ�ť
	POINT ptYMinus[3];//���ȼ��ٰ�ť
	POINT ptTPlus[3];//ʱ�����Ӱ�ť
	POINT ptTMinus[3];//ʱ����ٰ�ť
	ptYPlus[0].x = m_rectCurvePanel.left+15;//ȷ���������Ӱ�ť���϶˵��ˮƽλ��
	ptYPlus[0].y = m_rectCurve.bottom+3;//ȷ���������Ӱ�ť���϶˵�Ĵ�ֱλ��
	ptYPlus[1].x = ptYPlus[0].x-5;//ȷ���������Ӱ�ť����˵��ˮƽλ��
	ptYPlus[1].y = ptYPlus[0].y+6;//ȷ���������Ӱ�ť����˵�Ĵ�ֱλ��
	ptYPlus[2].x = ptYPlus[0].x+5;//ȷ���������Ӱ�ť���Ҷ˵��ˮƽλ��
	ptYPlus[2].y = ptYPlus[0].y+6;//ȷ���������Ӱ�ť���Ҷ˵�Ĵ�ֱλ��

	ptYMinus[0].x = m_rectCurvePanel.left+5;
	ptYMinus[0].y = m_rectCurve.bottom+18;
	ptYMinus[1].x = ptYMinus[0].x-5;
	ptYMinus[1].y = ptYMinus[0].y-6;
	ptYMinus[2].x = ptYMinus[0].x+5;
	ptYMinus[2].y = ptYMinus[0].y-6;

	ptTPlus[0].x = m_rectScroll.left+m_rectScroll.Width()/2;
	ptTPlus[0].y = m_rectCurve.bottom+3;
	ptTPlus[1].x = ptTPlus[0].x-5;
	ptTPlus[1].y = ptTPlus[0].y+6;
	ptTPlus[2].x = ptTPlus[0].x+5;
	ptTPlus[2].y = ptTPlus[0].y+6;

	ptTMinus[0].x = m_rectScroll.left+m_rectScroll.Width()/2;
	ptTMinus[0].y = m_rectCurve.bottom+18;
	ptTMinus[1].x = ptTMinus[0].x-5;
	ptTMinus[1].y = ptTMinus[0].y-6;
	ptTMinus[2].x = ptTMinus[0].x+5;
	ptTMinus[2].y = ptTMinus[0].y-6;
	if(m_rgnYPlus.m_hObject==NULL)
		m_rgnYPlus.CreatePolygonRgn( ptYPlus, 3, ALTERNATE );
	if(m_rgnYMinus.m_hObject==NULL)
		m_rgnYMinus.CreatePolygonRgn( ptYMinus, 3, ALTERNATE );
	if(m_rgnTPlus.m_hObject==NULL)
		m_rgnTPlus.CreatePolygonRgn( ptTPlus, 3, ALTERNATE );
	if(m_rgnTMinus.m_hObject==NULL)
		m_rgnTMinus.CreatePolygonRgn( ptTMinus, 3, ALTERNATE );
*/	
	return TRUE;
}

void CScope::OnPaint() //��̬����Լ�����������пؼ��Ļ���
{
	CPaintDC dc(this); 
	DrawCurvePanel(&dc);//��ʾ�������
	DrawGrid(&dc);//���ֻ�������

	DrawCurveA(&dc);//�������Ҳ�
	DrawCurveB(&dc);//���Ʒ���
	DrawCurveC(&dc);//�������Ҳ�
	DrawCurveD(&dc);//���Ʒ���
	DrawCurveE(&dc);//�������Ҳ�
	DrawCurveF(&dc);//���Ʒ���
	DrawAxis(&dc);//���ƿ̶�
}
void CScope::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CStatic::PreSubclassWindow();
}
void CScope::DrawTitle(CDC *pDC)//���Ʊ�����
{
}
void CScope::SetTitle(CString strTitle)//������������
{	
}
void CScope::DrawValuePanel(CDC *pDC)//������ֵ��壨�����¶˵����崰���Լ���������֣�
{
}

void CScope::DrawValueA(CDC *pDC)//����һ���ı��򣬲����ڿ�����ʾ������
{
}

void CScope::SetValueA(double dValue)//�ڶԻ����в���һ����-4��4�仯����ֵ
{
}

void CScope::SetValueB(double dValue)//�ڶԻ����в���һ����-4��4�仯����ֵ��û��ҪŪ������
{
}

void CScope::SetValueC(double dValue)//�ڶԻ����в���һ����-4��4�仯����ֵ
{
}

void CScope::SetValueD(double dValue)//�ڶԻ����в���һ����-4��4�仯����ֵ��û��ҪŪ������
{
}

void CScope::SetValueE(double dValue)//�ڶԻ����в���һ����-4��4�仯����ֵ��û��ҪŪ������
{
}
void CScope::SetValueF(double dValue)//�ڶԻ����в���һ����-4��4�仯����ֵ��û��ҪŪ������
{
}

void CScope::SetDimT(double DimT)//���ⲿ��������
{
/*	if(m_dDimT==DimT/10)
	{
		return;
	}
	else
	{
		m_dDimT = DimT/10;
		Invalidate();//�ػ��������ˢ��
	}*/
}
void CScope::SetDimy(double newDimY)//���ⲿ��������
{
/*
	if(m_dDimY==newDimY)	
	{

		return;
	}
	else
	{
		m_dDimY = newDimY;
		Invalidate();//�ػ��������ˢ��
	}*/
}
void CScope::SetBase(int nNewABase,int nRange)//���ⲿ��������
{
}


void CScope::DrawCurvePanel(CDC *pDC)//��������������䣬�������������Ч��
{
	CPen *pOldPen;
	pDC->FillRect(&m_rectCurvePanel,&m_PanelBrush);//������ɫ����������

	pOldPen = pDC->SelectObject(&m_PenBrightLine);//���õ�ǰĬ�ϻ���Ϊm_PenBrightLine
	pDC->MoveTo(m_rectCurvePanel.left,m_rectCurvePanel.top);
	pDC->LineTo(m_rectCurvePanel.left,m_rectCurvePanel.bottom);
	pDC->MoveTo(m_rectCurvePanel.left,m_rectCurvePanel.top);
	pDC->LineTo(m_rectCurvePanel.right,m_rectCurvePanel.top);
/////////////////////�����߹��������������Ա�Ч��
	pDC->SelectObject(&m_PenDarkLine);//���õ�ǰĬ�ϻ���Ϊm_PenDarkLine
	pDC->MoveTo(m_rectCurvePanel.right,m_rectCurvePanel.top);
	pDC->LineTo(m_rectCurvePanel.right,m_rectCurvePanel.bottom);
	pDC->MoveTo(m_rectCurvePanel.left,m_rectCurvePanel.bottom);
	pDC->LineTo(m_rectCurvePanel.right,m_rectCurvePanel.bottom);
	pDC->SelectObject(pOldPen);
}/////////////////////�ð��߹��������������Ա�Ч��
void CScope::DrawGrid(CDC *pDC)//�����߻�������
{
	CPen *pOldPen;

	pDC->FillRect(&m_rectCurve,&m_CurveBrush);//��ˢ����������

	pOldPen = pDC->SelectObject(&m_PenDarkLine);//����m_PenDarkLineΪĬ�ϻ���
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.top);
/////////////////////�ð��߹��������������Ա�Ч��
	pDC->SelectObject(&m_PenBrightLine);
	pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
/////////////////////�����߹��������������Ա�Ч��	

	int i;
	CString str;
	pDC->SelectObject(&m_PenGrid);//���õ�ǰ����Ϊm_PenGrid
	pDC->SelectClipRgn(&m_rgnCurve);//���õ�ǰĬ������Ϊm_rgnCurve
	int nCenterY  = m_rectCurve.top+(int)(m_nBase/(double)m_nRange*m_rectCurve.Height());


	int nPosY;
	//������
	for(i=0;i<32;i+=4)
	{
//		if(i==(6/2)) continue;
		nPosY = nCenterY-(i/33.0)*m_rectCurve.Height();
		if(nPosY<m_rectCurve.bottom)
		{
			pDC->MoveTo(m_rectCurve.left,nPosY);
			pDC->LineTo(m_rectCurve.right,nPosY);
		}
		nPosY = nCenterY+(i/33.0)*m_rectCurve.Height();
		if(nPosY<m_rectCurve.bottom)
		{
			pDC->MoveTo(m_rectCurve.left,nPosY);
			pDC->LineTo(m_rectCurve.right,nPosY);
		}








	}
	//������
	for(i=1;i<=10;i++)
	{
		pDC->MoveTo(m_rectCurve.left+i*m_rectCurve.Width()/10,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left+i*m_rectCurve.Width()/10,m_rectCurve.bottom);
	}
}
void CScope::DrawTrack(CDC *pDC,BOOL bPressed)//���ƻ���
{
}
void CScope::DrawAxis(CDC *pDC)//��ֵ�̶ȱ��
{
	CFont *pOldFont;
	int i,nPosY;
	CString str;
	pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(255,255,0));//����Ĭ����ɫΪ��ɫ��������ɫ��
	pDC->SetBkMode(TRANSPARENT);//����Ĭ������Ϊ͸���������ƶ�ʱ����͸����
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);//����Ĭ���ı�ģʽ���Ҷ��룬���߶��룩
	int nCenterY = m_rectCurve.top+(int)((double)m_nBase/(double)m_nRange*m_rectCurve.Height());
	nPosY = nCenterY;
	if(nPosY<=m_rectCurve.top+10)
		nPosY += 10;
	////////////////////////�趨���ȿ̶ȼ��
	if(m_dDimY<1)
		pDC->TextOut(m_rectCurve.left-2,nPosY,CString("0.0"));
	else
		pDC->TextOut(m_rectCurve.left-2,nPosY,CString("0"));
	//////////////////////�趨���ȿ̶ȵı�ʾ��ʽ

///������
	for(i=1;i<=2;i++)
	{
		nPosY = nCenterY+i*m_rectCurve.Height()/4;
		if(nPosY<=m_rectCurve.bottom)
		{
			if(m_dDimY<1)
				str.Format("%.1f",-i*2*m_dDimY);
			else if(m_dDimY<1000)
				str.Format("%.0f",-i*2*m_dDimY);
			else
				str.Format("%.0fK",-i*2*m_dDimY/1000);//��ʾ���������%.0fK�����ֵ������ʽ��0��С������λ����f�Ǳ�ʾ���Ϊ�����ͣ�k��������������ĵ�λ
			pDC->TextOut(m_rectCurve.left-2,nPosY,str);//��ʾ�̶�
		}
	}
////������
	for(i=1;i<=2;i++)
	{
		nPosY = nCenterY-i*2*m_rectCurve.Height()/8;
		if(nPosY>=m_rectCurve.top)
		{
			if(nPosY<=m_rectCurve.top+10)
				nPosY += 10;
			if(m_dDimY<1)
				str.Format("%.1f",i*2*m_dDimY);
			else if(m_dDimY<1000)
				str.Format("%.0f",i*2*m_dDimY);
			else
				str.Format("%.0fK",i*2*m_dDimY/1000);
			pDC->TextOut(m_rectCurve.left-2,nPosY,str);
		}//���ȿ̶ȵı�ʾ��ʽ
	}//////������



	//������




	pDC->SetTextAlign(TA_LEFT|TA_TOP);//����Ĭ���ı�Ϊ����룬�ö�
	pDC->TextOut(m_rectCurve.left,m_rectCurve.bottom+2,CString("0.0"));//�̶ȹ涨ԭ��
	pDC->SetTextAlign(TA_CENTER|TA_TOP);
	for(i=2;i<=9;i+=2)
	{
		str.Format("%.1f",i*m_dDimT);
		pDC->TextOut(m_rectCurve.left+i*m_rectCurve.Width()/10,m_rectCurve.bottom+2,str);
	}
	pDC->SetTextAlign(TA_RIGHT|TA_TOP);
	str.Format("%.1f",10*m_dDimT);
	pDC->TextOut(m_rectCurve.right,m_rectCurve.bottom+2,str);
	pDC->SelectObject(&pOldFont);//�ͷŵ�ǰ����
}

void CScope::OnLButtonUp(UINT nFlags, CPoint point) //��׽��굯��
{
}

void CScope::OnLButtonDown(UINT nFlags, CPoint point) //��׽���ĵ��
{
}

void CScope::OnMouseMove(UINT nFlags, CPoint point) //������ƶ��Ĳ�׽
{
}
void CScope::DrawArrow(CDC *pDC,int nIndex,BOOL bLighted)//���Ƶ���ʱ��ͷ��ȵļ�ͷ��ť
{
}
void CScope::DrawCurveA(CDC *pDC)//�������Ҳ�
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListA.size();//ָ��һ���µĳߴ�

	POINT *pPointArray =(POINT *) new POINT[nSize];//�趨һ������
	int i;
	std::list<double>::iterator time_it = m_TimeListA.begin();
	std::list<double>::iterator value_it = m_ValueListA.begin();
	std::list<double>::iterator time_begin = time_it;
//��ʱ���ʼ���ָ��Ͳ��γ�ʼ���ָ���Ӧ��������֤���κ�ʱ����ͬʱ��ʼ
	for(i=0;i<nSize;i++)
	{
		pPointArray[i].x = ConvertTimeToAxisX(*time_it-*time_begin);
		pPointArray[i].y = ConvertValueToAxisY(*value_it);
		pPointArray[i].y = pPointArray[i].y+m_Amove;
		time_it++;
		value_it++;
	}
	m_bDrawing =FALSE;
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//���õ�ǰ����Ϊm_PenCurveA
	pDC->SelectClipRgn(&m_rgnCurve);//���õ�ǰĬ������Ϊm_rgnCurve
	pDC->Polyline(pPointArray,nSize);//��ʱ�佫������ߵĵ�ȫ�����Ƴ���
	pDC->SelectClipRgn(NULL);//�ͷ�����
	pDC->SelectObject(pOldPen);//�ͷŻ���
	
	delete []pPointArray;		 
}

void CScope::DrawCurveB(CDC *pDC)//���Ʒ�������
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListB.size();//ָ��һ���µĳߴ�

	POINT *pPointArray =(POINT *) new POINT[nSize];//�趨һ������
	int i;
	
	std::list<double>::iterator time_it = m_TimeListB.begin();
	std::list<double>::iterator value_it = m_ValueListB.begin();
	std::list<double>::iterator time_begin = time_it;
	for(i=0;i<nSize;i++)
	{
		pPointArray[i].x = ConvertTimeToAxisX(*time_it-*time_begin);
		pPointArray[i].y = ConvertValueToAxisY(*value_it);
		pPointArray[i].y = pPointArray[i].y+m_Bmove;
		time_it++;
		value_it++;
	}
	m_bDrawing =FALSE;
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveB);//���õ�ǰ����Ϊm_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////���õ�ǰĬ������Ϊm_rgnCurve
	pDC->Polyline(pPointArray,nSize);//��ʱ�佫������ߵĵ�ȫ�����Ƴ���
	pDC->SelectClipRgn(NULL);//�ͷ�����
	pDC->SelectObject(pOldPen);//�ͷŻ���
	
	delete []pPointArray;		 
}

void CScope::DrawCurveC(CDC *pDC)//���Ʒ�������
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListC.size();//ָ��һ���µĳߴ�

	POINT *pPointArray =(POINT *) new POINT[nSize];//�趨һ������
	int i;
	
	std::list<double>::iterator time_it = m_TimeListC.begin();
	std::list<double>::iterator value_it = m_ValueListC.begin();
	std::list<double>::iterator time_begin = time_it;
	for(i=0;i<nSize;i++)
	{
		pPointArray[i].x = ConvertTimeToAxisX(*time_it-*time_begin);
		pPointArray[i].y = ConvertValueToAxisY(*value_it);
		pPointArray[i].y = pPointArray[i].y+m_Cmove;
		time_it++;
		value_it++;
	}
	m_bDrawing =FALSE;
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveC);//���õ�ǰ����Ϊm_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////���õ�ǰĬ������Ϊm_rgnCurve
	pDC->Polyline(pPointArray,nSize);//��ʱ�佫������ߵĵ�ȫ�����Ƴ���
	pDC->SelectClipRgn(NULL);//�ͷ�����
	pDC->SelectObject(pOldPen);//�ͷŻ���
	
	delete []pPointArray;		 
}

void CScope::DrawCurveD(CDC *pDC)//���Ʒ�������
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListD.size();//ָ��һ���µĳߴ�

	POINT *pPointArray =(POINT *) new POINT[nSize];//�趨һ������
	int i;
	
	std::list<double>::iterator time_it = m_TimeListD.begin();
	std::list<double>::iterator value_it = m_ValueListD.begin();
	std::list<double>::iterator time_begin = time_it;
	for(i=0;i<nSize;i++)
	{
		pPointArray[i].x = ConvertTimeToAxisX(*time_it-*time_begin);
		pPointArray[i].y = ConvertValueToAxisY(*value_it);
		pPointArray[i].y = pPointArray[i].y+m_Dmove;
		time_it++;
		value_it++;
	}
	m_bDrawing =FALSE;
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveD);//���õ�ǰ����Ϊm_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////���õ�ǰĬ������Ϊm_rgnCurve
	pDC->Polyline(pPointArray,nSize);//��ʱ�佫������ߵĵ�ȫ�����Ƴ���
	pDC->SelectClipRgn(NULL);//�ͷ�����
	pDC->SelectObject(pOldPen);//�ͷŻ���
	
	delete []pPointArray;		 
}


void CScope::DrawCurveE(CDC *pDC)//���Ʒ�������
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListE.size();//ָ��һ���µĳߴ�

	POINT *pPointArray =(POINT *) new POINT[nSize];//�趨һ������
	int i;
	
	std::list<double>::iterator time_it = m_TimeListE.begin();
	std::list<double>::iterator value_it = m_ValueListE.begin();
	std::list<double>::iterator time_begin = time_it;
	for(i=0;i<nSize;i++)
	{
		pPointArray[i].x = ConvertTimeToAxisX(*time_it-*time_begin);
		pPointArray[i].y = ConvertValueToAxisY(*value_it);
		pPointArray[i].y = pPointArray[i].y+m_Emove;
		time_it++;
		value_it++;
	}
	m_bDrawing =FALSE;
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveE);//���õ�ǰ����Ϊm_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////���õ�ǰĬ������Ϊm_rgnCurve
	pDC->Polyline(pPointArray,nSize);//��ʱ�佫������ߵĵ�ȫ�����Ƴ���
	pDC->SelectClipRgn(NULL);//�ͷ�����
	pDC->SelectObject(pOldPen);//�ͷŻ���
	
	delete []pPointArray;		 
}


void CScope::DrawCurveF(CDC *pDC)//���Ʒ�������
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListF.size();//ָ��һ���µĳߴ�

	POINT *pPointArray =(POINT *) new POINT[nSize];//�趨һ������
	int i;
	
	std::list<double>::iterator time_it = m_TimeListF.begin();
	std::list<double>::iterator value_it = m_ValueListF.begin();
	std::list<double>::iterator time_begin = time_it;
	for(i=0;i<nSize;i++)
	{
		pPointArray[i].x = ConvertTimeToAxisX(*time_it-*time_begin);
		pPointArray[i].y = ConvertValueToAxisY(*value_it);
		pPointArray[i].y = pPointArray[i].y+m_Fmove;
		time_it++;
		value_it++;
	}
	m_bDrawing =FALSE;
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveF);//���õ�ǰ����Ϊm_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////���õ�ǰĬ������Ϊm_rgnCurve
	pDC->Polyline(pPointArray,nSize);//��ʱ�佫������ߵĵ�ȫ�����Ƴ���
	pDC->SelectClipRgn(NULL);//�ͷ�����
	pDC->SelectObject(pOldPen);//�ͷŻ���
	
	delete []pPointArray;		 
}


























void CScope::UpdateCurve()//ʹ���ߵĲ�ͣˢ��
{
		
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//��ȡ�ͻ�����
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);//����ǰ��������Ϊλͼ����memDC��
	CBitmap bitmap,*pOldBmp;
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());//����λͼ&dc����ʼ������
	pOldBmp = memDC.SelectObject(&bitmap);//��λͼbitmap���ݸ�memDC
	DrawGrid(&memDC);//���û�������

	DrawCurveA(&memDC);//�������Ҳ�����
	DrawCurveB(&memDC);//���Ʒ�������
	DrawCurveC(&memDC);//�������Ҳ�����
	DrawCurveD(&memDC);//���Ʒ�������
	DrawCurveE(&memDC);//�������Ҳ�����
	DrawCurveF(&memDC);//���Ʒ�������


	dc.BitBlt(m_rectCurve.left,m_rectCurve.top,m_rectCurve.Width(),m_rectCurve.Height(),&memDC,m_rectCurve.left,m_rectCurve.top,SRCCOPY);//��λͼ���Ƶ�dc��
	memDC.SelectObject(pOldBmp);//�ͷŵ�ǰλͼ	

}

LRESULT CScope::OnNcHitTest(CPoint point) //�����ѡ��
{
	// TODO: Add your message handler code here and/or call default	
	return HTCLIENT;
}
void CScope::AddValueA(double dTime,double dValue)//��ʱ��ı仯�������Ҳ���ĩ�˵�
{
	if(m_bDrawing)
		return;

	m_TimeListA.push_back(dTime);//�����Ҳ�ĩ������һ����ĺ�����
	m_ValueListA.push_back(dValue);//�����Ҳ�ĩ������һ�����������

	std::list<double>::iterator start_it = m_TimeListA.begin();
	std::list<double>::iterator end_it = m_TimeListA.end();
	end_it--;//��ʱ�亯�������Ʋ��εı仯
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>20*m_dDimT)
	{
		m_TimeListA.pop_front();//�����Ҳ�ǰ��ɾ��һ����ĺ�����
		m_ValueListA.pop_front();//�����Ҳ�ǰ��ɾ��һ�����������
		
		start_it = m_TimeListA.begin();//�������Ҳ�ǰ�˵�ַ��start_it
		end_it = m_TimeListA.end();//�������Ҳ�ĩ�˵�ַ��end_it
		end_it--;

		dStartTime = *start_it;//��ָ�������һλ
		dEndTime = *(end_it);//βָ�������һλ
	}
}
void CScope::AddValueB(double dTime,double dValue)//��ʱ��ı仯���ӷ�����ĩ�˵�
{
	if(m_bDrawing)
		return;

	m_TimeListB.push_back(dTime);//�ڷ���ĩ������һ����ĺ�����
	m_ValueListB.push_back(dValue);//�ڷ���ĩ������һ�����������
	std::list<double>::iterator start_it = m_TimeListB.begin();
	std::list<double>::iterator end_it = m_TimeListB.end();
	end_it--;//��ʱ�亯�������Ʋ��εı仯
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListB.pop_front();//�ڷ���ǰ��ɾ��һ����ĺ�����
		m_ValueListB.pop_front();//�ڷ���ǰ��ɾ��һ�����������
		
		start_it = m_TimeListB.begin();//���ط���ǰ�˵�ַ��start_it
		end_it = m_TimeListB.end();//���ط���ĩ�˵�ַ��end_it
		end_it--;

		dStartTime = *start_it;//��ָ�������һλ
		dEndTime = *(end_it);//βָ�������һλ
	}
}

void CScope::AddValueC(double dTime,double dValue)//��ʱ��ı仯���ӷ�����ĩ�˵�
{
	if(m_bDrawing)
		return;

	m_TimeListC.push_back(dTime);//�ڷ���ĩ������һ����ĺ�����
	m_ValueListC.push_back(dValue);//�ڷ���ĩ������һ�����������
	std::list<double>::iterator start_it = m_TimeListC.begin();
	std::list<double>::iterator end_it = m_TimeListC.end();
	end_it--;//��ʱ�亯�������Ʋ��εı仯
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListC.pop_front();//�ڷ���ǰ��ɾ��һ����ĺ�����
		m_ValueListC.pop_front();//�ڷ���ǰ��ɾ��һ�����������
		
		start_it = m_TimeListC.begin();//���ط���ǰ�˵�ַ��start_it
		end_it = m_TimeListC.end();//���ط���ĩ�˵�ַ��end_it
		end_it--;

		dStartTime = *start_it;//��ָ�������һλ
		dEndTime = *(end_it);//βָ�������һλ
	}
}

void CScope::AddValueD(double dTime,double dValue)//��ʱ��ı仯���ӷ�����ĩ�˵�
{
	if(m_bDrawing)
		return;

	m_TimeListD.push_back(dTime);//�ڷ���ĩ������һ����ĺ�����
	m_ValueListD.push_back(dValue);//�ڷ���ĩ������һ�����������
	std::list<double>::iterator start_it = m_TimeListD.begin();
	std::list<double>::iterator end_it = m_TimeListD.end();
	end_it--;//��ʱ�亯�������Ʋ��εı仯
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListD.pop_front();//�ڷ���ǰ��ɾ��һ����ĺ�����
		m_ValueListD.pop_front();//�ڷ���ǰ��ɾ��һ�����������
		
		start_it = m_TimeListD.begin();//���ط���ǰ�˵�ַ��start_it
		end_it = m_TimeListD.end();//���ط���ĩ�˵�ַ��end_it
		end_it--;

		dStartTime = *start_it;//��ָ�������һλ
		dEndTime = *(end_it);//βָ�������һλ
	}
}


void CScope::AddValueE(double dTime,double dValue)//��ʱ��ı仯���ӷ�����ĩ�˵�
{
	if(m_bDrawing)
		return;

	m_TimeListE.push_back(dTime);//�ڷ���ĩ������һ����ĺ�����
	m_ValueListE.push_back(dValue);//�ڷ���ĩ������һ�����������
	std::list<double>::iterator start_it = m_TimeListE.begin();
	std::list<double>::iterator end_it = m_TimeListE.end();
	end_it--;//��ʱ�亯�������Ʋ��εı仯
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListE.pop_front();//�ڷ���ǰ��ɾ��һ����ĺ�����
		m_ValueListE.pop_front();//�ڷ���ǰ��ɾ��һ�����������
		
		start_it = m_TimeListE.begin();//���ط���ǰ�˵�ַ��start_it
		end_it = m_TimeListE.end();//���ط���ĩ�˵�ַ��end_it
		end_it--;

		dStartTime = *start_it;//��ָ�������һλ
		dEndTime = *(end_it);//βָ�������һλ
	}
}


void CScope::AddValueF(double dTime,double dValue)//��ʱ��ı仯���ӷ�����ĩ�˵�
{
	if(m_bDrawing)
		return;

	m_TimeListF.push_back(dTime);//�ڷ���ĩ������һ����ĺ�����
	m_ValueListF.push_back(dValue);//�ڷ���ĩ������һ�����������
	std::list<double>::iterator start_it = m_TimeListF.begin();
	std::list<double>::iterator end_it = m_TimeListF.end();
	end_it--;//��ʱ�亯�������Ʋ��εı仯
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListF.pop_front();//�ڷ���ǰ��ɾ��һ����ĺ�����
		m_ValueListF.pop_front();//�ڷ���ǰ��ɾ��һ�����������
		
		start_it = m_TimeListF.begin();//���ط���ǰ�˵�ַ��start_it
		end_it = m_TimeListF.end();//���ط���ĩ�˵�ַ��end_it
		end_it--;

		dStartTime = *start_it;//��ָ�������һλ
		dEndTime = *(end_it);//βָ�������һλ
	}
}


inline int CScope::ConvertTimeToAxisX(double dTime)//��ʱ������Ӳ�ͣ�Ļ��Ʋ��εĺ����꣨ʱ�����ӣ�
{
	int nReturn;
	nReturn = m_rectCurve.left+dTime/(10.0*m_dDimT)*m_rectCurve.Width();
	return nReturn;
}
inline int CScope::ConvertValueToAxisY(double dValue)//��ʱ������Ӳ�ͣ�Ļ��Ʋ��ε������꣨�������ӣ�
{
	int nReturn;
	int nCenterY  = m_rectCurve.top+(int)(m_nBase/(double)m_nRange*m_rectCurve.Height());

	nReturn = nCenterY - dValue/(8.0*m_dDimY)*m_rectCurve.Height();
	return nReturn;
}
void CScope::SetValueString(CString strTitle,CString strUnit)//���ֵĸ��ģ����ڶ�Ӧ��ͬ���εĵ�λ��Ĭ��Ϊ�ȣ�
{
}
void CScope::Clear()//�ֱ�ɾ�����������Ҳ���غ������ͷ��ڴ�
{
	m_TimeListA.clear();
	m_ValueListA.clear();
	m_TimeListB.clear();
	m_ValueListB.clear();
	m_TimeListC.clear();
	m_ValueListC.clear();
	m_TimeListD.clear();
	m_ValueListD.clear();
	m_TimeListE.clear();
	m_ValueListE.clear();
	m_TimeListF.clear();
	m_ValueListF.clear();

	UpdateCurve();
	SetValueA(0.0);
	SetValueB(0.0);
	SetValueC(0.0);
	SetValueD(0.0);
	SetValueE(0.0);
	SetValueF(0.0);

}

void CScope::Button( int i )
{
	switch(i)
	{
	case 0:
		{
		if(m_dDimY>=1&&m_dDimY<10)
			m_dDimY+=1;
		if(m_dDimY>=10&&m_dDimY<100)
			m_dDimY+=10;
		if(m_dDimY>=100&&m_dDimY<1000)
			m_dDimY+=100;
		if(m_dDimY>=1000)
			m_dDimY+=1000;
		else if(m_dDimY>=0&&m_dDimY<1)
			m_dDimY+=0.1;
        break;
		}
	case 1:
		{
		if(m_dDimY>1&&m_dDimY<=10)
			m_dDimY-=1;
		if(m_dDimY>10&&m_dDimY<=100)
			m_dDimY-=10;
		if(m_dDimY>100&&m_dDimY<=1000)
			m_dDimY-=100;
		if(m_dDimY>1000)
			m_dDimY-=1000;
		if(m_dDimY<=1)
			m_dDimY=max(m_dDimY-0.1,0.1);
		break;
		}
	case 2:
		{
		m_dDimT+=0.1;
		break;
		}
	case 3:
		{
		m_dDimT=max(m_dDimT-0.1,0.1); 
        break;
		}
	case 4:
		{
		if (m_Amove>-60)
		m_Amove=m_Amove-10;
        break;
		}
	case 5:
		{	
		if (m_Amove<60)
		m_Amove=m_Amove+10;
        break;
		}
	case 6:
		{
		if (m_Bmove>-60)
		m_Bmove=m_Bmove-10;
        break;
		}
	case 7:
		{
		if (m_Bmove<60)
		m_Bmove=m_Bmove+10;
        break;
		}
	default:
		break;
	}	
	Invalidate();
}


void CScope::ClearA()
{
	m_TimeListA.clear();
	m_ValueListA.clear();
	UpdateCurve();
	SetValueA(0.0);

}

void CScope::ClearB()
{
	m_TimeListB.clear();
	m_ValueListB.clear();
	UpdateCurve();
	SetValueB(0.0);
}

void CScope::ClearC()
{
	m_TimeListC.clear();
	m_ValueListC.clear();
	UpdateCurve();
	SetValueC(0.0);

}

void CScope::ClearD()
{
	m_TimeListD.clear();
	m_ValueListD.clear();
	UpdateCurve();
	SetValueD(0.0);
}

void CScope::ClearE()
{
	m_TimeListE.clear();
	m_ValueListE.clear();
	UpdateCurve();
	SetValueE(0.0);
}

void CScope::ClearF()
{
	m_TimeListF.clear();
	m_ValueListF.clear();
	UpdateCurve();
	SetValueF(0.0);
}