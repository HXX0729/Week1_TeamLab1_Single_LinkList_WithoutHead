#ifndef __Sgl_NODE_H__
#define __Sgl_NODE_H__


// ˫����������
template <class ElemType>
struct SglNode 
{
// ���ݳ�Ա:
	ElemType data;				// ������
	SglNode<ElemType> *next;	// ָ���̽���ָ����

// ���캯��:
	SglNode();						// �����ݵĹ��캯��
	SglNode(ElemType item,
	SglNode<ElemType> *nextlink = NULL);// ��֪�������ָ�������ṹ
};


// ˫�����������ʵ�ֲ���

template<class ElemType>
SglNode<ElemType>::SglNode()
// �������������ָ����Ϊ�յĽ��
{

   next = NULL;
}

template<class ElemType>
SglNode<ElemType>::SglNode(ElemType item,

			SglNode<ElemType> *nextlink)
// �������������һ��������Ϊitem��nextָ����Ϊnextlink�Ľ��
{
   data = item;

   next = nextlink;
}

#endif
