# PROFILE = -pg
CPPFLAGS = -g $(PROFILE) -I. -I../config -I../import -I../geometry -I.. -I../spin-logic -I../gcode
LIB_DIRS = -L. -L../geometry
LIBS = -ljsoncpp -lgeometry
OBJS = spinner.main.o \
       ../config/readConfig.o \
	   ../import/import.o \
	   ../spin-logic/circular_profile.o \
	   ../gcode/gcode.o


spinner:	$(OBJS)
	g++ -o spinner $(OBJS) $(LIB_DIRS) $(LIBS)

spinner.main.o:	spinner.main.cpp
	g++ $(CPPFLAGS) -c -o spinner.main.o spinner.main.cpp

clean:
	rm -f *.o spinner
