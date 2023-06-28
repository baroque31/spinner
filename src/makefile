# PROFILE = -gp
CPPFLAGS = -std=c++20 $(PROFILE) -g -I. -Iconfig -Igeometry -Iimport -Ispin-logic -Igcode
LIB_DIRS = -L. -Lgeometry
LIBS = -ljsoncpp -lgeometry 
LDFLAGS = $(LIB_DIRS) $(LIBS)

OBJS = spinner.main.o \
       config/readConfig.o \
	   import/import.o \
	   spin-logic/circular_profile.o \
	   gcode/gcode.o

DIRS = config geometry import spin-logic gcode

spinner:  $(DIRS) spinner.main.cpp $(OBJS)
	g++ $(CPPFLAGS) $(LIB_DIRS) $(OBJS) $(LIBS) -o spinner

spinner.main.o:	spinner.main.cpp
	g++ $(CPPFLAGS) -c spinner.main.cpp

profile_maker:	profile_maker.cpp
	g++ $(CPPFLAGS) -c profile_maker.cpp
	g++ -o profile_maker profile_maker.o $(LDFLAGS)

config:	config/*.cpp config/*.h
	cd config; make

geometry: 
	cd geometry; make

gcode: 
	cd gcode; make

spin-logic: 
	cd spin-logic; make

import: 
	cd import; make


out2.gcode: spinner *.json
	./spinner -m > profile_test.data
	./spinner -c spinner.json -p profile_test.data > out2.gcode

clean:
	rm -f *.o
	cd import && make clean
	cd gcode && make clean
	cd geometry && make clean
	cd config && make clean
	cd spin-logic && make clean
