// MFCWorldView.cpp : CMFCWorldView 类的实现
#include "stdafx.h"
#include "MFCWorld.h"
#include "MFCWorldDoc.h"
#include "MFCWorldView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCWorldView
IMPLEMENT_DYNCREATE(CMFCWorldView, CView)
BEGIN_MESSAGE_MAP(CMFCWorldView, CView)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
END_MESSAGE_MAP()

//系统默认的视图初始化
BOOL CMFCWorldView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CMFCWorldView 绘制
#define Start 15 //开始绘图的坐标
#define cubelong 10//每个小方块的边长
void CMFCWorldView::OnDraw(CDC* pDC)
{
	//获取文档
	CMFCWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//准备内存绘图缓冲区
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);//创建绘图设备
	//绘图区域大小，可以像这样中直接使用窗口大小，也可以自己计算需要多大的区域
	MemBitmap.CreateCompatibleBitmap(pDC,870,510);CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);//创建绘图区
	MemDC.FillSolidRect(0,0,870,510,RGB(255,255,255));//初始化
	//读取文档
	char** p;
	p = pDoc->getmap(5);
	//画刷定义
	int wallc=RGB(0,0,0);//墙是黑色
	CBrush wallBrush(wallc);
	int playc=RGB(0,255,0);//玩家是绿色
	CBrush playBrush(playc);
	int exitc=RGB(255,0,0);//出口是红色
	CBrush exitBrush(exitc);
	CBrush *oldBrush;
	//缓冲区绘图
	for (int i = 0; i <= 2*MM; ++i)
	{
		for (int j = 0; j <= 2*NN; ++j)
		{
			switch (p[j][i])
			{
			case WALL:
				oldBrush = MemDC.SelectObject(&wallBrush);
				MemDC.Rectangle(Start+i*cubelong,Start+j*cubelong,Start+(i+1)*cubelong,Start+(j+1)*cubelong);
				MemDC.SelectObject(oldBrush);
				break;
			case PLAY:
				oldBrush = MemDC.SelectObject(&playBrush);
				MemDC.Rectangle(Start+i*cubelong,Start+j*cubelong,Start+(i+1)*cubelong,Start+(j+1)*cubelong);
				MemDC.SelectObject(oldBrush);
				break;
			case EXIT:
				oldBrush = MemDC.SelectObject(&exitBrush);
				MemDC.Rectangle(Start+i*cubelong,Start+j*cubelong,Start+(i+1)*cubelong,Start+(j+1)*cubelong);
				MemDC.SelectObject(oldBrush);
			}
		}
	}
	//将内存中的图拷贝到屏幕上进行显示 
	pDC->BitBlt(0,0,870,510,&MemDC,0,0,SRCCOPY); 
	//绘图完成后的清理 
	MemBitmap.DeleteObject(); 
	MemDC.DeleteDC(); 

}

#ifdef _DEBUG
void CMFCWorldView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCWorldView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCWorldDoc* CMFCWorldView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCWorldDoc)));
	return (CMFCWorldDoc*)m_pDocument;
}
#endif

// CMFCWorldView 消息处理程序
void CMFCWorldView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)//按键事件
{
	CMFCWorldDoc* pDoc = GetDocument();
	if (!pDoc->win())//取胜后禁止移动
	{
		switch (nChar)//根据按键做出响应
		{
			case VK_UP:
			case VK_NUMPAD8:
				pDoc->getmap(8);
				break;
			case VK_DOWN:
			case VK_NUMPAD2:
				pDoc->getmap(2);
				break;
			case VK_LEFT:
			case VK_NUMPAD4:
				pDoc->getmap(4);
				break;
			case VK_RIGHT:
			case VK_NUMPAD6:
				pDoc->getmap(6);
				break;
		}
		InvalidateRect(NULL,TRUE);//重绘视图
		if(pDoc->win())MessageBox(L"Your Win!",L"Congregation!",MB_OK);//取胜时弹出
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);//剩下的工作交给基类处理
}

BOOL CMFCWorldView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;//无论何时都返回true，实际上那个禁止了背景刷新
}

//与按键事件处理类似
void CMFCWorldView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMFCWorldDoc* pDoc = GetDocument();
	if (!pDoc->win())
	{
		switch (nChar)
		{
			case 'W':
			case 'w':
				pDoc->getmap(8);
				break;
			case 'S':
			case 's':
				pDoc->getmap(2);
				break;
			case 'A':
			case 'a':
				pDoc->getmap(4);
				break;
			case 'D':
			case 'd':
				pDoc->getmap(6);
				break;
		}
		InvalidateRect(NULL,TRUE);
		if(pDoc->win())MessageBox(L"Your Win!",L"Congregation!",MB_OK);
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}