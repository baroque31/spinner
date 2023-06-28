#ifndef POINT2D_INCLUDE
#define POINT2D_INCLUDE

#include <iostream>
#include <math.h>

using namespace std;

class point2D;

class point2D {
  public:
    double x, y; 
    
    point2D():x(0),y(0){};

    //point2D(point2D& p) { x = p.X(); y = p.Y(); }

    point2D(double a, double b):x(a),y(b){};

    point2D scale(double xScale, double yScale) {
	     x*=xScale, y*=yScale;
		 return *this;
    }

    point2D translate(double dx, double dy) {
	     x+=dx, y+=dy;
		 return *this;
    }

    double hypot(const point2D &p1) { 
		 double a, b;
		 a = fabs(x - p1.x);
		 b = fabs(y - p1.y); 
		 return sqrt(a*a + b*b); 
    }
	     
    friend ostream &operator<<(ostream &os, const point2D &P) {
	    os << "[ " << P.x << ", " << P.y << " ]" << endl;
		return os;
	}
};


#endif
