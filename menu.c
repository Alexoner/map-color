#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "graph.h"

extern Vertex vertex[];

struct list
{
    void *data;
    struct list *next;
};


char *prov_info[PINFO_NUM]=
{
    "省会城市名",
    "电话区号  ",
    "人口数    ",
    "地理位置  "
};



GtkWidget *main_window,*box_main,*box_query,*image;

//callback functions are defined below
//callback functions for main menu
void cb_color(GtkWidget *widget,gpointer data)
{
    colorize_graph();
    printf("cb_color:%p\n",*(GtkWidget**)data);
    gtk_image_set_from_file(GTK_IMAGE(*(GtkWidget**)data),"colorized_map.jpg");
    gtk_widget_show(image);
}

void cb_tree(GtkWidget *widget,gpointer data)
{
    if(minspanningtree())
    {
        gtk_image_set_from_file(GTK_IMAGE(*(GtkWidget**)data),"lined_map.jpg");
        printf("cb_tree:%p\n",*(GtkWidget**)data);
    }
    gtk_widget_show(image);
    return ;
}

void cb_info(GtkWidget *widget,gpointer data)
{
    static int i=0,width,height;
    i++;
    //gtk_widget_hide(box_main);
    if(i%2)
    {
        gtk_window_get_size(GTK_WINDOW(main_window),&width,&height);
        printf("%d,%d\n",width,height);
        gtk_widget_show_all(box_query);
    }
    else
    {
        gtk_widget_hide_all(box_query);
        gtk_window_resize(GTK_WINDOW(main_window),width,height);
    }
    printf("cb_info:%p\n",box_query);
}

void cb_quit(GtkWidget *widget,gpointer data)
{
    gtk_main_quit();
}
//end for callbacks for main menu
//callbacks for query menu

void cb_query_capname(GtkWidget *widget,gpointer data)
{
    int i;
    const char *name=gtk_entry_get_text(GTK_ENTRY(
                *(GtkWidget**)(((struct list*)data)->data)));
    i=locate_vertex(name,vertex);
    if(i+1)
    {
        gtk_entry_set_text(GTK_ENTRY(
                    *(GtkWidget**)(((struct list*)data)->next->data)),
                    vertex[i].capname);
    }
}

void cb_query_phone_code(GtkWidget *widget,gpointer data)
{
    const char *name=gtk_entry_get_text(GTK_ENTRY(
                *(GtkWidget**)(((struct list*)data)->data)));
    int i=locate_vertex(name,vertex);
    if(i+1)
    {
        gtk_entry_set_text(GTK_ENTRY(
                    *(GtkWidget**)(((struct list*)data)->next->data)),
                vertex[i].phone_area_code);
    }
}

void cb_query_population(GtkWidget *widget,gpointer data)
{
    const char *name=gtk_entry_get_text(GTK_ENTRY(
                *(GtkWidget**)(((struct list*)data)->data)));
    char str[18];
    int i=locate_vertex(name,vertex);
    if(i+1)
    {
        sprintf(str,"%.0f",vertex[i].population);
        gtk_entry_set_text(GTK_ENTRY(
                    *(GtkWidget **)(((struct list*)data)->next->data)),
                str);
    }
}

void cb_query_location(GtkWidget *widget,gpointer data)
{
    const char *name=gtk_entry_get_text(GTK_ENTRY(
                *(GtkWidget**)(((struct list*)data)->data)));
    int i=locate_vertex(name,vertex);
    if(i+1)
    {
        gtk_entry_set_text(GTK_ENTRY(
                    *(GtkWidget **)(((struct list*)data)->next->data)),
                "location");
    }
}
//end for callbacks for query
//end for callbacks

