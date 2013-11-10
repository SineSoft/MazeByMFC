#pragma once

// MFCWorldView.h : CMFCWorldView ��Ľӿ�
class CMFCWorldView : public CView
{
public:
	virtual ~CMFCWorldView(){}
	CMFCWorldDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);//�����ĵ���������ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);//�����¼�����ʱ���ػ���ͼ����Ӧ
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);//�����ͼ��ʱ�����Ӳ�
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);//�����ַ��¼�����ʱ���ػ���ͼ����Ӧ

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMFCWorldView(){} // �������л�������ͼ
	DECLARE_DYNCREATE(CMFCWorldView)
	DECLARE_MESSAGE_MAP()// ���ɵ���Ϣӳ�亯��
};

#ifndef _DEBUG  // MFCWorldView.cpp �еĵ��԰汾
inline CMFCWorldDoc* CMFCWorldView::GetDocument() const
   { return reinterpret_cast<CMFCWorldDoc*>(m_pDocument); }
#endif

