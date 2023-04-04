#pragma once
class CGame
{
public:
	void SetHandle(HWND hWnd);//����������ڵľ��

	bool EnterFrame(DWORD dwTime);//������Ϸ֡

	void OnMouseMove(UINT nFlags, CPoint point);//��������ƶ��¼�

	void OnLButtonUp(UINT nFlags, CPoint point);//�������̧���¼�

private:
	HWND m_hWnd;//����

	//��Ϸ��ͼ����
	//����滭��Ϸ�еĶ���
	void GameRunDraw();
	//���fps
	void DrawFps(Graphics& gh);

	//��¼��Ϸÿ�����֡
	int m_fps{ 0 };
};

