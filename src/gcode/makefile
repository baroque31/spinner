#PROFILE = -pg
CPPFLAGS = -g $(PROFILE) -std=c++20 -I. -I../config -I../geometry
LIB_DIRS = -L. -L../geometry
LIBS = -ljsoncpp -lgeometry


gcode.o:	gcode.cpp
	g++ $(CPPFLAGS) -c -o gcode.o gcode.cpp

clean:
	rm -f *.o
