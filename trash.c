/*************************************************************************
    > File Name: trash.c
    > Author: hao
    > Mail: onerhao@gmail.com
    > Created Time: Tue 25 Dec 2012 09:26:17 PM CST
 ************************************************************************/
/*int colorize_graph()
{//traverse the graph
    int i,j,k;
    int color=0;//color counts from 1 to 4
    int stack[31],top=-1;//use a stack to traverse
    memset(stack,0,sizeof(int)*31);
    stack[++top]=0;
    //starts with 0,pushes the visited vertex into the stack
    vertex[0].color=1;
    char str[4];
    IplImage *img=cvLoadImage("chinamap.jpg",CV_LOAD_IMAGE_COLOR);
    CvPoint pt;
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, .8, .8, 0, 1, 8);
    CvScalar cvcolor[5]=
    {
        CV_RGB(255,0,0),CV_RGB(0,255,0),
        CV_RGB(0,0,255),CV_RGB(0,0,0),CV_RGB(99,76,23)
    };
    if(!img)
    {
        printf("open file chinamap.jpg failed");
    }
    cvNamedWindow("map of china",CV_WINDOW_AUTOSIZE);
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
            memcpy(&pt,&vertex[j].capcity,sizeof(CvPoint));
            cvFloodFill(img,pt,cvcolor[vertex[j].color-1],
                    CV_RGB(20,20,20),CV_RGB(20,20,20),NULL,4,NULL);
            sprintf(str,"%d",vertex[j].color);
            //cvPutText(img,vertex[j].proname,pt,&font,CV_RGB(25,55,255));
            cvPutText(img,str,pt,&font,CV_RGB(25,55,255));
            cvShowImage("map of china",img);
            stack[++top]=j;
            printf("adj[%d,%d]=%d\n",i,j,adj[i][j]);
            //cvWaitKey(0);
        }
    }
    cvShowImage("map of china",img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyWindow("chinamap.jpg");
    return 1;
}*/

