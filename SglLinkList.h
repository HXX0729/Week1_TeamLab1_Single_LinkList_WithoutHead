#ifndef __Sgl_LK_LIST_H__
#define __Sgl_LK_LIST_H__

#include "Assistance.h"				// 辅助软件包
#include "SglNode.h"				// 双向链表结点类

// 双向链表类
template <class ElemType>
class SglLinkList 
{
protected:
//  循环链表的数据成员:
	SglNode<ElemType> *head;			// 头结点指针
	int length;							// 元素个数

public:
	SglLinkList();				        // 无参数的构造函数
	SglLinkList(ElemType v[], int n);	// 有参数的构造函数
 	virtual ~SglLinkList();		        // 析构函数
	int GetLength() const;			    // 求循环链表长度			 
	bool IsEmpty() const;			    // 判断循环链表是否为空
	void Clear();				        // 将循环链表清空
	void Traverse(void (*Visit)(const ElemType &)) const;// 遍历循环链表
	int LocateElem(const ElemType &e);	// 元素定位 
	Status GetElem(int i, ElemType &e) const;	 // 取指定位置的元素	
	Status SetElem(int i, const ElemType &e);	// 设置指定位置的元素值
	Status DeleteElem(int i, ElemType &e);		// 删除元素		
	Status InsertElem(int i, const ElemType &e);// 在任意位置插入元素
	Status InsertElem(const ElemType &e);	    // 在表尾插入元素
	SglLinkList(const SglLinkList<ElemType> &la);// 复制构造函数
	SglLinkList<ElemType> &operator =(const SglLinkList<ElemType> &la); // 重载赋值运算
    Status InserElemByOrder(const ElemType& e);
    Status reversal();
};


// 链表类的实现部分
template <class ElemType>
SglLinkList<ElemType>::SglLinkList()
// 操作结果：构造一个空链表
{
	head = new SglNode<ElemType>;	// 构造头指针
    head->data == NULL;
    head->next = head;
	assert(head);                   // 构造头结点失败，终止程序运行
	length = 0;						// 初始化元素个数
}

template <class ElemType>
SglLinkList<ElemType>::SglLinkList(ElemType v[], int n)
// 操作结果：根据数组v中的元素，构造循环链表
{
    SglNode<ElemType> *p;
	p = head =  new SglNode<ElemType>;	// 构造头结点 
	assert(head);// 构造头结点失败，终止程序运行
    p->data = v[0];

    if(n>=2) {
        for (int i = 1; i < n; i++) {
            p->next = new SglNode<ElemType>(v[i], p);
            assert(p->next);                // 构造元素结点失败，终止程序运行
            p = p->next;
        }
    }
	length = n;						    // 初始化元素个数
    p->next = head;	                    //尾结点的next指向头结点 
}

template <class ElemType>
SglLinkList<ElemType>::~SglLinkList()
// 操作结果：销毁循环链表
{
	Clear();			// 清空循环链表
}

template <class ElemType>
int SglLinkList<ElemType>::GetLength() const
// 操作结果：返回循环链表元素个数
{
	return length;
}


template <class ElemType>
bool SglLinkList<ElemType>::IsEmpty() const
// 操作结果：如循环链表为空，则返回true，否则返回false
{
	return head->next == head;
}

template <class ElemType>
void SglLinkList<ElemType>::Clear()
// 操作结果：清空循环链表
{

	ElemType tmpElem;	// 临时元素值
    //head->data == NULL;
	while (length > 0)	// 循环链表非空，则删除第1个元素
		DeleteElem(1, tmpElem);
}

template <class ElemType>
void SglLinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对循环链表的每个元素调用函数(*visit)
{
    SglNode<ElemType> *p;
	for (p = head; p->next != head; p = p->next)		// 用p依次访问每个元素
		(*Visit)(p->data);	// 对循环链表的每个元素调用函数(*visit)
    (*Visit)(p->data);
}


template <class ElemType>
int SglLinkList<ElemType>::LocateElem(const ElemType &e)
// 操作结果：返回指定元素在循环链表中第一次出现的序号，如果不存在返回0 
{
    SglNode<ElemType> *p = head;//不带头节点
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
    if(length == 0 || length ==1){        //鲁棒性
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
    cur->next = pre;    //当 cur 指向最后一个节点的话，由于已经退出了 while 循环，所以需要单独处理
    head = cur;   //头指针指向最后一个节点，把原来的NULL 换成最后一个节点的地址，使之成环
return SUCCESS;
}


template <class ElemType>
Status SglLinkList<ElemType>::GetElem(int i, ElemType &e) const
// 操作结果：当循环链表存在第i个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
    SglNode<ElemType> *p = head;
    int count;
	if (i < 1 || i > length)		// i范围错
		return NOT_PRESENT;				
	else	{	// i合法
		for (count = 1; count < i; count++)
		  p = p->next;	            // p指向第i个结点	
		e = p->data;				// 用e返回第i个元素的值
		return ENTRY_FOUND;
	}
}


