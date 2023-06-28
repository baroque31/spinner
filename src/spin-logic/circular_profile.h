
#ifndef CIRCULARPROFILE_INCLUDE
#define CIRCULARPROFILE_INCLUDE

#include "readConfig.h"
#include "geometry.h"

double dfFind( Path& profile, double z, double dh, double threshold, double tolerance=0.001);
NonPlanarPath
spiral_profile (Path profile, Config CV, int stage);

#endif
