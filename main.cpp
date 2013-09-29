#include <iostream>
#include "Set.h"

using namespace std;

int main()
{
    //int *p=(int*)(0x3d3fe0);
    SET a(9);
    int i,j;
    for(i=0;i<5;i++)
    {
        a.insert(i+1);
    }
    //p[2]=9;
    //cout<<p[2]<<endl;
    for(i=0;i<5;i++)
    {
        if((j=a.has(i+1)))
            cout <<i+1<<endl;
    }
    //a.~SET();
    return 0;
}
