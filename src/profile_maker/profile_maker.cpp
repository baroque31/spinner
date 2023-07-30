#include "geometry.h"


Path wine_glass()
{
	Path::PlanarSequence P  = { {25, 0}, {24, 5},   { 2, 6},   { 2, 25 }   };
	Path::PlanarSequence P1 = { {2, 45}, {2.5, 55}, { 40, 80}, { 25, 100 } };

	Path foot(P);
	Path cup(P1);

	NonPlanarPath Foot = Path2NonPlanar (foot, 0);
	NonPlanarPath Cup = Path2NonPlanar (cup, 0);

    Path base = NonPlanar2Path(bezier_curveV ( 0.01, Foot));
    Path head = NonPlanar2Path(bezier_curveV ( 0.01,  Cup));
	base.concat(head);
	return base;
}


Path doublewine()
{
    Path P = wine_glass();
    Path P2 = wine_glass().translate(0, 100);
	return  P.concat(P2);
}

Path doublewine2()
{
    Path P = wine_glass();
    Path P2 = wine_glass().reverse();
	Path P3 = P2.translate(0,100);
	return  P.concat(P3);
}

Path doublewine_2()
{
    Path P = wine_glass().reverse();
    Path P2 = wine_glass();
	Path P3 = P2.translate(0,100);
	return  P.concat(P3);
}

Path doublewine_3()
{
    Path P = wine_glass().reverse();
    Path P2 = wine_glass().reverse();
	Path P3 = P2.translate(0,100);
	return  P.concat(P3);
}

Path simple_flair()
{
	Path::PlanarSequence P  = { {25, 0}, {15, 20},   { 10, 50},   { 10, 100 }   };
	Path curve(P);
	NonPlanarPath Curve = Path2NonPlanar (curve, 0);
    return NonPlanar2Path(bezier_curveV ( 0.01, Curve));
}    

Path hall_sconce()
{
	double mount_dia = 40.15;
	double mount_tall = 18.5;
	double xoff = 5;

	Path::PlanarSequence P  = { { xoff + 106/2,         0 }, 
	                            { xoff +  5/2,         50 },   
								{ xoff + 170,         125 },   
								{ mount_dia/2, 115 }   
							  };
	Path curve(P);
	NonPlanarPath Curve = Path2NonPlanar (curve, 0);
    Path P1  = NonPlanar2Path(bezier_curveV ( 0.01, Curve));
	P1.push_back( point2D(mount_dia/2, 130) );
	return P1;
} 

Path hall_sconce2()
{
    double mount_dia = 40.15;
    double mount_tall = 18.5;
    double xoff = 5;

    Path::PlanarSequence P  = { 
                                { mount_dia/2,       25 },
	                            { xoff + 50,         40 },   
                                { xoff + 60,         145 }, 
                                { mount_dia/2,       200 }
                              };
    Path curve(P);
    NonPlanarPath Curve = Path2NonPlanar (curve, 0);
    Path P1;
    P1.push_back( point2D(mount_dia/2, 0) );
	Path P2 ( NonPlanar2Path(bezier_curveV ( 0.01, Curve)) );
	P1.concat ( P2 );
    return P1;
}


int main(int argc, char *argv[])
{
    Path P = hall_sconce2();
	//P.scale(2,2);
	cout << P;
}


