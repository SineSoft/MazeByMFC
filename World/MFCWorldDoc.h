#pragma once

// MFCWorldDoc.h : CMFCWorldDoc 类的接口
class CMFCWorldDoc : public CDocument,public world
{//本应用程序使用的文档“是”一个文档，也“是”一张地图，双重继承
public:
	virtual ~CMFCWorldDoc(){}
	virtual BOOL OnNewDocument();//新建文档
	virtual void Serialize(CArchive& ar);//序列化

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CMFCWorldDoc():world(MM,NN){}//文档对象只能从序列化创建，初始化基类，限定迷宫大小
	DECLARE_DYNCREATE(CMFCWorldDoc)
	DECLARE_MESSAGE_MAP()// 生成的消息映射函数
};
