#ifndef _VSNAKE_SNAKE_H
#define _VSNAKE_SNAKE_H

#include <queue>
#include "gameboard.h"

typedef std::pair<int,bool> cmd;
typedef std::pair<int,int> point;

//̰�����࣬�ṩ��Ϸ���߼�ʵ��
//ά��̰���߼����˶���ʵ�ֵ��߼�������
//�������ݷ����仯ʱʵʱ֪ͨgameboard������Ӧ����

class Snake {

public:
	Snake(int x,int y,int l,bool front,bool xvec_v,gameboard* mapin,int TimerID);
	bool move();//���һ���ƶ�
	void getcmd(int v,bool v_x);//������Ϸ��������
	bool isalive() {return alive;}//�����������ж���Ϸ�Ƿ����ڼ���
	int levelnow() {return level;}//�����������֪��ǰ�Ѷȼ���
	int Timer() {return TID;}//�����������֪����̰���ߵļ�ʱ���ı��
	bool need_refresh_timer();//����֪ͨ������Ϸ��ʱ����ˢ�¼�ʱ���
	~Snake();

private:
	int x,y,v,level,score,TID;
	bool x_v,alive,vecxnew;
	bool uplevel;
	std::queue<point> snake;
	std::queue<cmd> cmdline;
	bool pop();//��̰����β��ȥ��һ��������ʵ���˶�
	gameboard* map;//����̰���ߡ����桱��gameboard
};

#endif