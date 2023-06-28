# PROFILE = -pg
CPPFLAGS = -g $(PROFILE) -std=c++20 -I. -I../config -I../geometry -I../import -I../spin-logic -I../gcode

readConfig.o:	readConfig.cpp readConfig.h
	g++ $(CPPFLAGS) -c -o readConfig.o readConfig.cpp

clean:
	rm -f *.o
