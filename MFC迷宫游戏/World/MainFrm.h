#pragma once

// MainFrm.h : CMainFrame ��Ľӿ�
class CMainFrame : public CFrameWnd
{
public:
	virtual ~CMainFrame(){}
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);//��������������

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: // �������л�����
	CMainFrame(){}
	DECLARE_DYNCREATE(CMainFrame)
	DECLARE_MESSAGE_MAP()// ���ɵ���Ϣӳ�亯��
};