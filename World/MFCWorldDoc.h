#pragma once

// MFCWorldDoc.h : CMFCWorldDoc ��Ľӿ�
class CMFCWorldDoc : public CDocument,public world
{//��Ӧ�ó���ʹ�õ��ĵ����ǡ�һ���ĵ���Ҳ���ǡ�һ�ŵ�ͼ��˫�ؼ̳�
public:
	virtual ~CMFCWorldDoc(){}
	virtual BOOL OnNewDocument();//�½��ĵ�
	virtual void Serialize(CArchive& ar);//���л�

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CMFCWorldDoc():world(MM,NN){}//�ĵ�����ֻ�ܴ����л���������ʼ�����࣬�޶��Թ���С
	DECLARE_DYNCREATE(CMFCWorldDoc)
	DECLARE_MESSAGE_MAP()// ���ɵ���Ϣӳ�亯��
};
