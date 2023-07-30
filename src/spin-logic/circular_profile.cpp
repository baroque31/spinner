#include "circular_profile.h"

extern int spinner_debug;
using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))
double dhFind( Path& profile, double z, double dh, double threshold, double tolerance=0.005);

float radius_at ( float z, Path profile)
{
   // this is a linear search...
   Path::PlanarSequence S = profile.getData();

   int i, len = S.size();

   for (i=0; i<len && S[i].y < z; i++)
          ;

   // if the requested z is beyond the last sample point, 
   // return the last sample point.
   if (i==len) 
   {
      return (S[i-1].x);
   }

   point2D lowside  = S[i-1];
   point2D highside = S[i];

   if (highside.x == lowside.x)
       return (highside.x);

   return ( lowside.x 
            + ( highside.x - lowside.x) * ( ( z - lowside.y ) / ( highside.y - lowside.y ) ) );
}

Path fill_circle ( double radius, double nozzle_dia )
{
      Path pattern;
      double X, Y;
      int sign = 1;
      double angle;
      
      for (X=-(radius-nozzle_dia); X < radius-nozzle_dia; X+=nozzle_dia ) {
           angle = acos (X/radius);
		   Y = sin(angle) * radius * sign;
		   pattern.push_back ( point2D(X, Y) );
		   pattern.push_back ( point2D(X, -Y));
		   sign *= -1;
      }
      return pattern;
}


double dhFind( Path& profile, double z, double dh, double threshold, double tolerance)
{
     double radatZ = radius_at(z, profile);
	 double radatZdh = radius_at(z+dh, profile);
     double deltaRad = (radatZdh - radatZ);

	 double last_dh = dh/2;
     while ( fabs(deltaRad) > threshold && fabs(last_dh - dh) > 0.001) 
	 {
		last_dh = dh;
		dh = fabs(threshold * dh / deltaRad);
	 	radatZdh = radius_at(z+dh, profile);
     	deltaRad = (radatZdh - radatZ);

	    if ( spinner_debug) cerr << "threshold: " << threshold << " dh: " << dh << " radatZ/radatZhd: " << radatZ << '/' << radatZdh << endl;
	} 

    return MAX(0.005, dh);
}

NonPlanarPath
spiral_profile (Path profile, Config CV, int stage)
{
   NonPlanarPath shape;
   double nozzlesize = CV.nozzleSize();
   double z = CV.layerHeight();  // first layer here
   double tlh = CV.layerHeight(); // target layer height
   double threshold = CV.overhang();
   double sides = CV.sides();
   double z_start = z;
   double dr;
   int layer_count = 0;

   /*** 
   * stage decoding:
   * stage = 0: output priming path
   * stage = 1; output object build path
   *****/

   z=z_start+tlh;
   double z_end = profile.getData()[profile.getData().size()-1].y;

   // what is the diameter of this model at the bottom?
   double rPrime = radius_at(0, profile);
   // prime 3 rotations of filament...
   if ( stage == 0 )
   {
       for (auto &p2d : arc(0, 360, rPrime+10+2*nozzlesize, 360.0/sides).getData())  shape.push_back ( point3D(p2d.x, p2d.y, z-z_start) ); 
       for (auto &p2d : arc(0, 360, rPrime+10+1*nozzlesize, 360.0/sides).getData())  shape.push_back ( point3D(p2d.x, p2d.y, z-z_start) ); 
       for (auto &p2d : arc(0, 360, rPrime+10+0*nozzlesize, 360.0/sides).getData())  shape.push_back ( point3D(p2d.x, p2d.y, z-z_start) ); 
       return shape;
   }

   //start with a flat circle.
   for (auto &p2d : arc(0, 360, rPrime, 360.0/sides).getData())  shape.push_back ( point3D(p2d.x, p2d.y, z-z_start, 1.2) ); 
   for (auto &p2d : arc(0, 360, rPrime-CV.nozzleSize(), 360.0/sides).getData())  shape.push_back ( point3D(p2d.x, p2d.y, z-z_start, 1.2) ); 
   // now begin the spiral stage...
   double extrusion_factor;
   double previous_dh = tlh;
   while (z < z_end-0.1 ) {
         double dh=tlh;

		 dh = dhFind ( profile, z, dh, threshold);
		 if (spinner_debug) cerr << "z=" << z << "  dh=" << dh << "; threshold = " 
		      << threshold << endl;
		 extrusion_factor = MAX(0.1, dh) / tlh;

		 if ( 0 == layer_count ) {
		     extrusion_factor *= 1.5;  // 50% over extrusion on the first layer
		 }

		 for (double angle=0; angle<=360.0; angle+=(360.0/sides)) {
		     dr = radius_at(z+(dh*angle/360.0), profile);
			 point2D p2d = circle_point(dr, angle);
			 point3D p3d(p2d.x, p2d.y, z+(dh*angle/360.0)-z_start, extrusion_factor);
			 shape.push_back(p3d);
		 }
		 z += dh;
		 previous_dh = dh;
		 layer_count++;
  }
  for (auto &p2d : arc(0, 360, dr, 360.0/sides).getData())     shape.push_back ( point3D(p2d.x, p2d.y, z-z_start) ); 
  for (auto &p2d : arc(0, 360, dr-threshold/2, 360.0/sides).getData()) shape.push_back ( point3D(p2d.x, p2d.y, z-z_start) ); 
//  shape.push_back( point3D ( 100, 100, z-z_start ));
  /*
  Path filltop = fill_circle(dr, 0.3);
  NonPlanarPath finish_circle = Path2NonPlanar ( filltop, z-z_start );
  shape.insert ( shape.end(), finish_circle.begin(), finish_circle.end() );
  */
  return shape;
}

