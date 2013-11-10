// MFCWorldDoc.cpp : CMFCWorldDoc 类的实现
#include "stdafx.h"
#include "MFCWorld.h"
#include "MFCWorldDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCWorldDoc
IMPLEMENT_DYNCREATE(CMFCWorldDoc, CDocument)
BEGIN_MESSAGE_MAP(CMFCWorldDoc, CDocument)
END_MESSAGE_MAP()

BOOL CMFCWorldDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	creatworld();//生成新迷宫
	return TRUE;
}

// CMFCWorldDoc 序列化
void CMFCWorldDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())//保存文档
	{
		int tx = x,ty = y;//建临时变量保存当前玩家所在位置
		getmap(0);//重置地图
		ar<<sx<<sy;//保存文件：保存入口位置
		for (int i = 0; i <= 2*NN; ++i)//保存迷宫区域
		{
			for (int j = 0; j <= 2*MM; ++j)
			{
				ar<<p[i][j];
			}
		}
		//保存完毕，恢复工作
		p[y][x] = ROAD;//将入口处设置为ROAD
		x = tx;//将玩家放置在原来的位置
		y = ty;
		getmap(5);//重建迷宫区域
	}
	else//打开文档
	{
		iwin = false;//无论当前是否取胜，都设定为未取胜
		//读取文件内容，保存到文档对象中
		ar>>sx>>sy;
		for (int i = 0; i <= 2*NN; ++i)
		{
			for (int j = 0; j <= 2*MM; ++j)
			{
				ar>>p[i][j];
			}
		}
		//初始化迷宫
		x = sx;
		y = sy;
		getmap(0);
	}
}

#ifdef _DEBUG
void CMFCWorldDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCWorldDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif