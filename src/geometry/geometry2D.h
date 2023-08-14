#ifndef GEOMETRY2D_INCLUDE
#define GEOMETRY2D_INCLUDE

#include <vector>
#include <math.h>
#include "point2D.h"
#include "units.h"
#include "Path.h"


// helper generators...
Path four_points_centered(double dx, double dy);

point2D circle_point (double radius, double angle);
Path arcat ( double x, double y,  double a0, double a1, double r, double delta=5);
Path arc ( double a0, double a1, double r, double delta=5);
Path spiral ( double inside_rad, double outside_rad, double rotations, double starting_angle=0, double delta=5);


Path
loops_on_a_line_p ( double hypot,  point2D start, point2D end, 
                  double start_len, double rad, double spin, 
				  double resolution=0.1 );
Path
loops_on_a_path ( const Path &pointList, double rad, double spin, double resolution );

Path 
spirograph ( double R, double r, double rp, double start, int cycles);

void translate(Path &P, double x, double y);


// formatted sequences...
void print_points(Path);


#endif
