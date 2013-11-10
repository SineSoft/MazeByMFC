#include "winshell.h"
BEGIN_MESSAGE_MAP(Snakeform,CFrameWnd)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

RECT Snakeform::normal_size() {
	RECT n = {CFrameWnd::rectDefault.left,
		CFrameWnd::rectDefault.top,
		CFrameWnd::rectDefault.left+width+10,
		CFrameWnd::rectDefault.top+height+30
	};
	return n;
}

void Snakeform::OnTimer(UINT_PTR nIDEvent) {
	CDC *pDC = GetDC();
	switch (nIDEvent) {
	case 1:
		pDC->BitBlt(0,0,width,height,&MemDC,0,0,SRCCOPY);//将绘图板刷到屏幕上
		break;
	case 100:
		if (snake->need_refresh_timer()) {//检测到需要刷新
			SetTimer(snake->Timer(),1000/(snake->levelnow()+1),NULL);
		}
		if (snake->isalive()) {
			snake->move();
		} else {
			game_over();
		}
		break;
	}
	ReleaseDC(pDC);
}

void Snakeform::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		if (ISRUNNING) snake->getcmd(-1,true);
		else if (ISHOLD) start_game();
		break;
	case VK_RIGHT:
		if (ISRUNNING) snake->getcmd(1,true);
		else if (ISHOLD) start_game();
		break;
	case VK_UP:
		if (ISRUNNING) snake->getcmd(-1,false);
		else if (ISHOLD) start_game();
		break;
	case VK_DOWN:
		if (ISRUNNING) snake->getcmd(1,false);
		else if (ISHOLD) start_game();
		break;
	case VK_SPACE:
		if (ISRUNNING) pause();
		else if (ISPAUSE) continue_game();
		break;
	case VK_ESCAPE:
		if (ISRUNNING) pause();
		else if (ISPAUSE || ISGAMEOVER || ISHOLD) StopApp();
		break;
	case VK_RETURN:
		if (ISGAMEOVER) hold_game();
		break;
	}
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void Snakeform::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case 'A': case 'a':
		if (ISRUNNING) snake->getcmd(-1,true);
		else if (ISHOLD) start_game();
		break;
	case 'D': case 'd':
		if (ISRUNNING) snake->getcmd(1,true);
		else if (ISHOLD) start_game();
		break;
	case 'W': case 'w':
		if (ISRUNNING) snake->getcmd(-1,false);
		else if (ISHOLD) start_game();
		break;
	case 'S': case 's':
		if (ISRUNNING) snake->getcmd(1,false);
		else if (ISHOLD) start_game();
		break;
	}
	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}

void Snakeform::OnDestroy() {
	CFrameWnd::OnDestroy();
	StopApp();
}

BOOL Snakeform::OnEraseBkgnd(CDC* pDC) {
	return true;
}

void Snakeform::init() {
	SetIcon(AfxGetApp()->LoadIcon(IDI_MAIN), TRUE);
	MemDC.CreateCompatibleDC(NULL);
	CDC *pDC = GetDC();
	MemBitmap.CreateCompatibleBitmap(pDC,width,height);
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);//创建绘图区
	MemDC.FillSolidRect(0,0,width,height,RGB(255,255,255));//初始化
	Text = CreateFont(20,10,0,0,FW_NORMAL,0,0,0,
		GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"宋体字");
	MemDC.SelectObject(Text);
	MemDC.SetTextColor(RGB(0,0,0));
	MemDC.SetBkColor(RGB(255,255,255));
	SetTimer(1,20,NULL);
	ReleaseDC(pDC);
	Status = HOLD;
	map = new gameboard(1,&MemDC,20,20,20);
	//初始化gameboard的边框
	for (int i = 0; i < 40; ++i) {
		map->set(i,0,false);
		map->set(i,23,false);
	}
	for (int i = 1; i < 23; ++i) {
		map->set(0,i,false);
		map->set(39,i,false);
	}
	snake = new Snake(1,1,5,true,true,map,100);
	MemDC.TextOut(120,20,"您的分数：");
	MemDC.TextOut(600,20,"当前级别：");
}

void Snakeform::pause() {
	KillTimer(snake->Timer());
	Status = PAUSE;
	MemDC.TextOut(20,480,L"按空格键返回游戏或按“ESC”键退出。");
}

void Snakeform::continue_game() {
	SetTimer(snake->Timer(),1000/(snake->levelnow()+1),NULL);
	Status = RUNNING;
	CBrush blk(RGB(0,0,0)),*oldBrush = MemDC.SelectObject(&blk);
	MemDC.Rectangle(20,480,420,500);
	MemDC.SelectObject(oldBrush);
}

void Snakeform::game_over() {
	Status = GAMEOVER;
	KillTimer(100);
	MemDC.TextOut(20,480,L"你输了！按回车键重新开始游戏或按“ESC”退出。");
}

void Snakeform::hold_game() {
	Status = HOLD;
	delete snake;
	delete map;
	map = new gameboard(1,&MemDC,20,20,20);
	for (int i = 0; i < 40; ++i) {
		map->set(i,0,false);
		map->set(i,23,false);
	}
	for (int i = 1; i < 23; ++i) {
		map->set(0,i,false);
		map->set(39,i,false);
	}
	snake = new Snake(1,1,5,true,true,map,100);
	MemDC.TextOut(120,20,"您的分数：");
	MemDC.TextOut(600,20,"当前级别：");
}

void Snakeform::start_game(void) {
	Status = RUNNING;
	map->setfood(1);
	SetTimer(snake->Timer(),1000/(snake->levelnow()+1),NULL);
	MemDC.TextOut(700,20,L"01");
	MemDC.TextOut(220,20,L"0000");
}

void Snakeform::StopApp(void) {
	KillTimer(1);
	MemBitmap.DeleteObject(); 
	MemDC.DeleteDC();
	PostQuitMessage(0);
}