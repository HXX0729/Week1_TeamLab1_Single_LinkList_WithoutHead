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
    la.SetElem(1,55);
    la.InsertElem(1,88);
    la.Traverse(Write);
    cout<<endl<<la.LocateElem(99)<<" "<<la.LocateElem(88)<<" "<<la.LocateElem(2);
    la.GetElem(6,x);

    cout<<endl<<x;
    cout<<"endend"<<endl;
    la.Traverse(Write);
    cout<<endl;
    SglLinkList<int> lb=la;
    cout<<lb.IsEmpty()<<" "<<la.IsEmpty()<<endl;
    lb.reversal();               //reversal似乎还有bug
    lb.Traverse(Write);
    cout<<endl;
  /*  lb = la;
    lb.Traverse(Write);*/
  //la.reversal();
  //la.Traverse(Write);




	return 0;		
}
