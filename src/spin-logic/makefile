# PROFILE = -pg
CPPFLAGS = -g $(PROFILE) -I. -I../config -I../geometry
LIB_DIRS = -L. -L../geometry
LIBS = -ljsoncpp -lgeometry



circular_profile.o:	circular_profile.cpp
	g++ $(CPPFLAGS) -c -o circular_profile.o circular_profile.cpp

clean:
	rm -f *.o
