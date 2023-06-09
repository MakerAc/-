#include "pch.h"
#include "Game.h"
void CGame::SetHandle(HWND hWnd)//设置输出窗口的句柄
{
	m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)//进入游戏帧
{
	GameRunDraw();
	return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)//处理鼠标移动事件
{
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)//处理鼠标左键抬起事件
{
}

void CGame::GameRunDraw()
{
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;//客户区的大小
	GetClientRect(m_hWnd, &rc);

	CDC* dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;//双缓冲绘图用
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());//构造对象
	gh.Clear(Color::White);//清除背景
	gh.ResetClip();

	DrawFps(gh);//画入内存

	//画出一幅图片
	{
		//获取游戏窗口大小
		CRect rc;
		GetClientRect(m_hWnd, rc);

		//载入要绘制的图片
		Gdiplus::Image* img = Image::FromFile(_T("menu_background.png"));
		
		//画出图片
		gh.DrawImage(img, rc.left, rc.top, rc.Width(), rc.Height());
	}
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),//复制到屏幕
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();//释放
	return;
}

//画fps
void CGame::DrawFps(Graphics& gh)
{
	static int fps = 0;//定义静态变量，每次进入函数时保存上次的值
	m_fps++;//记录已经画了多少帧
	static DWORD dwLast = GetTickCount();//记录上次输出fps的时间
	if (GetTickCount() - dwLast >= 1000)//判断时间是否超过1秒，如果超过，输出fps
	{
		fps = m_fps;
		m_fps = 0;//清零，方便队帧进行重新计数
		dwLast = GetTickCount();//记录本次输出的时间
	}

	//输出fps
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);//将fps格式化到字符串
		SolidBrush brush(Color(0x00, 0x00, 0xFF));//创建红色的画刷
		Gdiplus::Font font(_T("宋体"), 10.0);//创建输出的字体
		CRect rc;
		::GetClientRect(m_hWnd, &rc);//获取输出窗口的大小，用来定位文字的输出位置
		PointF origin(static_cast<float>(rc.right - 80),
			static_cast<float>(rc.top + 2));
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);//正式输出文字
	}
}