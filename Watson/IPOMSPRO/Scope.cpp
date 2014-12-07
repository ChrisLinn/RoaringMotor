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

CScope::CScope()//程序初始化数据
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
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"宋体");
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

CScope::~CScope()//程序结束时释放内存空间
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


BEGIN_MESSAGE_MAP(CScope, CStatic)//Windows的映射
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

BOOL CScope::OnEraseBkgnd(CDC* pDC) //绘制整个背景面板
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;

	GetClientRect(&rect);//获取用户区域
	rect.InflateRect(-0.5,-0.5,-3,-3);//curve panel////curve panel确定一个区域（凸起的部分）的大小和位置，离总区域的距离分别为左、上、右、下
	m_rectCurvePanel = rect;//确定曲线面板
	m_rectCurve = rect;//显示曲线、滑块和按钮
	m_rectCurve.InflateRect(-35,-5,-10,-20);//curve area确定黑色网格的总区域的大小

	m_rectValuePanel = rect;//显示数值面板区域
	m_rectValuePanel.top = rect.bottom+5;//确定数值面板的上端位置（以曲线面板为参照）
	m_rectValuePanel.bottom= m_rectValuePanel.top+51;//rectValuePanel created确定数值面板的下端位置（以自己的上端为参照）

	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&m_FontLabel);
	CSize size = pDC->GetTextExtent(m_strValueName);//获取文本所占区域的大小
	m_rectValue.left = m_rectValuePanel.left+20+size.cx;//确定数值框的左端位置，cx为文本横向宽度（以数值面板左端为参照）
	m_rectValue.top = m_rectValuePanel.top+(m_rectValuePanel.Height()-size.cy)/2-2;//确定数值框的上端位置
	m_rectValue.bottom = m_rectValue.top+size.cy+4;//确定数值框的下端位置，cy为文本纵向宽度
	size = pDC->GetTextExtent(m_strUnitName);
	m_rectValue.right = m_rectValuePanel.right - 20 - size.cx;//确定数值框的右端位置（以数值面板右端为参照为参照）
	pDC->SelectObject(pOldFont);//释放当前字体
///////////////////////////////////////////////确定相对坐标位移时，原点在屏幕的左上角

	if(m_rgnCurve.m_hObject==NULL)
		m_rgnCurve.CreateRectRgn(m_rectCurve.left+2,m_rectCurve.top+2,m_rectCurve.right-2,m_rectCurve.bottom-2);

