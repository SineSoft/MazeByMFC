#ifndef _VSNAKE_WINSHELL_H
#define _VSNAKE_WINSHELL_H

#include <afxwin.h>
#include "gameboard.h"
#include "snake.h"
#include "resource.h"

#define width (int) 840
#define height (int) 520

#define ISPAUSE Status == PAUSE
#define ISRUNNING Status == RUNNING
#define ISGAMEOVER Status == GAMEOVER
#define ISHOLD Status == HOLD

//�����࣬�����û�����Ĳ��֡�
//ά����ʱ������ͼ�壬����gameboard��snake������
//����ϵͳ��Ϣ����Ӧ����Ϸ״̬��ת������Ϸ���̵Ŀ���

class Snakeform : public CFrameWnd {
public:
	RECT normal_size();//������Ϸ���ڵĳ�ʼֵ�����Ժ������ݾ���ϵͳ������
	//Ŀ����ʹ���ڳ�ʼ��С�������Ĵ�С���첻Ҫ���󣬵������ڴ�С�Ĺ��̾Ͳ����Ե�ͻأ��
	void init();//��һ�ο�ʼ��Ϸǰ�ĳ�ʼ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);//��ֹˢ�±������ⴰ����˸
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()//û��OnPaint����Ϊ����OnTimer��ͻ��ֻ����һ��ʱ�����϶̵ļ�ʱ��ȡ��֮��

private:
	gameboard *map;
	Snake * snake;
	CDC MemDC;//��ͼ���ͼ��
	CBitmap MemBitmap;//��ͼ��
	HFONT Text;//��Ϸ�е�����
	enum {RUNNING,GAMEOVER,PAUSE,HOLD}Status;//������Ϸ״̬
	//����Ϊ״̬ת�ƺ���
	void continue_game();
	void game_over();
	void pause();
	void hold_game();
	void start_game();
	//��ֹ��Ϸ
	void StopApp();
};

#endif