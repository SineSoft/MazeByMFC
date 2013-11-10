// MFCWorld.cpp : 定义应用程序的类行为。
#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCWorld.h"
#include "MainFrm.h"
#include "world.h"
#include "MFCWorldDoc.h"
#include "MFCWorldView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCWorldApp

BEGIN_MESSAGE_MAP(CMFCWorldApp, CWinApp)//菜单命令全部使用系统提供的默认版本
	ON_COMMAND(ID_APP_ABOUT, &CMFCWorldApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

// CMFCWorldApp 构造
CMFCWorldApp::CMFCWorldApp()
{
	//以下应用程序 ID 字符串为应用程序唯一的 ID 字符串；一般来说字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Sine.World.Game.0.1"));
}

// 唯一的一个 CMFCWorldApp 对象，代表本程序，供系统调用
CMFCWorldApp theApp;

//系统生成的 CMFCWorldApp 初始化函数
BOOL CMFCWorldApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	EnableTaskbarInteraction(FALSE);
	SetRegistryKey(_T("Sine-World"));

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFCWorldDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMFCWorldView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	// 使本程序禁止作为服务启动
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	//允许使用将文件拖进窗口内释放的方式打开文件，系统自动生成
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

//系统生成的用于应用程序结束时的操作
int CMFCWorldApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}

//系统生成的定义“关于”对话框的类
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() : CDialogEx(CAboutDlg::IDD){}
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
};

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CHAR()
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMFCWorldApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCWorldApp 消息处理程序