/*	POINT ptYPlus[3];//幅度增加按钮
	POINT ptYMinus[3];//幅度减少按钮
	POINT ptTPlus[3];//时间增加按钮
	POINT ptTMinus[3];//时间减少按钮
	ptYPlus[0].x = m_rectCurvePanel.left+15;//确定幅度增加按钮的上端点的水平位置
	ptYPlus[0].y = m_rectCurve.bottom+3;//确定幅度增加按钮的上端点的垂直位置
	ptYPlus[1].x = ptYPlus[0].x-5;//确定幅度增加按钮的左端点的水平位置
	ptYPlus[1].y = ptYPlus[0].y+6;//确定幅度增加按钮的左端点的垂直位置
	ptYPlus[2].x = ptYPlus[0].x+5;//确定幅度增加按钮的右端点的水平位置
	ptYPlus[2].y = ptYPlus[0].y+6;//确定幅度增加按钮的右端点的垂直位置

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

void CScope::OnPaint() //静态面板以及该面板上所有控件的绘制
{
	CPaintDC dc(this); 
	DrawCurvePanel(&dc);//显示曲线面板
	DrawGrid(&dc);//出现绘制网格

	DrawCurveA(&dc);//绘制正弦波
	DrawCurveB(&dc);//绘制方波
	DrawCurveC(&dc);//绘制正弦波
	DrawCurveD(&dc);//绘制方波
	DrawCurveE(&dc);//绘制正弦波
	DrawCurveF(&dc);//绘制方波
	DrawAxis(&dc);//绘制刻度
}
void CScope::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CStatic::PreSubclassWindow();
}
void CScope::DrawTitle(CDC *pDC)//绘制标题栏
{
}
void CScope::SetTitle(CString strTitle)//输出大标题文字
{	
}
void CScope::DrawValuePanel(CDC *pDC)//绘制数值面板（波形下端的立体窗口以及上面的文字）
{
}

void CScope::DrawValueA(CDC *pDC)//产生一个文本框，并且在框内显示出数字
{
}

void CScope::SetValueA(double dValue)//在对话框中产生一个从-4到4变化的数值
{
}

void CScope::SetValueB(double dValue)//在对话框中产生一个从-4到4变化的数值（没必要弄两个）
{
}

void CScope::SetValueC(double dValue)//在对话框中产生一个从-4到4变化的数值
{
}

void CScope::SetValueD(double dValue)//在对话框中产生一个从-4到4变化的数值（没必要弄两个）
{
}

void CScope::SetValueE(double dValue)//在对话框中产生一个从-4到4变化的数值（没必要弄两个）
{
}
void CScope::SetValueF(double dValue)//在对话框中产生一个从-4到4变化的数值（没必要弄两个）
{
}

void CScope::SetDimT(double DimT)//与外部相连函数
{
/*	if(m_dDimT==DimT/10)
	{
		return;
	}
	else
	{
		m_dDimT = DimT/10;
		Invalidate();//重画画面进行刷新
	}*/
}
void CScope::SetDimy(double newDimY)//与外部相连函数
{
/*
	if(m_dDimY==newDimY)	
	{

		return;
	}
	else
	{
		m_dDimY = newDimY;
		Invalidate();//重画画面进行刷新
	}*/
}
void CScope::SetBase(int nNewABase,int nRange)//与外部相连函数
{
}


void CScope::DrawCurvePanel(CDC *pDC)//对整体面板进行填充，并增加面板立体效果
{
	CPen *pOldPen;
	pDC->FillRect(&m_rectCurvePanel,&m_PanelBrush);//用深蓝色填充曲线面板

	pOldPen = pDC->SelectObject(&m_PenBrightLine);//设置当前默认画笔为m_PenBrightLine
	pDC->MoveTo(m_rectCurvePanel.left,m_rectCurvePanel.top);
	pDC->LineTo(m_rectCurvePanel.left,m_rectCurvePanel.bottom);
	pDC->MoveTo(m_rectCurvePanel.left,m_rectCurvePanel.top);
	pDC->LineTo(m_rectCurvePanel.right,m_rectCurvePanel.top);
/////////////////////用明线勾画出面板的明暗对比效果
	pDC->SelectObject(&m_PenDarkLine);//设置当前默认画笔为m_PenDarkLine
	pDC->MoveTo(m_rectCurvePanel.right,m_rectCurvePanel.top);
	pDC->LineTo(m_rectCurvePanel.right,m_rectCurvePanel.bottom);
	pDC->MoveTo(m_rectCurvePanel.left,m_rectCurvePanel.bottom);
	pDC->LineTo(m_rectCurvePanel.right,m_rectCurvePanel.bottom);
	pDC->SelectObject(pOldPen);
}/////////////////////用暗线勾画出面板的明暗对比效果
void CScope::DrawGrid(CDC *pDC)//用明线绘制网格
{
	CPen *pOldPen;

	pDC->FillRect(&m_rectCurve,&m_CurveBrush);//画刷填充曲线面板

	pOldPen = pDC->SelectObject(&m_PenDarkLine);//设置m_PenDarkLine为默认画笔
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.top);
/////////////////////用暗线勾画出面板的明暗对比效果
	pDC->SelectObject(&m_PenBrightLine);
	pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
	pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
	pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
