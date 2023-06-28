#ifndef UNITS_INCLUDE
#define UNITS_INCLUDE

class Units
{
	public:
    static double deg2rad(double deg)   { return ( (deg / 360.0) * (2 * M_PI) ); }
	static double rad2deg(double rad)   { return ( (rad / (2 * M_PI)) * 360.0);  }
	static double inch2mm(double inch)  { return ( inch * 25.4 );   }
	static double mm2inch(double mm)    { return ( mm / 25.4 );     }
};

#endif
