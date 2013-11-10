#include "snake.h"

Snake::Snake(int x,int y,int l,bool front,bool xvec_v,gameboard* mapin,int TimerID)
	: map(mapin),x_v(xvec_v),alive(true),TID(TimerID),vecxnew(xvec_v) {
	//以(x,y)为起点向给定方向延伸l格形成贪吃蛇
	level = 1;
	score = 0;
	v = (front) ? 1 : -1;
	if (xvec_v) {
		for (int i = 0; i < l; ++i) {
			snake.push(point(x,y));
			map->set(x,y,false,RGB(0,255,0));
			x += v;
		}
		x -= v;
	} else {
		for (int i = 0; i < l; ++i) {
			snake.push(point(x,y));
			map->set(x,y,false,RGB(0,255,0));
			y += v;
		}
		y -= v;
	}
	this->x = x;
	this->y = y;
}

bool Snake::pop() {
	map->set(snake.front().first,snake.front().second,true);//通知gameboard更改状态
	if (snake.size() == 1) return false;
	snake.pop();
	return true;
}

bool Snake::move() {
	if (!alive) return false;
	if (!cmdline.empty()) {
		v = cmdline.front().first;
		x_v = cmdline.front().second;
		cmdline.pop();
	}
	if (x_v) x += v;
	else y += v;
	if (!map->get(x,y)) {//前方不可行，结束游戏
		alive = false;
		return false;
	}
	map->set(x,y,false,RGB(0,255,0));//前进
	snake.push(point(x,y));
	if (!map->getfood(x,y)) pop();
	else {
		++score;
		map->PrintNum(10,0,L"%04d",score);
		if (!(score%30)) {
			++level;
			map->PrintNum(34,0,L"%02d",level);
			uplevel = true;//通知计时器及时修改计时间隔
		}
	}
	return true;
}

bool Snake::need_refresh_timer() {//用于通知负责游戏计时的类刷新计时间隔
	if (uplevel) {
		uplevel = false;
		return true;
	}
	return false;
}

void Snake::getcmd(int v,bool vin_x) {
	if (!alive) return ;
	if (vin_x != vecxnew) {//法向
		vecxnew = vin_x;
		cmdline.push(cmd(v,vin_x));
	} else if (v == this->v) {//同向
		move();
	}
}

Snake::~Snake() {
	while (!cmdline.empty()) cmdline.pop();
	while (!(snake.size() == 1)) pop();
	map->set(snake.front().first,snake.front().second,true);
	snake.pop();
}


// snake 消息处理程序


