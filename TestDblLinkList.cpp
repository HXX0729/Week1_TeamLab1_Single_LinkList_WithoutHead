#include "SglLinkList.h"        // 双向循环链表类
#include <unistd.h>
int main(void)
{
/*   SglLinkList<int> l0;
    int a = 1;

    l0.InsertElem(1,a);

    l0.Traverse(Write);
    cout<<"-------------"<<endl;*/
    int x = 99;
    int arr0[]{0,1,2,3};
    SglLinkList<int> la(arr0,4);
    la.InsertElem(x);
    la.InsertElem(1,88);
    la.Traverse(Write);
    cout<<"endend"<<endl;
    SglLinkList<int> lb;
  /*  lb = la;
    lb.Traverse(Write);*/
  la.reversal();
  la.Traverse(Write);




	return 0;		
}
