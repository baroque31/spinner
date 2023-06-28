#ifndef GEOMETRY3D_INCLUDE
#define GEOMETRY3D_INCLUDE

#include "point3D.h"
#include <vector>
typedef vector<point3D> NonPlanarPath;

// continuous curves....
NonPlanarPath bezier_curve(double t_step, point3D p0, point3D p2, point3D p3, point3D p4);
NonPlanarPath bezier_curveV(double t_step, const NonPlanarPath &V);

void translate(NonPlanarPath &npp, double x, double y, double z);

#endif
