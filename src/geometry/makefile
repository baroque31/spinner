CPPFLAGS=-std=c++20 -pg

libgeometry.a:	geometry.o geometry3D.o geometry2D.o Path.o
	ar rscv libgeometry.a geometry.o geometry3D.o geometry2D.o Path.o

geometry.o:	geometry.cpp geometry.h geometry2D.o geometry3D.o
	g++ $(CPPFLAGS) -g -c -o geometry.o geometry.cpp

geometry3D.o:	geometry3D.cpp geometry3D.h point3D.h geometry2D.o
	g++ $(CPPFLAGS) -g -c -o geometry3D.o geometry3D.cpp

geometry2D.o:	geometry2D.cpp geometry2D.h point2D.h units.h 
	g++ $(CPPFLAGS) -g -c -o geometry2D.o geometry2D.cpp

Path.o:	Path.cpp Path.h point2D.h 
	g++ $(CPPFLAGS) -g -c -o Path.o Path.cpp

clean:	
	rm -f *.o
