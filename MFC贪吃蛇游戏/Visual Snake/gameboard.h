#ifndef _VSNAKE_GAMEBOARD_H
#define _VSNAKE_GAMEBOARD_H

#include <cstdlib>
#include <afxwin.h>

//��Ϸ����࣬�ṩ��Ϸ�Ļ�����ܡ�
//gameboardά��snake��ʳ��Լ�snake�Ŀ���������
//gameboard��Ὣ�Լ���״̬ʵʱ������һ����ͼ�豸�ϣ���������ָ����ͼ�豸����ز���

class gameboard {

public:
	gameboard(int foods,CDC* pdc,int dctop,int dcleft,int dccella);
	void set(int x,int y,bool b,COLORREF clr = RGB(0,0,0));//�ı�ĳһ���״̬����Ϊfalse����dc����clr��ɫ��ʾ
	bool get(int x,int y);//��ȡ(x,y)���״̬
	void PrintNum(int x, int y, wchar_t* format, int num);//��dc��ָ��λ�ð�ָ����ʽ���һ������
	bool getfood(int x,int y);//�ж�snake�ߵ�(x,y)λ���Ƿ�Ե���ʳ��ǵĻ���������һ��ʳ�ﲢ����true
	void setfood(int n);//�����µ�ʳ�ﲢ����dc��

private:
	inline int getrand(int max);//���������
	int gridcanmove;//��ǰ���������������
	int foodnum;//��¼��gameboard��ͬʱ���ڵ�ʳ������
	bool map[40][24];//��Ϸ����Ϊtrue��ʾ����
	int *foodx,*foody;//��¼gameboard�ϵ�����ʳ�����Ϣ
	CDC* dc;//���ڻ�ͼ���豸
	int top,left,cella;//��ͼ��������(top,left)���ؿ�ʼ��ÿһ��߳�20����
	//��ͼ�õ�����ʱ����
	CBrush *oldBrush;
	CPen *oldpen;
};

#endif