/////////////////////用明线勾画出面板的明暗对比效果	

	int i;
	CString str;
	pDC->SelectObject(&m_PenGrid);//设置当前画笔为m_PenGrid
	pDC->SelectClipRgn(&m_rgnCurve);//设置当前默认区域为m_rgnCurve
	int nCenterY  = m_rectCurve.top+(int)(m_nBase/(double)m_nRange*m_rectCurve.Height());


	int nPosY;
	//画横线
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
	//画竖线
	for(i=1;i<=10;i++)
	{
		pDC->MoveTo(m_rectCurve.left+i*m_rectCurve.Width()/10,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left+i*m_rectCurve.Width()/10,m_rectCurve.bottom);
	}
}
void CScope::DrawTrack(CDC *pDC,BOOL bPressed)//绘制滑块
{
}
void CScope::DrawAxis(CDC *pDC)//数值刻度标记
{
	CFont *pOldFont;
	int i,nPosY;
	CString str;
	pOldFont = pDC->SelectObject(&m_FontAxis);//设置当前字体默认为Axis（数字字体）
	pDC->SetTextColor(RGB(255,255,0));//设置默认颜色为黄色（数字颜色）
	pDC->SetBkMode(TRANSPARENT);//设置默认输入为透明（滑块移动时数字透明）
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);//设置默认文本模式（右对齐，基线对齐）
	int nCenterY = m_rectCurve.top+(int)((double)m_nBase/(double)m_nRange*m_rectCurve.Height());
	nPosY = nCenterY;
	if(nPosY<=m_rectCurve.top+10)
		nPosY += 10;
	////////////////////////设定幅度刻度间隔
	if(m_dDimY<1)
		pDC->TextOut(m_rectCurve.left-2,nPosY,CString("0.0"));
	else
		pDC->TextOut(m_rectCurve.left-2,nPosY,CString("0"));
	//////////////////////设定幅度刻度的表示形式

///纵坐标
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
				str.Format("%.0fK",-i*2*m_dDimY/1000);//表示数字输出，%.0fK是数字的输出形式，0是小数点后的位数，f是表示输出为浮点型，k是输出数字所带的单位
			pDC->TextOut(m_rectCurve.left-2,nPosY,str);//显示刻度
		}
	}
////负半轴
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
		}//幅度刻度的表示形式
	}//////正半轴



	//横坐标




	pDC->SetTextAlign(TA_LEFT|TA_TOP);//设置默认文本为左对齐，置顶
	pDC->TextOut(m_rectCurve.left,m_rectCurve.bottom+2,CString("0.0"));//刻度规定原点
	pDC->SetTextAlign(TA_CENTER|TA_TOP);
	for(i=2;i<=9;i+=2)
	{
		str.Format("%.1f",i*m_dDimT);
		pDC->TextOut(m_rectCurve.left+i*m_rectCurve.Width()/10,m_rectCurve.bottom+2,str);
	}
	pDC->SetTextAlign(TA_RIGHT|TA_TOP);
	str.Format("%.1f",10*m_dDimT);
	pDC->TextOut(m_rectCurve.right,m_rectCurve.bottom+2,str);
	pDC->SelectObject(&pOldFont);//释放当前字体
}

void CScope::OnLButtonUp(UINT nFlags, CPoint point) //捕捉鼠标弹起
{
}

void CScope::OnLButtonDown(UINT nFlags, CPoint point) //捕捉鼠标的点击
{
}

void CScope::OnMouseMove(UINT nFlags, CPoint point) //对鼠标移动的捕捉
{
}
void CScope::DrawArrow(CDC *pDC,int nIndex,BOOL bLighted)//绘制调节时间和幅度的箭头按钮
{
}
void CScope::DrawCurveA(CDC *pDC)//绘制正弦波
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListA.size();//指定一个新的尺寸

	POINT *pPointArray =(POINT *) new POINT[nSize];//设定一个数组
	int i;
	std::list<double>::iterator time_it = m_TimeListA.begin();
	std::list<double>::iterator value_it = m_ValueListA.begin();
	std::list<double>::iterator time_begin = time_it;
