#ifndef __Sgl_LK_LIST_H__
#define __Sgl_LK_LIST_H__

#include "Assistance.h"				// ���������
#include "SglNode.h"				// ˫����������

// ˫��������
template <class ElemType>
class SglLinkList 
{
protected:
//  ѭ����������ݳ�Ա:
	SglNode<ElemType> *head;			// ͷ���ָ��
	int length;							// Ԫ�ظ���

public:
	SglLinkList();				        // �޲����Ĺ��캯��
	SglLinkList(ElemType v[], int n);	// �в����Ĺ��캯��
 	virtual ~SglLinkList();		        // ��������
	int GetLength() const;			    // ��ѭ��������			 
	bool IsEmpty() const;			    // �ж�ѭ�������Ƿ�Ϊ��
	void Clear();				        // ��ѭ���������
	void Traverse(void (*Visit)(const ElemType &)) const;// ����ѭ������
	int LocateElem(const ElemType &e);	// Ԫ�ض�λ 
	Status GetElem(int i, ElemType &e) const;	 // ȡָ��λ�õ�Ԫ��	
	Status SetElem(int i, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	Status DeleteElem(int i, ElemType &e);		// ɾ��Ԫ��		
	Status InsertElem(int i, const ElemType &e);// ������λ�ò���Ԫ��
	Status InsertElem(const ElemType &e);	    // �ڱ�β����Ԫ��
	SglLinkList(const SglLinkList<ElemType> &la);// ���ƹ��캯��
	SglLinkList<ElemType> &operator =(const SglLinkList<ElemType> &la); // ���ظ�ֵ����
    Status InserElemByOrder(const ElemType& e);
    Status reversal();
};


// �������ʵ�ֲ���
template <class ElemType>
SglLinkList<ElemType>::SglLinkList()
// �������������һ��������
{
	head = new SglNode<ElemType>;	// ����ͷָ��
    head->data == NULL;
    head->next = head;
	assert(head);                   // ����ͷ���ʧ�ܣ���ֹ��������
	length = 0;						// ��ʼ��Ԫ�ظ���
}

template <class ElemType>
SglLinkList<ElemType>::SglLinkList(ElemType v[], int n)
// �����������������v�е�Ԫ�أ�����ѭ������
{
    SglNode<ElemType> *p;
	p = head =  new SglNode<ElemType>;	// ����ͷ��� 
	assert(head);// ����ͷ���ʧ�ܣ���ֹ��������
    p->data = v[0];

    if(n>=2) {
        for (int i = 1; i < n; i++) {
            p->next = new SglNode<ElemType>(v[i], p);
            assert(p->next);                // ����Ԫ�ؽ��ʧ�ܣ���ֹ��������
            p = p->next;
        }
    }
	length = n;						    // ��ʼ��Ԫ�ظ���
    p->next = head;	                    //β����nextָ��ͷ��� 
}

template <class ElemType>
SglLinkList<ElemType>::~SglLinkList()
// �������������ѭ������
{
	Clear();			// ���ѭ������
}

template <class ElemType>
int SglLinkList<ElemType>::GetLength() const
// �������������ѭ������Ԫ�ظ���
{
	return length;
}


template <class ElemType>
bool SglLinkList<ElemType>::IsEmpty() const
// �����������ѭ������Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

template <class ElemType>
void SglLinkList<ElemType>::Clear()
// ������������ѭ������
{

	ElemType tmpElem;	// ��ʱԪ��ֵ
    //head->data == NULL;
	while (length > 0)	// ѭ������ǿգ���ɾ����1��Ԫ��
		DeleteElem(1, tmpElem);
}

template <class ElemType>
void SglLinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// ������������ζ�ѭ�������ÿ��Ԫ�ص��ú���(*visit)
{
    SglNode<ElemType> *p;
	for (p = head; p->next != head; p = p->next)		// ��p���η���ÿ��Ԫ��
		(*Visit)(p->data);	// ��ѭ�������ÿ��Ԫ�ص��ú���(*visit)
    (*Visit)(p->data);
}


template <class ElemType>
int SglLinkList<ElemType>::LocateElem(const ElemType &e)
// �������������ָ��Ԫ����ѭ�������е�һ�γ��ֵ���ţ���������ڷ���0 
{
    SglNode<ElemType> *p = head;//����ͷ�ڵ�
    int count=1;
    if(p->data==e)
        return count;
    p=p->next;
    count++;
	while (p != head && p->data != e) {
	    count++;
		p = p->next;
	}
	if (p != head)
	    return count;
    else 
        return 0;
}

template<class ElemType>
Status SglLinkList<ElemType>::reversal() {
    if(length == 0 || length ==1){        //³����
        return SUCCESS;
    }

    SglNode<ElemType>* cur = head;
     SglNode<ElemType>* pre = cur;
     while(pre->next!=head){
         pre=pre->next;
     }
    SglNode<ElemType>* fut = nullptr;

    while(cur->next!=head){
        fut = cur->next;
        cur->next = pre;
        pre = cur;
        cur = fut;
    }
    cur->next = pre;    //�� cur ָ�����һ���ڵ�Ļ��������Ѿ��˳��� while ѭ����������Ҫ��������
    head = cur;   //ͷָ��ָ�����һ���ڵ㣬��ԭ����NULL �������һ���ڵ�ĵ�ַ��ʹ֮�ɻ�
return SUCCESS;
}


template <class ElemType>
Status SglLinkList<ElemType>::GetElem(int i, ElemType &e) const
// �����������ѭ��������ڵ�i��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
    SglNode<ElemType> *p = head;
    int count;
	if (i < 1 || i > length)		// i��Χ��
		return NOT_PRESENT;				
	else	{	// i�Ϸ�
		for (count = 1; count < i; count++)
		  p = p->next;	            // pָ���i�����	
		e = p->data;				// ��e���ص�i��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}


template <class ElemType>
Status SglLinkList<ElemType>::SetElem(int i, const ElemType &e)
// �����������ѭ������ĵ�i��λ�õ�Ԫ�ظ�ֵΪe,
//	i��ȡֵ��ΧΪ1��i��length,
//	i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
    SglNode<ElemType> *p = head;
    int count;
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else	{	// i�Ϸ�
		for (count = 1; count < i; count++)
		  p = p->next;	// pָ���i�����	
		p->data = e;	// ���õ�i��Ԫ�ص�ֵ
		return SUCCESS;
	}
}

/*template <class ElemType>
Status SglLinkList<ElemType>::DeleteElem(int i, ElemType &e)
// ���������ɾ��ѭ������ĵ�i��λ�õ�Ԫ��, ����e������ֵ,
//	i��ȡֵ��ΧΪ1��i��length,
//	i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
    SglNode<ElemType> *p = head;
    int count;
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else	{	// i�Ϸ�
		for (count = 1; count < i; count++)
		  p = p->next;	// pָ���i�����
		e = p->data;				// ��e���ر�ɾ���Ԫ��ֵ
		length--;					// ɾ���ɹ���Ԫ�ظ�����1 
		delete p;				    // �ͷű�ɾ���
		return SUCCESS;
	}
}*/
template <class ElemType>
Status SglLinkList<ElemType>::DeleteElem(int i, ElemType &e)
// ���������ɾ��������ĵ�i��λ�õ�Ԫ��, ����e������ֵ,
//	i��ȡֵ��ΧΪ1��i��length,
//	i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
    if (i < 1 || i > length)
        return RANGE_ERROR;   // i��Χ��
    else	{
        SglNode<ElemType> *p = head, *q;
        int count;
        for (count = 1; count < i; count++)
            p = p->next;	      // pָ���i-1�����
        q = p->next;	      // qָ���i�����
        p->next = q->next;	  // ɾ�����
        e = q->data;		  // ��e���ر�ɾ���Ԫ��ֵ
        length--;			  // ɾ���ɹ���Ԫ�ظ�����1
        delete q;			  // �ͷű�ɾ���
        return SUCCESS;
    }
}

