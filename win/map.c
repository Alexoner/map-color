/*************************************************************************
    > File Name: map.cpp
    > Author: hao
    > Mail: onerhao@gmail.com
    > Created Time: Sun 23 Dec 2012 02:16:35 PM CST
 ************************************************************************/
#include <cv.h>
#include <highgui.h>
//#include <opencv2/highgui/highgui_c.h>
#include "graph.h"

int colorize_map()
{
    int i;
    char str[4];
    IplImage *img=cvLoadImage("chinamap.jpg",CV_LOAD_IMAGE_COLOR);
    CvPoint pt;
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, .8, .8, 0, 1, 8);
    CvScalar color[5]=
    {
        CV_RGB(255,0,0),CV_RGB(0,255,0),
        CV_RGB(0,0,255),CV_RGB(0,0,0),CV_RGB(99,76,23)
    };
    if(!img)
    {
        printf("open file chinamap.jpg failed");
    }
    //cvNamedWindow("map of china",CV_WINDOW_AUTOSIZE);
    for(i=0;i<V;i++)
    {
        memcpy(&pt,&vertex[i].capcity,sizeof(CvPoint));
        cvFloodFill(img,pt,color[vertex[i].color-1],
                CV_RGB(25,25,25),CV_RGB(25,25,25),NULL,4,NULL);
        sprintf(str,"%d",vertex[i].color);
        //cvPutText(img,vertex[i].proname,pt,&font,CV_RGB(25,55,255));
        //cvPutText(img,vertex[i].proname,pt,&font,CV_RGB(25,55,255));
        //cvShowImage("map of china",img);
        //cvWaitKey(0);
    }
    //cvShowImage("map of china",img);
    //cvSaveImage("colorized_map.jpg",img,0);
    cvSaveImage("colorized_map.jpg",img);
    //cvWaitKey(0);
    cvReleaseImage(&img);
    //cvDestroyWindow("chinamap.jpg");
    return 1;
}

int drawline(Edge *e,int n)
{
    int i;//index for edge
    int m=0;
    CvPoint pt1,pt2;
    CvScalar color;
    //cvNamedWindow("minimal spanning tree",CV_WINDOW_AUTOSIZE);
    IplImage *img=cvLoadImage("colorized_map.jpg",CV_LOAD_IMAGE_COLOR);
    if(!img)
        img=cvLoadImage("chinamap.jpg",CV_LOAD_IMAGE_COLOR);
    if(!img)
    {
        printf("image not found,exit with error\n");
        return 0;
    }
    //printf("%d %d,%d\n",i,e[i].v1,e[i].v2);
    for(i=0;i<n;i++)
    {
        memcpy(&pt1,&vertex[e[i].v1].capcity,sizeof(CvPoint));
        memcpy(&pt2,&vertex[e[i].v2].capcity,sizeof(CvPoint));
        m+=10;
        color=CV_RGB(255,255,m);
        cvLine(img,pt1,pt2,color,1,8,0);
    }
    cvLine(img,cvPoint(349,283),cvPoint(323,273),color,1,8,0);
    cvLine(img,cvPoint(261,321),cvPoint(278,295),color,1,8,0);
    //cvShowImage("minimal spanning tree",img);
    //cvSaveImage("lined_map.jpg",img,0);
    cvSaveImage("lined_map.jpg",img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    //cvDestroyWindow("minimal spanning tree");
    return 1;
}