template <class ElemType>
Status SglLinkList<ElemType>::SetElem(int i, const ElemType &e)
// 操作结果：将循环链表的第i个位置的元素赋值为e,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
    SglNode<ElemType> *p = head;
    int count;
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else	{	// i合法
		for (count = 1; count < i; count++)
		  p = p->next;	// p指向第i个结点	
		p->data = e;	// 设置第i个元素的值
		return SUCCESS;
	}
}

/*template <class ElemType>
Status SglLinkList<ElemType>::DeleteElem(int i, ElemType &e)
// 操作结果：删除循环链表的第i个位置的元素, 并用e返回其值,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
    SglNode<ElemType> *p = head;
    int count;
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else	{	// i合法
		for (count = 1; count < i; count++)
		  p = p->next;	// p指向第i个结点
		e = p->data;				// 用e返回被删结点元素值
		length--;					// 删除成功后元素个数减1 
		delete p;				    // 释放被删结点
		return SUCCESS;
	}
}*/
template <class ElemType>
Status SglLinkList<ElemType>::DeleteElem(int i, ElemType &e)
// 操作结果：删除单链表的第i个位置的元素, 并用e返回其值,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
    if (i < 1 || i > length)
        return RANGE_ERROR;   // i范围错
    else	{
        SglNode<ElemType> *p = head, *q;
        int count;
        for (count = 1; count < i; count++)
            p = p->next;	      // p指向第i-1个结点
        q = p->next;	      // q指向第i个结点
        p->next = q->next;	  // 删除结点
        e = q->data;		  // 用e返回被删结点元素值
        length--;			  // 删除成功后元素个数减1
        delete q;			  // 释放被删结点
        return SUCCESS;
    }
}

template <class ElemType>
Status SglLinkList<ElemType>::InsertElem(int i, const ElemType &e)
// 操作结果：在单链表的第i个位置前插入元素e
//	i的取值范围为1≤i≤length+1
//	i合法时返回SUCCESS, 否则函数返回RANGE_ERROR
{
    if (i < 1 || i > length+1)
        return RANGE_ERROR;
    else	{
        SglNode<ElemType> *p = head, *q;
        int count;
        if(i==1){
            SglNode<ElemType>* end = head;//备份最后一个节点，以便后续使之指向新创建的头节点 q
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
            p = p->next;	                    // p指向第i-1个结点	
        q = new SglNode<ElemType>(e, p->next); // 生成新结点q
        assert(q);                          // 申请结点失败，终止程序运行 
        p->next = q;				        // 将q插入到链表中
        length++;							// 插入成功后，单链表长度加1 
        return SUCCESS;
    }
}

template <class ElemType>
Status SglLinkList<ElemType>::InsertElem(const ElemType &e)
// 操作结果：在单链表的表尾位置插入元素e
{   if(length==0){head->data = e;return  SUCCESS;}
    SglNode<ElemType> *p, *q;
    q = new SglNode<ElemType>(e, head);    // 生成新结点q
    assert(q);                          // 申请结点失败，终止程序运行 
    for (p = head; p->next != head; p = p->next) ;	// p指向表尾结点
    p->next = q;                        // 在单链表的表尾位置插入新结点 
    length++;							// 插入成功后，单链表长度加1 
    return SUCCESS;
}


template <class ElemType>
SglLinkList<ElemType>::SglLinkList(const SglLinkList<ElemType> &la)
// 操作结果：复制构造函数，由单链表la构造新单链表
{
    int laLength = la.GetLength();	// 取被复制单链表的长度
    SglNode<ElemType> *p, *q;
    ElemType e;
    head = new SglNode<ElemType>;		// 构造头指针
    assert(head);                   // 构造头指针失败，终止程序运行
    if(laLength==0) {head->data=NULL;head->next=head;}
    else{
        p=head;q=la.head;
        p->data=q->data;
        for (int i = 2; i <= laLength; i++)		// 复制数据元素
            {
                p->next = new SglNode<ElemType>(q->next->data, p);
                assert(p->next);                // 构造元素结点失败，终止程序运行
                p = p->next;
                q=q->next;
        }
        length=laLength;
        p->next = head;	                    //尾结点的next指向头结点

    }
}

////有 bug，还没修
//template <class ElemType>
//SglLinkList<ElemType> &SglLinkList<ElemType>::operator =(const SglLinkList<ElemType> &la)
//// 操作结果：重载赋值运算符，将单链表la赋值给当前单链表
//{
//	if (&la != this)	{
//		int laLength = la.GetLength();// 取被赋值单链表的长度
//		ElemType e;
//		Clear();							// 清空当前单链表
//		for (int i = 1; i <= laLength; i++)		{
//			la.GetElem(i, e);		    // 取出第i个元素的值放在e中
//			InsertElem(e);		            // 将e插入到当前单链表的表尾
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