GtkWidget * query_box()
{
    int i,j;
    GtkWidget *vbox,*hbox;
    GtkWidget *entrynum,*entry[PINFO_NUM],*buttons[PINFO_NUM+2],*label;
    //entrynum is for the province number.

    GtkWidget *table=gtk_table_new(5,2,FALSE);
    struct list *head[PINFO_NUM],*p=NULL;

    void (*cb_query[PINFO_NUM])(GtkWidget *widget,
            gpointer data)=
    {
        cb_query_capname,
        cb_query_phone_code,
        cb_query_population,
        cb_query_location
    };

    memset(head,0,PINFO_NUM*sizeof(struct list*));
    vbox=gtk_vbox_new(FALSE,0);
    hbox=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
    label=gtk_label_new("District name");
    gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,0,1);
    entrynum=gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entrynum,1,2,0,1);

    gtk_box_pack_start(GTK_BOX(vbox),table,FALSE,FALSE,0);



    for(i=0; i<PINFO_NUM; i++)
    {
        //hbox=gtk_hbox_new(FALSE,0);
        //gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,0);
        entry[i]=gtk_entry_new();

        p=(struct list*)malloc(sizeof(struct list));
        p->data=malloc(sizeof(GtkWidget *));
        *(GtkWidget**)p->data=entry[i];//output entry
        p->next=head[i];
        head[i]=p;

        p=(struct list*)malloc(sizeof(struct list));
        p->data=malloc(sizeof(GtkWidget *));
        *(GtkWidget**)p->data=entrynum;//input entry
        p->next=head[i];
        head[i]=p;

        buttons[i]=gtk_button_new_with_label(prov_info[i]);
        gtk_table_attach_defaults(GTK_TABLE(table),buttons[i],0,1,i+1,i+2);
        g_signal_connect(buttons[i],"clicked",G_CALLBACK(cb_query[i]),head[i]);
        //gtk_box_pack_start(GTK_BOX(hbox),buttons[i],TRUE,TRUE,0);

        gtk_table_attach_defaults(GTK_TABLE(table),entry[i],1,2,i+1,i+2);
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
        gtk_entry_set_width_chars(GTK_ENTRY(entry[i]),10);
    }

    return vbox;
}


GtkWidget *main_box()
{
    int i;
    GtkWidget *vbox,*hbox,*button[FUN_NUM];
    gpointer data[]=
    {
        &image,
        &image,
        box_query,
        NULL
    };
    void (*fun[FUN_NUM])(GtkWidget *,gpointer)=
    {
        cb_color,
        cb_tree,
        cb_info,
        cb_quit
    };

    char *fun_name[]=
    {
        "染色求解",
        "建立通信网络",
        "查询省份信息",
        "退出系统"
    };
    vbox=gtk_vbox_new(FALSE,0);
    for(i=0; i<FUN_NUM; i++)
    {
        hbox=gtk_hbox_new(FALSE,0);
        button[i]=gtk_button_new_with_label(fun_name[i]);
        g_signal_connect(button[i],"clicked",G_CALLBACK(fun[i]),data[i]);
        gtk_box_pack_start(GTK_BOX(hbox),button[i],TRUE,TRUE,0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
    }
    return vbox;
}

int main_menu()
{
    GtkWidget *vbox=gtk_vbox_new(FALSE,0);
    main_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //gtk_window_resize(GTK_WINDOW(main_window),400,400);
    image=gtk_image_new_from_file("chinamap.jpg");
    //printf("184:%p\n",image);
    box_query=query_box();
    box_main=main_box();


    gtk_container_add(GTK_CONTAINER(main_window),vbox);

    gtk_box_pack_start(GTK_BOX(vbox),image,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box_main,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box_query,FALSE,FALSE,0);

    gtk_widget_show(image);
    gtk_widget_show_all(box_main);
    //gtk_widget_show_all(box_query);
    gtk_widget_show(vbox);
    gtk_widget_show(main_window);
    gtk_main();
    return 1;
}

int main(int argc,char **argv)
{
    gtk_init(&argc,&argv);
    loadadjmatrix("vertex.txt","edge.txt");
    main_menu();
    return 1;
}