//将时间初始点的指针和波形初始点的指针对应起来，保证波形和时间能同时开始
	for(i=0;i<nSize;i++)
	{
		pPointArray[i].x = ConvertTimeToAxisX(*time_it-*time_begin);
		pPointArray[i].y = ConvertValueToAxisY(*value_it);
		pPointArray[i].y = pPointArray[i].y+m_Amove;
		time_it++;
		value_it++;
	}
	m_bDrawing =FALSE;
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//设置当前画笔为m_PenCurveA
	pDC->SelectClipRgn(&m_rgnCurve);//设置当前默认区域为m_rgnCurve
	pDC->Polyline(pPointArray,nSize);//随时间将组成曲线的点全部绘制出来
	pDC->SelectClipRgn(NULL);//释放区域
	pDC->SelectObject(pOldPen);//释放画笔
	
	delete []pPointArray;		 
}

void CScope::DrawCurveB(CDC *pDC)//绘制方波曲线
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListB.size();//指定一个新的尺寸

	POINT *pPointArray =(POINT *) new POINT[nSize];//设定一个数组
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
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveB);//设置当前画笔为m_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////设置当前默认区域为m_rgnCurve
	pDC->Polyline(pPointArray,nSize);//随时间将组成曲线的点全部绘制出来
	pDC->SelectClipRgn(NULL);//释放区域
	pDC->SelectObject(pOldPen);//释放画笔
	
	delete []pPointArray;		 
}

void CScope::DrawCurveC(CDC *pDC)//绘制方波曲线
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListC.size();//指定一个新的尺寸

	POINT *pPointArray =(POINT *) new POINT[nSize];//设定一个数组
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
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveC);//设置当前画笔为m_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////设置当前默认区域为m_rgnCurve
	pDC->Polyline(pPointArray,nSize);//随时间将组成曲线的点全部绘制出来
	pDC->SelectClipRgn(NULL);//释放区域
	pDC->SelectObject(pOldPen);//释放画笔
	
	delete []pPointArray;		 
}

void CScope::DrawCurveD(CDC *pDC)//绘制方波曲线
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListD.size();//指定一个新的尺寸

	POINT *pPointArray =(POINT *) new POINT[nSize];//设定一个数组
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
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveD);//设置当前画笔为m_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////设置当前默认区域为m_rgnCurve
	pDC->Polyline(pPointArray,nSize);//随时间将组成曲线的点全部绘制出来
	pDC->SelectClipRgn(NULL);//释放区域
	pDC->SelectObject(pOldPen);//释放画笔
	
	delete []pPointArray;		 
}


void CScope::DrawCurveE(CDC *pDC)//绘制方波曲线
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListE.size();//指定一个新的尺寸

	POINT *pPointArray =(POINT *) new POINT[nSize];//设定一个数组
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
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveE);//设置当前画笔为m_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////设置当前默认区域为m_rgnCurve
	pDC->Polyline(pPointArray,nSize);//随时间将组成曲线的点全部绘制出来
	pDC->SelectClipRgn(NULL);//释放区域
	pDC->SelectObject(pOldPen);//释放画笔
	
	delete []pPointArray;		 
}


void CScope::DrawCurveF(CDC *pDC)//绘制方波曲线
{
	m_bDrawing = TRUE;
	int nSize = m_TimeListF.size();//指定一个新的尺寸

	POINT *pPointArray =(POINT *) new POINT[nSize];//设定一个数组
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
	CPen *pOldPen = pDC->SelectObject(&m_PenCurveF);//设置当前画笔为m_PenCurveB
	pDC->SelectClipRgn(&m_rgnCurve);////设置当前默认区域为m_rgnCurve
	pDC->Polyline(pPointArray,nSize);//随时间将组成曲线的点全部绘制出来
	pDC->SelectClipRgn(NULL);//释放区域
	pDC->SelectObject(pOldPen);//释放画笔
	
	delete []pPointArray;		 
}


























