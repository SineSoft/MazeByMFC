#include "snake.h"

Snake::Snake(int x,int y,int l,bool front,bool xvec_v,gameboard* mapin,int TimerID)
	: map(mapin),x_v(xvec_v),alive(true),TID(TimerID),vecxnew(xvec_v) {
	//��(x,y)Ϊ����������������l���γ�̰����
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
	map->set(snake.front().first,snake.front().second,true);//֪ͨgameboard����״̬
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
	if (!map->get(x,y)) {//ǰ�������У�������Ϸ
		alive = false;
		return false;
	}
	map->set(x,y,false,RGB(0,255,0));//ǰ��
	snake.push(point(x,y));
	if (!map->getfood(x,y)) pop();
	else {
		++score;
		map->PrintNum(10,0,L"%04d",score);
		if (!(score%30)) {
			++level;
			map->PrintNum(34,0,L"%02d",level);
			uplevel = true;//֪ͨ��ʱ����ʱ�޸ļ�ʱ���
		}
	}
	return true;
}

bool Snake::need_refresh_timer() {//����֪ͨ������Ϸ��ʱ����ˢ�¼�ʱ���
	if (uplevel) {
		uplevel = false;
		return true;
	}
	return false;
}

void Snake::getcmd(int v,bool vin_x) {
	if (!alive) return ;
	if (vin_x != vecxnew) {//����
		vecxnew = vin_x;
		cmdline.push(cmd(v,vin_x));
	} else if (v == this->v) {//ͬ��
		move();
	}
}

Snake::~Snake() {
	while (!cmdline.empty()) cmdline.pop();
	while (!(snake.size() == 1)) pop();
	map->set(snake.front().first,snake.front().second,true);
	snake.pop();
}


// snake ��Ϣ�������


