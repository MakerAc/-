#include "pch.h"
#include "Game.h"
void CGame::SetHandle(HWND hWnd)//����������ڵľ��
{
	m_hWnd = hWnd;
}

bool CGame::EnterFrame(DWORD dwTime)//������Ϸ֡
{
	GameRunDraw();
	return false;
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)//��������ƶ��¼�
{
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)//����������̧���¼�
{
}

void CGame::GameRunDraw()
{
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;//�ͻ����Ĵ�С
	GetClientRect(m_hWnd, &rc);

	CDC* dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;//˫�����ͼ��
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());//�������
	gh.Clear(Color::White);//�������
	gh.ResetClip();

	DrawFps(gh);//�����ڴ�

	//����һ��ͼƬ
	{
		//��ȡ��Ϸ���ڴ�С
		CRect rc;
		GetClientRect(m_hWnd, rc);

		//����Ҫ���Ƶ�ͼƬ
		Gdiplus::Image* img = Image::FromFile(_T("menu_background.png"));
		
		//����ͼƬ
		gh.DrawImage(img, rc.left, rc.top, rc.Width(), rc.Height());
	}
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),//���Ƶ���Ļ
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();//�ͷ�
	return;
}

//��fps
void CGame::DrawFps(Graphics& gh)
{
	static int fps = 0;//���徲̬������ÿ�ν��뺯��ʱ�����ϴε�ֵ
	m_fps++;//��¼�Ѿ����˶���֡
	static DWORD dwLast = GetTickCount();//��¼�ϴ����fps��ʱ��
	if (GetTickCount() - dwLast >= 1000)//�ж�ʱ���Ƿ񳬹�1�룬������������fps
	{
		fps = m_fps;
		m_fps = 0;//���㣬�����֡�������¼���
		dwLast = GetTickCount();//��¼���������ʱ��
	}

	//���fps
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);//��fps��ʽ�����ַ���
		SolidBrush brush(Color(0x00, 0x00, 0xFF));//������ɫ�Ļ�ˢ
		Gdiplus::Font font(_T("����"), 10.0);//�������������
		CRect rc;
		::GetClientRect(m_hWnd, &rc);//��ȡ������ڵĴ�С��������λ���ֵ����λ��
		PointF origin(static_cast<float>(rc.right - 80),
			static_cast<float>(rc.top + 2));
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);//��ʽ�������
	}
}