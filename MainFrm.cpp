#include"pch.h"
#include"Tank.h"

#include"MainFrm.h"

#ifdef DEBUG
#define new DEBUG_NEW
#endif // DEBUG

#define GAME_WIN_W (800)       //全局变量：窗口宽
#define GAME_WIN_H (600)       //全局变量：窗口高

//CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame,CFrameWnd)//Viual Studio 2015自动生成代码

BEGIN_MESSAGE_MAP(CMainFrame,CFrameWnd)//Viual Studio 2015自动生成代码
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//CMainFrame构造/析构

CMainFrame::CMainFrame()
{
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | \
		WS_MINIMIZEBOX | FWS_ADDTOTITLE)
	//创建窗口
	Create(NULL, _T("AcMake,坤坤大战"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
	//设置客户区大小
	{
		CRect rcCli;
		GetClientRect(rcCli);  //获取客户区的大小

		RECT rcFrame = { 0,0,
						m_iWidth + m_iWidth - rcCli.right,
						m_iHeight + m_iHeight - rcCli.bottom
						};
		MoveWindow(&rcFrame, TRUE);  //调用windowsAPI设置窗口大小
	}
}

CMainFrame::~CMainFrame()       //析构函数
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	SetTimer(ETimerIdGameLoop, 0, NULL);//启动定时器每次都会进入游戏帧
	m_game.SetHandle(GetSafeHwnd());//设置游戏主窗口句柄
	return 0;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case ETimerIdGameLoop://游戏循环ID
		{
			static DWORD dwLastUpdate = GetTickCount(); //记录本次时刻
			if (GetTickCount() - dwLastUpdate >= 20)//判断时间间隔
			{
				m_game.EnterFrame(GetTickCount());
				dwLastUpdate = GetTickCount();
			}
			//否则什么都不做
		}
		default:
			break;
	}
	CFrameWnd::OnTimer(nIDEvent);
}