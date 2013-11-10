// MFCWorldView.cpp : CMFCWorldView ���ʵ��
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

//ϵͳĬ�ϵ���ͼ��ʼ��
BOOL CMFCWorldView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CMFCWorldView ����
#define Start 15 //��ʼ��ͼ������
#define cubelong 10//ÿ��С����ı߳�
void CMFCWorldView::OnDraw(CDC* pDC)
{
	//��ȡ�ĵ�
	CMFCWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//׼���ڴ��ͼ������
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);//������ͼ�豸
	//��ͼ�����С��������������ֱ��ʹ�ô��ڴ�С��Ҳ�����Լ�������Ҫ��������
	MemBitmap.CreateCompatibleBitmap(pDC,870,510);CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);//������ͼ��
	MemDC.FillSolidRect(0,0,870,510,RGB(255,255,255));//��ʼ��
	//��ȡ�ĵ�
	char** p;
	p = pDoc->getmap(5);
	//��ˢ����
	int wallc=RGB(0,0,0);//ǽ�Ǻ�ɫ
	CBrush wallBrush(wallc);
	int playc=RGB(0,255,0);//�������ɫ
	CBrush playBrush(playc);
	int exitc=RGB(255,0,0);//�����Ǻ�ɫ
	CBrush exitBrush(exitc);
	CBrush *oldBrush;
	//��������ͼ
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
	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ 
	pDC->BitBlt(0,0,870,510,&MemDC,0,0,SRCCOPY); 
	//��ͼ��ɺ������ 
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

CMFCWorldDoc* CMFCWorldView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCWorldDoc)));
	return (CMFCWorldDoc*)m_pDocument;
}
#endif

// CMFCWorldView ��Ϣ�������
void CMFCWorldView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)//�����¼�
{
	CMFCWorldDoc* pDoc = GetDocument();
	if (!pDoc->win())//ȡʤ���ֹ�ƶ�
	{
		switch (nChar)//���ݰ���������Ӧ
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
		InvalidateRect(NULL,TRUE);//�ػ���ͼ
		if(pDoc->win())MessageBox(L"Your Win!",L"Congregation!",MB_OK);//ȡʤʱ����
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);//ʣ�µĹ����������ദ��
}

BOOL CMFCWorldView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;//���ۺ�ʱ������true��ʵ�����Ǹ���ֹ�˱���ˢ��
}

//�밴���¼���������
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