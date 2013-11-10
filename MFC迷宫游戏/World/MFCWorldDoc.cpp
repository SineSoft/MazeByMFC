// MFCWorldDoc.cpp : CMFCWorldDoc ���ʵ��
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
	creatworld();//�������Թ�
	return TRUE;
}

// CMFCWorldDoc ���л�
void CMFCWorldDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())//�����ĵ�
	{
		int tx = x,ty = y;//����ʱ�������浱ǰ�������λ��
		getmap(0);//���õ�ͼ
		ar<<sx<<sy;//�����ļ����������λ��
		for (int i = 0; i <= 2*NN; ++i)//�����Թ�����
		{
			for (int j = 0; j <= 2*MM; ++j)
			{
				ar<<p[i][j];
			}
		}
		//������ϣ��ָ�����
		p[y][x] = ROAD;//����ڴ�����ΪROAD
		x = tx;//����ҷ�����ԭ����λ��
		y = ty;
		getmap(5);//�ؽ��Թ�����
	}
	else//���ĵ�
	{
		iwin = false;//���۵�ǰ�Ƿ�ȡʤ�����趨Ϊδȡʤ
		//��ȡ�ļ����ݣ����浽�ĵ�������
		ar>>sx>>sy;
		for (int i = 0; i <= 2*NN; ++i)
		{
			for (int j = 0; j <= 2*MM; ++j)
			{
				ar>>p[i][j];
			}
		}
		//��ʼ���Թ�
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