template <class ElemType>
Status SglLinkList<ElemType>::InsertElem(int i, const ElemType &e)
// ����������ڵ�����ĵ�i��λ��ǰ����Ԫ��e
//	i��ȡֵ��ΧΪ1��i��length+1
//	i�Ϸ�ʱ����SUCCESS, ����������RANGE_ERROR
{
    if (i < 1 || i > length+1)
        return RANGE_ERROR;
    else	{
        SglNode<ElemType> *p = head, *q;
        int count;
        if(i==1){
            SglNode<ElemType>* end = head;//�������һ���ڵ㣬�Ա����ʹָ֮���´�����ͷ�ڵ� q
            for(end;end->next!=head;end=end->next);

            q = new SglNode<ElemType>(e, head);
            head = q;
            length++;

            end->next = q;
            return SUCCESS;

        }
        if(i==2){
            q = new SglNode<ElemType>(e, head->next);
            head->next = q;
            length++;
            return SUCCESS;

        }
        for (count = 2; count < i; count++)
            p = p->next;	                    // pָ���i-1�����	
        q = new SglNode<ElemType>(e, p->next); // �����½��q
        assert(q);                          // ������ʧ�ܣ���ֹ�������� 
        p->next = q;				        // ��q���뵽������
        length++;							// ����ɹ��󣬵������ȼ�1 
        return SUCCESS;
    }
}

