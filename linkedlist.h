/*************************************************************************
    > File Name: linkedlist.h
    > Author: hao
    > Mail: onerhao@gmail.com
    > Created Time: Sun 23 Dec 2012 05:31:49 PM CST
 ************************************************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node
{
    int a;
    list *next;
};

class List
{
    private:
        struct node *head;
        struct node *tail;
    public:
        List();//constructor
        ~List();//destructor
        int append(int x);//append a node
        int remove(int x);//remove a node
        int has(int y);//whether the list has y
}

