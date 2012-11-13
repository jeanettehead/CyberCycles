g++ -o Tuto5.o -c -O3 -DNDEBUG -fPIC -I /research/bacoesen/osg4/OpenSceneGraph-3.0.1/include -I /research/bacoesen/osgi/include/ -L /research/bacoesen/osgi/lib64/ -L /research/bacoesen/osg4/OpenSceneGraph-3.0.1/lib Tuto5.cpp

g++ -oTuto5 Tuto5.o -I. -I/usr/include/ -I/usr/include/X11/ -I/usr/local/include/GL  -I/research/bacoesen/osg4/OpenSceneGraph-3.0.1/include -I/research/bacoesen/osgi/include -L. -L/usr/lib -L/usr/X11R6/lib -L/usr/local/lib -lm -ldl -lGL -lGLU -lpthread -lXext -lX11 -L/research/bacoesen/osg4/OpenSceneGraph-3.0.1/lib -losg -losgViewer -losgSim
