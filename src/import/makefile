# PROFILE = -pg
CPPFLAGS = -g $(PROFILE) -I. -I../config -I../geometry -I..
LIB_DIRS = -L. -L../geometry
LIBS = -ljsoncpp -lgeometry


import.o:	import.h import.cpp
	g++ $(CPPFLAGS) -c -o import.o import.cpp

clean:
	rm -f *.o
