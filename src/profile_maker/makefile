# PROFILE = -pg
CPPFLAGS = -g $(PROFILE) -I. -I../config -I../import -I../geometry -I.. -I../spin-logic -I../gcode
LIB_DIRS = -L. -L../geometry
LIBS = -ljsoncpp -lgeometry


profile_maker:	profile_maker.o
	g++ -o profile_maker profile_maker.o $(LIB_DIRS) $(LIBS)

profile_maker.o:	profile_maker.cpp
	g++ $(CPPFLAGS) -c -o profile_maker.o profile_maker.cpp

clean:
	rm -f *.o profile_maker
