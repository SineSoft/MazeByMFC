#pragma once
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
// MFCWorld.h : MFCWorld Ӧ�ó������ͷ�ļ�
#include "resource.h"       //��Դ

// CMFCWorldApp��:
class CMFCWorldApp : public CWinApp
{
public:
	CMFCWorldApp();
	virtual BOOL InitInstance();//Ӧ�ó����ʼ��
	virtual int ExitInstance();
	afx_msg void OnAppAbout();//�������ڶԻ���
	DECLARE_MESSAGE_MAP()
};

extern CMFCWorldApp theApp;//��Ӧ�ó���Ķ���,��ϵͳ����

//��Ŀԭ�ļ������к�DEBUG�����۵Ŀ������ķ��źʹ��붼�ǵ�����Ϊ�˽��е�����ӵģ���������ʱ(Release����)���ᱻ����