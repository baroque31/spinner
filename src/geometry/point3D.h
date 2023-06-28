#ifndef POINT3D_INCLUDE
#define POINT3D_INCLUDE


#include "point2D.h"

using namespace std;


class point3D : public point2D {
  public:
  	double z;
	double Efactor;
    point3D() :z(0), Efactor(1.0) 
	{
		::point2D();
	}
	
    point3D(double a, double b, double c)
	         :z(c), Efactor(1.0)
	{
        x=a, y=b;
	}

    point3D(double a, double b, double c, double e)
	         :z(c), Efactor(e)
	{
        x=a, y=b;
	}


	point3D &scale(double xfact, double yfact, double zfact) {
	     x*=xfact, y*=yfact; z*=zfact;
		 return *this;
    }

	point3D &translate(double dx, double dy, double dz) {
	     x+=dx, y+=dy; z+=dz;
		 return *this;
    }
    double hypot(const point3D &p1) { 
		 double a, b;
		 point2D P2d0(x, y), P2d1(p1.x, p1.y);
		 a = P2d0.hypot(P2d1);
		 b = fabs(z - p1.z); 
		 return sqrt(a*a + b*b); 
    }

    friend ostream &operator<<(ostream &os, const point3D &P) {
	    os << "[ " << P.x << ", " << P.y << ", " << P.z << " ]" << endl;
		return os;
	}
};


#endif
