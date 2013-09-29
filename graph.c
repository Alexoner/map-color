/*************************************************************************
    > File Name: graph.c
    > Author: hao
    > Mail: onerhao@gmail.com
    > Created Time: Sun 23 Dec 2012 12:58:39 AM CST
 ************************************************************************/
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui/highgui_c.h>


#include "graph.h"
#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


int adj[V][V];//adjacency matrix
Position capcity[V];
Vertex vertex[V];


int loadadjmatrix(const char *path1,const char *path2)
{
    int i,j,k;
    //FILE *fp=fopen("vertex.txt","r");
    FILE *fpv=fopen(path1,"r");
    FILE *fpe=fopen(path2,"r");
    assert(fpv);
    assert(fpe);
    memset(adj,0,V*V*sizeof(int));
    for(i=0;i<V&&!feof(fpv);i++)
    {
        fscanf(fpv,"%s%s%s%d%d%d%f",
                vertex[i].proname,
                vertex[i].capname,
                vertex[i].phone_area_code,
                &vertex[i].color,
                &vertex[i].capcity.x,
                &vertex[i].capcity.y,
                &vertex[i].population
              );//read the vertex information
        /*printf("%s %s %s %d %d %d %f\n",vertex[i].proname,vertex[i].capname,vertex[i].phone_area_code,
                    vertex[i].color,vertex[i].capcity.x,vertex[i].capcity.y,
                vertex[i].population);*/
    }
    for(i=0;!feof(fpe);i++)
    {
        fscanf(fpe,"%d%d",&j,&k);//read the vertex
        fscanf(fpe,"%d",&adj[j][k]);//assign the matrix value
        adj[k][j]=adj[j][k];//assign the symetric element
    }
    show_matrix();
    return 1;
}

int saveadjmatrix(const char *path)
{
    int i,j;
    FILE *fp=fopen(path,"w");
    fprintf(fp,"%d\n",V);
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
            fprintf(fp,"%d ",adj[i][j]);
        fprintf(fp,"\n");
    }
    return 0;
}

int colorize_graph()
{//traverse the graph
    int i,j,k;
    int color=0;//color counts from 1 to 4
    int stack[35],top=-1;//use a stack to traverse
    memset(stack,0,sizeof(int)*31);
    stack[++top]=0;
    //starts with 0,pushes the visited vertex into the stack
    vertex[0].color=1;
    while(top>-1)
    {
        i=stack[top];
        for(j=0;j<V&&(adj[i][j]==0||vertex[j].color);j++);
        //find the first connected and not visited vertex.
        if(j==V)
        {//not found
            top--;
            continue;
        }
        else
        {//found one
            for(k=0,color=1;k<V;k++)
            {
                if(adj[j][k]&&vertex[k].color==color)
                {
                    color++;
                    k=-1;
                    continue;
                }
            }
            vertex[j].color=color;
            stack[++top]=j;
            //printf("adj[%d,%d]=%d\n",i,j,adj[i][j]);
        }
    }
    vertex[26].color=vertex[31].color=1;
    printf("\ncolorizing the map of China\n");
    colorize_map();
    return 1;
}



int minspanningtree()
{//Prim algoithm
    Edge e[V-1];
    int i,j,k,min,mini,minj;
    int used[V];
    memset(used,0,V*sizeof(int));
    memset(e,0,E*sizeof(Edge));
    used[0]=1;
    min=65535;
    for(k=0;k<V-1;k++)
    {//V-1 edges
        min=65535;//initialize the minimal value in each loop.
        for(i=0;i<V;i++)
        {
            if(!used[i])
                continue;
            for(j=0;j<V;j++)
            {
                if(adj[i][j]&&used[j]==0)
                {//connected and not circle
                    if(adj[i][j]<min)
                    {
                        min=adj[i][j];
                        mini=i;
                        minj=j;
                    }//update the  minimal value
                }
            }
        }//select the shortest edge
        //printf("\n%dth time\n",k);
        //for(i=0;i<V;i++)
          //  printf("%d ",used[i]);

        if(min==65535)
        {
            break;//biggest connected component solved.
        }
        //e[k]={i,j,adj[i][j]};
        else
        {
            e[k].v1=mini;
            e[k].v2=minj;
            e[k].distance=min;
            used[minj]=1;
        }
    }
    drawline(e,k);
    return 1;
}


int locate_vertex(const char *name,Vertex *vertex)
{
    int i;
    for(i=0;i<V;i++)
    {
        if(!strcmp(name,vertex[i].proname))
            return i;
    }
    return -1;
}


int show_matrix()
{
    int i,j;
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            printf("%d\t",adj[i][j]);
        }
        printf("\n");
    }
    return 1;
}

/*int main(int argc,char **argv)
{
    loadadjmatrix("vertex.txt","edge.txt");
    colorize_graph();
    minspanningtree();
    return 0;
} */
