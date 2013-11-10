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

//文档类的数据基类：world类的定义
class world//Max:39*21
{
public:
	world(unsigned int,unsigned int);
	virtual ~world();
	void creatworld();//迷宫生成
	char** getmap(int);//数据输出
	bool win(); //取胜判断
protected:
	void rebuiltworld(int); //游戏功能
	char** p; //数据区
	int M,N;  //大小
	int x,y;  //player位置
	int sx,sy;//迷宫入口
	bool iwin;//取胜标记
};