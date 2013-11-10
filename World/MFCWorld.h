#pragma once
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif
// MFCWorld.h : MFCWorld 应用程序的主头文件
#include "resource.h"       //资源

// CMFCWorldApp类:
class CMFCWorldApp : public CWinApp
{
public:
	CMFCWorldApp();
	virtual BOOL InitInstance();//应用程序初始化
	virtual int ExitInstance();
	afx_msg void OnAppAbout();//弹出关于对话框
	DECLARE_MESSAGE_MAP()
};

extern CMFCWorldApp theApp;//本应用程序的对象,供系统调用

//项目原文件中所有含DEBUG等字眼的看不懂的符号和代码都是调试器为了进行调试添加的，正常运行时(Release编译)不会被编译