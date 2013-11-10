#pragma once

// MFCWorldView.h : CMFCWorldView 类的接口
class CMFCWorldView : public CView
{
public:
	virtual ~CMFCWorldView(){}
	CMFCWorldDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);//根据文档，绘制视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);//按键事件发生时，重绘视图以响应
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);//清空视图的时机：从不
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);//接收字符事件发生时，重绘视图以响应

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMFCWorldView(){} // 仅从序列化创建视图
	DECLARE_DYNCREATE(CMFCWorldView)
	DECLARE_MESSAGE_MAP()// 生成的消息映射函数
};

#ifndef _DEBUG  // MFCWorldView.cpp 中的调试版本
inline CMFCWorldDoc* CMFCWorldView::GetDocument() const
   { return reinterpret_cast<CMFCWorldDoc*>(m_pDocument); }
#endif

