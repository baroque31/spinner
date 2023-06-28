#ifndef GEOMETRY_INCLUDE
#define GEOMETRY_INCLUDE

#include "geometry2D.h"
#include "geometry3D.h"

// 2D <--> 3D conversions
NonPlanarPath Path2NonPlanar ( Path &P, double z=0 );
Path NonPlanar2Path ( const NonPlanarPath &P );

#endif
