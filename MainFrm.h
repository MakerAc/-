#pragma once
#include "Game.h"
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
protected:
	DECLARE_DYNAMIC(CMainFrame)

		//特性
public:

	//操作
public:

	//重写
public:

	//实现
public:
	virtual ~CMainFrame();

	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//生成消息的映射方法
protected:
	afx_msg int onCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP();

	int m_iWidth{ 800 };//客户区的宽
	int m_iHeight{ 600 };//客户区的高
	
	enum ETimerId { ETimerIdGameLoop = 1 };//定时器ID

	CGame m_game;//游戏对象
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};