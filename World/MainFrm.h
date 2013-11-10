#pragma once

// MainFrm.h : CMainFrame 类的接口
class CMainFrame : public CFrameWnd
{
public:
	virtual ~CMainFrame(){}
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);//定义主窗体属性

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: // 仅从序列化创建
	CMainFrame(){}
	DECLARE_DYNCREATE(CMainFrame)
	DECLARE_MESSAGE_MAP()// 生成的消息映射函数
};