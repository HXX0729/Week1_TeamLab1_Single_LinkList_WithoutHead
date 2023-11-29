#ifndef __Sgl_NODE_H__
#define __Sgl_NODE_H__


// 双向链表结点类
template <class ElemType>
struct SglNode 
{
// 数据成员:
	ElemType data;				// 数据域
	SglNode<ElemType> *next;	// 指向后继结点的指针域

// 构造函数:
	SglNode();						// 无数据的构造函数
	SglNode(ElemType item,
	SglNode<ElemType> *nextlink = NULL);// 已知数据域和指针域建立结构
};


// 双向链表结点类的实现部分

template<class ElemType>
SglNode<ElemType>::SglNode()
// 操作结果：构造指针域为空的结点
{

   next = NULL;
}

template<class ElemType>
SglNode<ElemType>::SglNode(ElemType item,

			SglNode<ElemType> *nextlink)
// 操作结果：构造一个数据域为item、next指针域为nextlink的结点
{
   data = item;

   next = nextlink;
}

#endif
