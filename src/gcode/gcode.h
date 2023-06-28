#ifndef MY_GCODE_INCLUDE
#define MY_GCODE_INCLUDE

#include <iostream>
#include <vector>
#include <math.h>

#include "geometry.h"

using namespace std;


class Gcode
{
   private:
       Config CV;
	   string gcode_start;
	   string gcode_end;
   public:
	   Gcode(Config cv) : CV(cv) {}
	   Gcode(Config cv, string beginfile, string endfile) : 
			  CV(cv), gcode_start(beginfile), gcode_end(endfile) {}

	   void gotoXY(const point2D &p);
	   void printToXY(double eCoefficient, point2D p0, point2D p1);
	   void setPrintSpeed();
	   void setTravelSpeed();
	   void gotoZ(double Z);
	   void setFan(double z);
	   void setPrint(double z);
	   void retract();
	   void unretract();
	   void setBedTemp();
	   void turnBedOff();
	   void setNozzleTemp();
	   void turnNozzleOff();
	   void startPrint();
	   void beginPrint();
	   void endPrint();
	   void paint3DPath(NonPlanarPath nonPlanarSection);
	   double getExtrusionRatio();
	   void out0param(string gcode, bool last=true);
	   void out1param(string gcode, char param, double value, bool last=true);
	   void out2param(string gcode, char param1, double value1, 
	                                char param2, double value2, bool last=true);
	   void out3param(string gcode, char param1, double value1, 
		                            char param2, double value2,
		                            char param3, double value3,
									bool last=true);
	   void out4param(string gcode, char param1, double value1, 
		                            char param2, double value2,
		                            char param3, double value3,
		                            char param4, double value4,
									bool last=true);
};

#endif
