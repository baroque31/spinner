# PROFILE = -gp
CPPFLAGS = -std=c++20 $(PROFILE) -g -I. -Iconfig -Igeometry -Iimport -Ispin-logic -Igcode
LIB_DIRS = -L. -Lgeometry
LIBS = -ljsoncpp -lgeometry 
LDFLAGS = $(LIB_DIRS) $(LIBS)

#OBJS = spinner.main.o \
#       config/readConfig.o \
#	   import/import.o \
#	   spin-logic/circular_profile.o \
#	   gcode/gcode.o

DIRS = config.d geometry.d import.d spin-logic.d gcode.d

all:	spinner profile_maker
	
spinner:	$(DIRS)
	cd spinner; $(MAKE)

profile_maker:	$(DIRS)
	cd profile_maker; $(MAKE)

config.d:
	cd config; $(MAKE)

geometry.d: 
	cd geometry; $(MAKE)

gcode.d: 
	cd gcode; $(MAKE)

spin-logic.d: 
	cd spin-logic; $(MAKE)

import.d: 
	cd import; $(MAKE)

clean:
	cd import && $(MAKE) clean
	cd gcode && $(MAKE) clean
	cd geometry && $(MAKE) clean
	cd config && $(MAKE) clean
	cd spin-logic && $(MAKE) clean
