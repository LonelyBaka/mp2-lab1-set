#include <iostream>
#include "tset.h"

using namespace std;

int main()
{
    TBitField bf1(10);
    cout<<"Input first "<<endl;
    cin>>bf1;
    cout<<endl<<"Input second "<<endl;
    TBitField bf2(10);
    cin>>bf2;
    cout<<endl<<"First BitField "<<bf1;
    cout<<"Second BitField "<<bf2;
    TBitField res1(10);
    res1=bf1&bf2;
    cout<<"Result & "<<res1<<endl;
    TBitField res2(10);
    res2=bf1|bf2;
    cout<<"Result | "<<res2<<endl;
    TBitField res3(10);
    res3=~bf1;
    cout<<"Result ~ of first "<<res3<<endl;
    if(bf1==bf2)
        cout<<"They are equal"<<endl;
    if(bf1!=bf2)
        cout<<"They are not equal"<<endl;

    return 0;
}
 