void CScope::UpdateCurve()//使曲线的不停刷新
{
		
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//获取客户区域
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);//将当前的曲线作为位图存入memDC中
	CBitmap bitmap,*pOldBmp;
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());//调入位图&dc并初始化界面
	pOldBmp = memDC.SelectObject(&bitmap);//将位图bitmap传递给memDC
	DrawGrid(&memDC);//调用绘制网格

	DrawCurveA(&memDC);//绘制正弦波曲线
	DrawCurveB(&memDC);//绘制方波曲线
	DrawCurveC(&memDC);//绘制正弦波曲线
	DrawCurveD(&memDC);//绘制方波曲线
	DrawCurveE(&memDC);//绘制正弦波曲线
	DrawCurveF(&memDC);//绘制方波曲线


	dc.BitBlt(m_rectCurve.left,m_rectCurve.top,m_rectCurve.Width(),m_rectCurve.Height(),&memDC,m_rectCurve.left,m_rectCurve.top,SRCCOPY);//将位图复制到dc中
	memDC.SelectObject(pOldBmp);//释放当前位图	

}

LRESULT CScope::OnNcHitTest(CPoint point) //滑块的选中
{
	// TODO: Add your message handler code here and/or call default	
	return HTCLIENT;
}
void CScope::AddValueA(double dTime,double dValue)//随时间的变化增加正弦波的末端点
{
	if(m_bDrawing)
		return;

	m_TimeListA.push_back(dTime);//在正弦波末端增加一个点的横坐标
	m_ValueListA.push_back(dValue);//在正弦波末端增加一个点的纵坐标

	std::list<double>::iterator start_it = m_TimeListA.begin();
	std::list<double>::iterator end_it = m_TimeListA.end();
	end_it--;//用时间函数来控制波形的变化
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>20*m_dDimT)
	{
		m_TimeListA.pop_front();//在正弦波前端删除一个点的横坐标
		m_ValueListA.pop_front();//在正弦波前端删除一个点的纵坐标
		
		start_it = m_TimeListA.begin();//返回正弦波前端地址给start_it
		end_it = m_TimeListA.end();//返回正弦波末端地址给end_it
		end_it--;

		dStartTime = *start_it;//首指针向后移一位
		dEndTime = *(end_it);//尾指针向后移一位
	}
}
void CScope::AddValueB(double dTime,double dValue)//随时间的变化增加方波的末端点
{
	if(m_bDrawing)
		return;

	m_TimeListB.push_back(dTime);//在方波末端增加一个点的横坐标
	m_ValueListB.push_back(dValue);//在方波末端增加一个点的纵坐标
	std::list<double>::iterator start_it = m_TimeListB.begin();
	std::list<double>::iterator end_it = m_TimeListB.end();
	end_it--;//用时间函数来控制波形的变化
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListB.pop_front();//在方波前端删除一个点的横坐标
		m_ValueListB.pop_front();//在方波前端删除一个点的纵坐标
		
		start_it = m_TimeListB.begin();//返回方波前端地址给start_it
		end_it = m_TimeListB.end();//返回方波末端地址给end_it
		end_it--;

		dStartTime = *start_it;//首指针向后移一位
		dEndTime = *(end_it);//尾指针向后移一位
	}
}

void CScope::AddValueC(double dTime,double dValue)//随时间的变化增加方波的末端点
{
	if(m_bDrawing)
		return;

	m_TimeListC.push_back(dTime);//在方波末端增加一个点的横坐标
	m_ValueListC.push_back(dValue);//在方波末端增加一个点的纵坐标
	std::list<double>::iterator start_it = m_TimeListC.begin();
	std::list<double>::iterator end_it = m_TimeListC.end();
	end_it--;//用时间函数来控制波形的变化
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListC.pop_front();//在方波前端删除一个点的横坐标
		m_ValueListC.pop_front();//在方波前端删除一个点的纵坐标
		
		start_it = m_TimeListC.begin();//返回方波前端地址给start_it
		end_it = m_TimeListC.end();//返回方波末端地址给end_it
		end_it--;

		dStartTime = *start_it;//首指针向后移一位
		dEndTime = *(end_it);//尾指针向后移一位
	}
}

