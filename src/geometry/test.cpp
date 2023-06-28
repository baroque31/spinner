#include "geometry.h"

int main(int argc, char *argv[])
{
    Path P = arc ( 0, 25, 30 );
	NonPlanarPath NP = Path2NonPlanar (P, 0);
	Path Q = NonPlanar2Path(NP);
	cout << Q;
	cout << P;
}

