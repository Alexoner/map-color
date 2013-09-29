#include "set.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

SET::SET(int card)
{
    set=(int *)malloc(sizeof(int)*card);
    SET::card=card;
    //cout<<&(SET::card)<<","<<&card<<endl;
    used=0;
}

SET::~SET()
{
    //cout<<"destructor\n";
    free(set);
    card=0;
    used=0;
}

int SET::size()
{
    return used;
}

int SET::insert(int v)
{
    if(used>=card)
        return 0;
    set[used++]=v;
    return 1;
}

int SET::remove(int v)
{
    int i,j;
    for(i=0;i<used-1&&set[i+1]!=v;i++);
    if(i==used-1)
    {
        return 0;
    }
    else
    {
        for(;i<used-1;i++)
        {
            set[i]=set[i+1];
        }
        used--;
    }
    return 1;
}

int SET::has(int v)
{
    int i;
    for(i=0;i<used&&set[i]!=v;i++);
    if(i==used)
        return 0;
    else
    {
        return 1;
    }
}
