CC=gcc  
#CVLIBS=`pkg-config --libs opencv`
#CVLIBS= /usr/local/lib/libopencv_contrib.a /usr/local/lib/libopencv_stitching.a /usr/local/lib/libopencv_ts.a /usr/local/lib/libopencv_videostab.a /usr/local/lib/libopencv_gpu.a /usr/local/lib/libopencv_legacy.a /usr/local/lib/libopencv_ml.a /usr/local/lib/libopencv_nonfree.a /usr/local/lib/libopencv_objdetect.a /usr/local/lib/libopencv_calib3d.a /usr/local/lib/libopencv_photo.a /usr/local/lib/libopencv_video.a /usr/local/lib/libopencv_features2d.a /usr/local/lib/libopencv_highgui.a /usr/local/share/OpenCV/3rdparty/lib/libIlmImf.a /usr/local/lib/libopencv_flann.a /usr/local/lib/libopencv_imgproc.a /usr/local/lib/libopencv_core.a /usr/local/lib/libjasper.a /usr/local/lib/libtiff.a /usr/local/lib/libpng15.a /usr/local/lib/libjpeg.a /usr/local/lib/libz.a -lgthread-2.0 -lglib-2.0 -lgobject-2.0 -lfontconfig -lz -lfreetype -lpango-1.0 -lX11 -lcairo -lXfixes -lgio-2.0 -lgdk_pixbuf-2.0 -lXdamage -lXcomposite -lXrandr -lXinerama -lXrender -lXext -lpangocairo-1.0 -lpangoft2-1.0 -latk-1.0 -lgdk-x11-2.0 -lgtk-x11-2.0 -lrt -lpthread -lm -ldl -lstdc++
CVLIBS=`pkg-config --libs opencv-static`
CVFLAGS=`pkg-config --cflags opencv`
GTKFLAGS=`pkg-config --cflags gtk+-2.0`
GTK_LIBS=`pkg-config --libs gtk+-2.0`
OPTS=-g -Wall -O2 #-static #-march=i386 

graph:graph.o map.o 
	$(CC) $(OPTS) $^ -o $@ $(CVLIBS) 

menu:menu.o graph.o map.o
	$(CC) $(OPTS) $^ -o $@ $(CVLIBS) $(GTK_LIBS) #-static
test:test.o
	$(CC) $(OPTS) $^ -o $@ $(GTK_LIBS)



test.o:test.c
	$(CC) $(OPTS) -c $^ $(GTKFLAGS)
graph.o:graph.c
	$(CC) $(OPTS) -c graph.c $(CVFLAGS)
map.o:map.c
	$(CC) $(OPTS) -c map.c $(CVFLAGS)
menu.o:menu.c
	$(CC) $(OPTS) -c $^ $(GTKFLAGS) 

.PHONY:clean

clean:
	-rm *.o graph

