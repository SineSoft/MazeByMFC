#ifndef _VSNAKE_SNAKE_H
#define _VSNAKE_SNAKE_H

#include <queue>
#include "gameboard.h"

typedef std::pair<int,bool> cmd;
typedef std::pair<int,int> point;

//贪吃蛇类，提供游戏的逻辑实现
//维护贪吃蛇及其运动的实现的逻辑与数据
//并在数据发生变化时实时通知gameboard做出相应更改

class Snake {

public:
	Snake(int x,int y,int l,bool front,bool xvec_v,gameboard* mapin,int TimerID);
	bool move();//完成一次移动
	void getcmd(int v,bool v_x);//接收游戏控制命令
	bool isalive() {return alive;}//用于其他类判断游戏是否仍在继续
	int levelnow() {return level;}//用于其他类获知当前难度级别
	int Timer() {return TID;}//用于其他类获知这条贪吃蛇的计时器的编号
	bool need_refresh_timer();//用于通知负责游戏计时的类刷新计时间隔
	~Snake();

private:
	int x,y,v,level,score,TID;
	bool x_v,alive,vecxnew;
	bool uplevel;
	std::queue<point> snake;
	std::queue<cmd> cmdline;
	bool pop();//从贪吃蛇尾部去掉一个，用于实现运动
	gameboard* map;//这条贪吃蛇“生存”的gameboard
};

#endif