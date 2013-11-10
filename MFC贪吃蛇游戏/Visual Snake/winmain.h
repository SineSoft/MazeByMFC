#ifndef _VSNAKE_WINMAIN_H
#define _VSNAKE_WINMAIN_H

#include <cstdlib>
#include <ctime>
#include <afxwin.h>
#include "winshell.h"

//应用程序类，完成应用程序进入消息循环前的一系列初始化工作

class Instance : public CWinApp {
public:
	BOOL InitInstance();//初始化应用程序
private:
	Snakeform Mainform;
};

#endif