#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#define MAXM 79
#define MAXN 41
#define EXIT 0x07
#define WALL 0x08
#define ROAD 0x09
#define PLAY 0x0D

//�ĵ�������ݻ��ࣺworld��Ķ���
class world//Max:39*21
{
public:
	world(unsigned int,unsigned int);
	virtual ~world();
	void creatworld();//�Թ�����
	char** getmap(int);//�������
	bool win(); //ȡʤ�ж�
protected:
	void rebuiltworld(int); //��Ϸ����
	char** p; //������
	int M,N;  //��С
	int x,y;  //playerλ��
	int sx,sy;//�Թ����
	bool iwin;//ȡʤ���
};