template <class ElemType>
Status SglLinkList<ElemType>::InsertElem(const ElemType &e)
// ����������ڵ�����ı�βλ�ò���Ԫ��e
{   if(length==0){head->data = e;return  SUCCESS;}
    SglNode<ElemType> *p, *q;
    q = new SglNode<ElemType>(e, head);    // �����½��q
    assert(q);                          // ������ʧ�ܣ���ֹ�������� 
    for (p = head; p->next != head; p = p->next) ;	// pָ���β���
    p->next = q;                        // �ڵ�����ı�βλ�ò����½�� 
    length++;							// ����ɹ��󣬵������ȼ�1 
    return SUCCESS;
}


template <class ElemType>
SglLinkList<ElemType>::SglLinkList(const SglLinkList<ElemType> &la)
// ������������ƹ��캯�����ɵ�����la�����µ�����
{
    int laLength = la.GetLength();	// ȡ�����Ƶ�����ĳ���
    SglNode<ElemType> *p, *q;
    ElemType e;
    head = new SglNode<ElemType>;		// ����ͷָ��
    assert(head);                   // ����ͷָ��ʧ�ܣ���ֹ��������
    if(laLength==0) {head->data=NULL;head->next=head;}
    else{
        p=head;q=la.head;
        p->data=q->data;
        for (int i = 2; i <= laLength; i++)		// ��������Ԫ��
            {
                p->next = new SglNode<ElemType>(q->next->data, p);
                assert(p->next);                // ����Ԫ�ؽ��ʧ�ܣ���ֹ��������
                p = p->next;
                q=q->next;
        }
        length=laLength;
        p->next = head;	                    //β����nextָ��ͷ���

    }
}

////�� bug����û��
//template <class ElemType>
//SglLinkList<ElemType> &SglLinkList<ElemType>::operator =(const SglLinkList<ElemType> &la)
//// ������������ظ�ֵ���������������la��ֵ����ǰ������
//{
//	if (&la != this)	{
//		int laLength = la.GetLength();// ȡ����ֵ������ĳ���
//		ElemType e;
//		Clear();							// ��յ�ǰ������
//		for (int i = 1; i <= laLength; i++)		{
//			la.GetElem(i, e);		    // ȡ����i��Ԫ�ص�ֵ����e��
//			InsertElem(e);		            // ��e���뵽��ǰ������ı�β
//		}
//	}
//	return *this;
//}
template <class ElemType>
SglLinkList<ElemType>& SglLinkList<ElemType>::operator=(const SglLinkList<ElemType> &la)
{
    if (this != &la) {

        Clear();

        int laLength = la.GetLength();
        SglNode<ElemType> *p, *q;
        ElemType e;
        head = new SglNode<ElemType>;
        assert(head);
        if (laLength == 0) {
            head->data = NULL;
            head->next = head;
        } else {
            p = head;
            q = la.head;
            p->data = q->data;
            for (int i = 2; i <= laLength; i++) {
                p->next = new SglNode<ElemType>(q->next->data, p);
                assert(p->next);
                p = p->next;
                q = q->next;
            }
            length = laLength;
            p->next = head;
        }
    }
    return *this;
}


#endif
