// MFCWorld.cpp : ����Ӧ�ó��������Ϊ��
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

BEGIN_MESSAGE_MAP(CMFCWorldApp, CWinApp)//�˵�����ȫ��ʹ��ϵͳ�ṩ��Ĭ�ϰ汾
	ON_COMMAND(ID_APP_ABOUT, &CMFCWorldApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

// CMFCWorldApp ����
CMFCWorldApp::CMFCWorldApp()
{
	//����Ӧ�ó��� ID �ַ���ΪӦ�ó���Ψһ�� ID �ַ�����һ����˵�ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Sine.World.Game.0.1"));
}

// Ψһ��һ�� CMFCWorldApp ���󣬴������򣬹�ϵͳ����
CMFCWorldApp theApp;

//ϵͳ���ɵ� CMFCWorldApp ��ʼ������
BOOL CMFCWorldApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	EnableTaskbarInteraction(FALSE);
	SetRegistryKey(_T("Sine-World"));

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFCWorldDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMFCWorldView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	// ʹ�������ֹ��Ϊ��������
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	//����ʹ�ý��ļ��Ͻ��������ͷŵķ�ʽ���ļ���ϵͳ�Զ�����
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

//ϵͳ���ɵ�����Ӧ�ó������ʱ�Ĳ���
int CMFCWorldApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}

//ϵͳ���ɵĶ��塰���ڡ��Ի������
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() : CDialogEx(CAboutDlg::IDD){}
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
};

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CHAR()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMFCWorldApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCWorldApp ��Ϣ�������