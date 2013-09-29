/*************************************************************************
    > File Name: linkedlist.cpp
    > Author: hao
    > Mail: onerhao@gmail.com
    > Created Time: Sun 23 Dec 2012 05:31:49 PM CST
 ************************************************************************/

int listappend(int x)
{
    struct node *p=(struct node*)malloc(sizeof(struct node));
    if(!p)
        return 0;
    p->a=x;
    p->next=head;
    head=p;
    if(!tail)
        tail=p;
    return 1;
}



