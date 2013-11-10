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

//窗口类，负责用户界面的布局。
//维护计时器，绘图板，管理gameboard与snake的数据
//负责系统信息的响应，游戏状态的转换，游戏进程的控制

class Snakeform : public CFrameWnd {
public:
	RECT normal_size();//给出游戏窗口的初始值，在稍后做根据具体系统调整。
	//目的是使窗口初始大小与调整后的大小差异不要过大，调整窗口大小的过程就不会显得突兀。
	void init();//第一次开始游戏前的初始化
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);//禁止刷新背景避免窗口闪烁
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()//没有OnPaint是因为它与OnTimer冲突，只好以一个时间间隔较短的计时器取代之。

private:
	gameboard *map;
	Snake * snake;
	CDC MemDC;//绘图板绘图器
	CBitmap MemBitmap;//绘图板
	HFONT Text;//游戏中的字体
	enum {RUNNING,GAMEOVER,PAUSE,HOLD}Status;//定义游戏状态
	//以下为状态转移函数
	void continue_game();
	void game_over();
	void pause();
	void hold_game();
	void start_game();
	//终止游戏
	void StopApp();
};

#endif