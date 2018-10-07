#include <iostream>
#include "tset.h"

using namespace std;

int main()
{
    TSet t1(10),t2(10);
    cout<<"Input first: "<<endl;
    cin>>t1;
    cout<<"Input second: "<<endl;
    cin>>t2;
    cout<<endl<<"First array: ";
    cout<<t1<<endl;
    cout<<"Second array: ";
    cout<<t2<<endl;
    TSet res1(10),res2(10),res3(10),res4(10),res5(10);
    res1=t1+t2;
    cout<<"A+B "<<res1<<endl;
    res2=t1*t2;
    cout<<"A*B "<<res2<<endl;
    res3=~t1;
    cout<<"~A "<<res3<<endl;
    res4=t1+10;
    cout<<"A+10 "<<res4<<endl;
    res5=t1-7;
    cout<<"A-7 "<<res5<<endl;
    if(t1==t2)
      cout<<"They are equal"<<endl;
    else cout<<"They are not equal"<<endl;
    return 0;
}
