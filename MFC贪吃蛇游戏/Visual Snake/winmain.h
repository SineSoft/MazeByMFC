#ifndef _VSNAKE_WINMAIN_H
#define _VSNAKE_WINMAIN_H

#include <cstdlib>
#include <ctime>
#include <afxwin.h>
#include "winshell.h"

//Ӧ�ó����࣬���Ӧ�ó��������Ϣѭ��ǰ��һϵ�г�ʼ������

class Instance : public CWinApp {
public:
	BOOL InitInstance();//��ʼ��Ӧ�ó���
private:
	Snakeform Mainform;
};

#endif