#include "winmain.h"
BOOL Instance::InitInstance() {
	srand((unsigned int)time(0));
	CWinApp::InitInstance();
	//Ӧ�ó��������ڵĴ���
	Mainform.Create(0,L"̰���� by Sine",
		WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		Mainform.normal_size());
	Mainform.ShowWindow(m_nCmdShow);
	//�����ڴ�С�ĵ���
    RECT WindowRect;
    RECT ClientRect;
    Mainform.GetWindowRect(&WindowRect);
    Mainform.GetClientRect(&ClientRect);
    WindowRect.right += (width - ClientRect.right);
	WindowRect.bottom += (height - ClientRect.bottom);
    Mainform.MoveWindow(WindowRect.left, WindowRect.top, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, true);
	//���ĳ�ʼ����������Ϸ���ڵĳ�ʼ��
	Mainform.Invalidate();
	m_pMainWnd = &Mainform;
	Mainform.init();
	return TRUE;
}
Instance theApp;