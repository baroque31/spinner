#include "geometry.h"


// convert a 2D path to a 3D path, at constant Z
NonPlanarPath Path2NonPlanar ( Path &P, double z )
{
   NonPlanarPath V;

   for ( auto &a : P.getData() )
       V.push_back ( point3D(a.x, a.y, z) );

   return V;
}

// convert 3D path to 2D path, dropping Z
Path NonPlanar2Path ( const NonPlanarPath &P )
{
   Path V;

   for ( auto &a : P )
       V.push_back ( point2D(a.x, a.y) );

   return V;
}

