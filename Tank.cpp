﻿
// Tank.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Tank.h"
#include "MainFrm.h"

#include "TankDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTankApp

BEGIN_MESSAGE_MAP(CTankApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTankApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CTankApp 构造

CTankApp::CTankApp() noexcept
{

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Tank.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CTankApp 对象

CTankApp theApp;


// CTankApp 初始化

BOOL CTankApp::InitInstance()
{
	CWinApp::InitInstance();
	//GDI+初始化
	Status s = GdiplusStartup(&m_tokenGdiplus, &input, &output);
	//若要创建主窗口，此代码将创建新的框架窗口
	//对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
	{
		return FALSE;
	}
	m_pMainWnd = pFrame;

	pFrame->ShowWindow(SW_SHOW);//显示窗口
	pFrame->UpdateWindow();     //更新窗口
	return TRUE;
}

int CTankApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CTankApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CTankApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTankApp 消息处理程序