void CScope::AddValueD(double dTime,double dValue)//随时间的变化增加方波的末端点
{
	if(m_bDrawing)
		return;

	m_TimeListD.push_back(dTime);//在方波末端增加一个点的横坐标
	m_ValueListD.push_back(dValue);//在方波末端增加一个点的纵坐标
	std::list<double>::iterator start_it = m_TimeListD.begin();
	std::list<double>::iterator end_it = m_TimeListD.end();
	end_it--;//用时间函数来控制波形的变化
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListD.pop_front();//在方波前端删除一个点的横坐标
		m_ValueListD.pop_front();//在方波前端删除一个点的纵坐标
		
		start_it = m_TimeListD.begin();//返回方波前端地址给start_it
		end_it = m_TimeListD.end();//返回方波末端地址给end_it
		end_it--;

		dStartTime = *start_it;//首指针向后移一位
		dEndTime = *(end_it);//尾指针向后移一位
	}
}


void CScope::AddValueE(double dTime,double dValue)//随时间的变化增加方波的末端点
{
	if(m_bDrawing)
		return;

	m_TimeListE.push_back(dTime);//在方波末端增加一个点的横坐标
	m_ValueListE.push_back(dValue);//在方波末端增加一个点的纵坐标
	std::list<double>::iterator start_it = m_TimeListE.begin();
	std::list<double>::iterator end_it = m_TimeListE.end();
	end_it--;//用时间函数来控制波形的变化
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListE.pop_front();//在方波前端删除一个点的横坐标
		m_ValueListE.pop_front();//在方波前端删除一个点的纵坐标
		
		start_it = m_TimeListE.begin();//返回方波前端地址给start_it
		end_it = m_TimeListE.end();//返回方波末端地址给end_it
		end_it--;

		dStartTime = *start_it;//首指针向后移一位
		dEndTime = *(end_it);//尾指针向后移一位
	}
}


void CScope::AddValueF(double dTime,double dValue)//随时间的变化增加方波的末端点
{
	if(m_bDrawing)
		return;

	m_TimeListF.push_back(dTime);//在方波末端增加一个点的横坐标
	m_ValueListF.push_back(dValue);//在方波末端增加一个点的纵坐标
	std::list<double>::iterator start_it = m_TimeListF.begin();
	std::list<double>::iterator end_it = m_TimeListF.end();
	end_it--;//用时间函数来控制波形的变化
	double dStartTime = *start_it;
	double dEndTime = *(end_it);
	while(dEndTime-dStartTime>10*m_dDimT)
	{
		m_TimeListF.pop_front();//在方波前端删除一个点的横坐标
		m_ValueListF.pop_front();//在方波前端删除一个点的纵坐标
		
		start_it = m_TimeListF.begin();//返回方波前端地址给start_it
		end_it = m_TimeListF.end();//返回方波末端地址给end_it
		end_it--;

		dStartTime = *start_it;//首指针向后移一位
		dEndTime = *(end_it);//尾指针向后移一位
	}
}


inline int CScope::ConvertTimeToAxisX(double dTime)//随时间的增加不停的绘制波形的横坐标（时间增加）
{
	int nReturn;
	nReturn = m_rectCurve.left+dTime/(10.0*m_dDimT)*m_rectCurve.Width();
	return nReturn;
}
inline int CScope::ConvertValueToAxisY(double dValue)//随时间的增加不停的绘制波形的纵坐标（幅度增加）
{
	int nReturn;
	int nCenterY  = m_rectCurve.top+(int)(m_nBase/(double)m_nRange*m_rectCurve.Height());

	nReturn = nCenterY - dValue/(8.0*m_dDimY)*m_rectCurve.Height();
	return nReturn;
}
void CScope::SetValueString(CString strTitle,CString strUnit)//文字的更改，用于对应不同波形的单位（默认为度）
{
}
void CScope::Clear()//分别删除方波和正弦波相关函数，释放内存
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