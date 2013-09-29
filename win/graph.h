/*************************************************************************
    > File Name: graph.h
    > Author: hao
    > Mail: onerhao@gmail.com
    > Created Time: Sat 22 Dec 2012 11:50:11 PM CST
 ************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#define V 32
#define E 20


typedef struct Position
{
    int x;
    int y;
}Position;

typedef struct Vertex
{
    char proname[20];//province name,etc
    char capname[20];//capital city name;
    char phone_area_code[5];//phone area code of capital city
    int color;//color painted
    Position capcity;//location of capital city
    float population;//population
}Vertex;//vertex type

typedef struct Edge
{
    int v1;
    int v2;
    int distance;
}Edge;

extern int adj[V][V];
extern Position capcity[V];
extern Vertex vertex[V];

Position position(int x,int y);

int loadadjmatrix(const char *path1,const char*path2);//load the graph from a file
int saveadjmatrix(const char *path);//save the graph
int colorize_graph();//colorize the graph
int minspanningtree();
int locate_vertex(const char *name,Vertex *vertex);
#endif
