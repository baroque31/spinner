#include "geometry2D.h"
#include <math.h>


Path  four_points_centered(double dx, double dy)
{
   Path V;
   V.push_back (point2D(-dx/2, -dy/2));
   V.push_back (point2D(-dx/2,  dy/2));
   V.push_back (point2D( dx/2, -dy/2));
   V.push_back (point2D( dx/2,  dy/2));
   return V;
}

point2D circle_point ( double r, double a )
{
	 double angle_radians = Units::deg2rad(a);
     point2D P(cos(angle_radians) * r, sin(angle_radians) * r );
	 return P;
}

Path arc ( double a0, double a1, double r, double delta)
{
    Path out;
	bool sign = (a1 > a0);

	if (sign) {
	   for (double a=a0; a<=a1; a+=delta)
            out.push_back(circle_point(r, a));
	}
	if (!sign) {
	   for (double a=a0; a>=a1; a-=delta)
            out.push_back(circle_point(r, a));
	}
    return out;
}

Path arcat ( double x, double y,  double a0, double a1, double r, double delta)
{
    Path curve = arc (a0, a1, r, delta);
	curve.translate(x,y);
	return curve;
}

point2D add_2_points (point2D p0, point2D p1)
{
   return point2D(p0.x+p1.x, p0.y+p1.y);
}

double delta_a_2_delta_A ( double da, double R, double r )
{
   return -da * (r/R);
}

double total_length (Path p)
{
   double total=0;
   for (int i=1; i<p.getData().size(); i++) {
       total += p.getData()[i-1].hypot(p.getData()[i]);
   }
   return total;
}

Path
loops_on_a_line_p ( double Hypot,
                  point2D p0, point2D p1, 
                  double start_len, double rad, double spin, 
				  double delta_h) 
{
     Path path;
     double pos = start_len;
     for (double h = 0; h < Hypot; h += delta_h) 
	     path.push_back(circle_point ( rad, (pos+h) * spin ).translate
		     ( p0.x + h/Hypot * (p1.x-p0.x), p0.y + h/Hypot * (p1.y - p0.y) ) );

	 return path;
}

Path 
loops_on_a_path ( Path &pointList, double rad, double spin, double resolution )
{
   double pos=0; // distance along the path
   double distance = total_length(pointList);  // total length of path we are following
   Path outpath;
   for ( int i = 1; i < pointList.getData().size(); i++ )  {
        double Hypot = pointList.getData()[i-1].hypot(pointList.getData()[i]);
        Path P = loops_on_a_line_p( Hypot, pointList.getData()[i-1], pointList.getData()[i], 
			                        pos, rad, spin, resolution);
		//cerr << " in loops P[0] = ";  P[0].print();
        outpath.concat( P );
	    pos += Hypot;
   }
   return outpath;
}

point2D spiropoint (double R, double A, double r, double a, double rp)
{
    return add_2_points ( circle_point(R-r, A), circle_point(rp, a));
}

Path spirograph ( double R, double r, double rp, double start_angle, int cycles=1)
{
    Path  path;
	for (double angle = start_angle; angle <= start_angle + (360 * cycles * (R/r)); angle += 5) {
	     path.push_back(spiropoint (R, delta_a_2_delta_A(angle, R, r), r, angle, rp));
	}
    return (path);
}

