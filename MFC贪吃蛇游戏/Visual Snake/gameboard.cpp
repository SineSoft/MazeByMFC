#include "gameboard.h"
//#define _SNAKE_WITH_BLACK_LINE //ע�͵����������Ͻ�������ֺ���

//Ԥ����Ļ�ͼ����
CBrush foodBrush(RGB(255,0,0));
CBrush whiteBrush(RGB(255,255,255));
CPen whitePen(PS_SOLID,0,RGB(255,255,255));

void gameboard::set(int x,int y,bool b,COLORREF clr) {
	CBrush tbrush(clr);
#ifndef _SNAKE_WITH_BLACK_LINE
	CPen tpen(PS_SOLID,0,clr);//�߿���ɫ�뻭ˢ��ɫһ��
#endif
	if ((!map[x][y]) && b) {
		++gridcanmove;
	} else if (map[x][y] && (!b)) {
		--gridcanmove;
	}
	oldBrush = dc ->SelectObject(&(b? whiteBrush : tbrush));
	if (b) oldpen = dc ->SelectObject(&whitePen);
#ifndef _SNAKE_WITH_BLACK_LINE
	else oldpen = dc ->SelectObject(&tpen);
#endif
	dc ->Rectangle(left+cella*x,top+cella*y,left+cella*(x+1),top+cella*(y+1));
	dc ->SelectObject(oldBrush);
	dc ->SelectObject(oldpen);
	map[x][y] = b;
}

bool gameboard::get(int x,int y) {
	return map[x][y];
}

gameboard::gameboard(int foods,CDC* pdc,int dctop,int dcleft,int dccella)
	:foodnum(foods),dc(pdc),top(dctop),left(dcleft),cella(dccella) {
	for (int i = 0; i < 40; ++i)
		for (int j = 0; j < 24; ++j)
			set(i,j,true);
	foodx = new int[foods];
	foody = new int[foods];
	gridcanmove = 960;
}

inline int gameboard::getrand(int max) {
	return rand()%max;
}

void gameboard::setfood(int fn) {//�������ʳ��
	int p = getrand(gridcanmove - foodnum + 1) + 1,n = 0;//�����п��������������ȡһ����
	for (int i = 1; i < 39; ++i) {//Ѱ�Ҹõ㲢����ʳ��
		for (int j = 1; j < 24; ++j) {
			if (map[i][j]) ++n;
			if (n == p) {
				foodx[fn-1] = i; foody[fn-1] = j;
				oldBrush = dc ->SelectObject(&foodBrush);
				dc ->Ellipse(left+cella*i,top+cella*j,left+cella*(i+1),top+cella*(j+1));
				dc ->SelectObject(oldBrush);
				return ;
			}
		}
	}
}

bool gameboard::getfood(int x,int y) {
	for (int i = 0; i < foodnum; ++i) {//�����ж�ÿ��ʳ���Ƿ񱻳Ե�
		if (x == foodx[i] && y == foody[i]) {
			setfood(i+1);
			return true;
		}
	}
	return false;
}

void gameboard::PrintNum(int x, int y, wchar_t* format, int num) {
	CString str;
	str.Format(format,num);
	dc->TextOut(left+cella*x,top+cella*y,str);
}
