#ifndef _VSNAKE_GAMEBOARD_H
#define _VSNAKE_GAMEBOARD_H

#include <cstdlib>
#include <afxwin.h>

//游戏面板类，提供游戏的基本框架。
//gameboard维护snake的食物、以及snake的可行走区域
//gameboard类会将自己的状态实时绘制在一个绘图设备上，创建是需指定绘图设备和相关参数

class gameboard {

public:
	gameboard(int foods,CDC* pdc,int dctop,int dcleft,int dccella);
	void set(int x,int y,bool b,COLORREF clr = RGB(0,0,0));//改变某一格的状态，若为false则在dc上以clr颜色显示
	bool get(int x,int y);//获取(x,y)格的状态
	void PrintNum(int x, int y, wchar_t* format, int num);//在dc的指定位置按指定格式输出一个数字
	bool getfood(int x,int y);//判断snake走到(x,y)位置是否吃到了食物，是的话就重生成一个食物并返回true
	void setfood(int n);//生成新的食物并画在dc上

private:
	inline int getrand(int max);//生成随机数
	int gridcanmove;//当前可行走区域的总数
	int foodnum;//记录该gameboard上同时存在的食物数量
	bool map[40][24];//游戏区域，为true表示可行
	int *foodx,*foody;//记录gameboard上的所有食物的信息
	CDC* dc;//用于绘图的设备
	int top,left,cella;//绘图参数：从(top,left)像素开始，每一格边长20像素
	//绘图用到的临时变量
	CBrush *oldBrush;
	CPen *oldpen;
};

#endif
