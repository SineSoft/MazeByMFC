#include "winmain.h"
BOOL Instance::InitInstance() {
	srand((unsigned int)time(0));
	CWinApp::InitInstance();
	//应用程序主窗口的创建
	Mainform.Create(0,L"贪吃蛇 by Sine",
		WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		Mainform.normal_size());
	Mainform.ShowWindow(m_nCmdShow);
	//主窗口大小的调整
    RECT WindowRect;
    RECT ClientRect;
    Mainform.GetWindowRect(&WindowRect);
    Mainform.GetClientRect(&ClientRect);
    WindowRect.right += (width - ClientRect.right);
	WindowRect.bottom += (height - ClientRect.bottom);
    Mainform.MoveWindow(WindowRect.left, WindowRect.top, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, true);
	//最后的初始化工作与游戏窗口的初始化
	Mainform.Invalidate();
	m_pMainWnd = &Mainform;
	Mainform.init();
	return TRUE;
}
Instance theApp;