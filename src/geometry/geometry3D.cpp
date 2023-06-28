#include "geometry3D.h"

using namespace std;

NonPlanarPath concat ( NonPlanarPath a, NonPlanarPath b )
{
	NonPlanarPath ret;
	ret.insert(ret.end(), a.begin(), a.end());
	ret.insert(ret.end(), b.begin(), b.end());

	return ret;
}

double bezier_coordinate ( double t, double n0, double n1, double n2, double n3 )
{
    return (      n0 *     pow ( (1-t), 3 )
            + 3 * n1 * t * pow ( (1-t), 2 )
            + 2 * n2 *     pow ( (t),   2 ) * (1-t)
	        +     n3 *     pow ( t,     3 ) );
}

point3D bezier_point ( double t, point3D p0, point3D p1, point3D p2, point3D p3 )
{
    return point3D(bezier_coordinate(t, p0.x, p1.x, p2.x, p3.x),
                   bezier_coordinate(t, p0.y, p1.y, p2.y, p3.y),
	               bezier_coordinate(t, p0.z, p1.z, p2.z, p3.z));
}

NonPlanarPath bezier_curve ( double t_step, point3D p0, point3D p1, point3D p2, point3D p3 )
{
    NonPlanarPath P;
    double t;

    for ( t = 0; t < 1 + t_step; t+=t_step )
         P.push_back( bezier_point ( t, p0, p1, p2, p3 ) );

    return (P);
}

NonPlanarPath bezier_curveV ( double t_step, const NonPlanarPath &P )
{
   return bezier_curve ( t_step, P[0], P[1], P[2], P[3] );
}

void translate(NonPlanarPath &NPP, double x, double y, double z) 
{ 
	for (auto &a : NPP) 
		a.translate(x, y, z); 
};

void print_points ( NonPlanarPath P )
{
   for (auto p : P)
        cout << p;
}

