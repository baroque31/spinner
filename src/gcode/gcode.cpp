#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>

#include "geometry.h"
#include "readConfig.h"
#include "gcode.h"

using namespace std;


void Gcode::gotoXY(const point2D &p) 
{ 
	 retract();
	 out3param( "G0", 'X', p.x, 'Y', p.y, 'F', CV.travelSpeed() );
	 unretract();
} 

double Gcode::getExtrusionRatio()
{
    /****
	* What is this Extrusion Ratio?
	*
	* When we issue this gcode command:  G1 Xx Yy E1.0
	* We instruct the printer to move the printhead to position (x,y) and tell the extruder to advance by 1mm.
	* How much filament volume this is depends on the filament diameter.
	* But we prefer to think about extrusion amount as the length of material we need at the nozzle diameter.
	* This extrusion Ratio is the ratio betweeen 
	* the area of the cross section of the fialment and 
	* the area of the circle described by the nozzle size.
	*
	* remember the area of a circle is (PI * r^2)
	****/

	double filament_area = M_PI * pow(CV.filamentDiameter()/2, 2);
	double nozzle_area =   M_PI * pow(CV.nozzleSize()/2, 2);
	return (nozzle_area / filament_area);

	/****
	* Now, if we want to extrude 1mm of material at the nozzle diameter,
	* we can compute as: G1 Xx Yy E(1.0*getExtrusionFactor())
	****/

}

void Gcode::setPrintSpeed() 
{ 
	out1param("G1", 'F', CV.printSpeed());
}

void Gcode::setTravelSpeed() 
{ 
	out1param("G0", 'F', CV.travelSpeed());
}

void Gcode::printToXY(double eCoefficient, 
	                        point2D p0, point2D p1) 
{ 
    double line_length = p0.hypot(p1);	
	out3param ( "G1", 'X', p1.x, 'Y', p1.y, 'E', line_length * eCoefficient );
}
	                                                
void Gcode::gotoZ(double Z) 
{ 
    out1param ("G0", 'Z', Z); 
}

void static send2stdout(string filename)
{
    FILE *input = fopen ( filename.c_str(), "r" );
	if (input)
	{
	     int c;

		 while ((c=getc(input))!=EOF)
		 	putchar(c);
	}
	fclose(input);
}


void Gcode::startPrint() 
{
	send2stdout(gcode_start);
}

void Gcode::endPrint() 
{
	retract();
	send2stdout(gcode_end);
	turnBedOff();
	turnNozzleOff();
}

	             
								 /*****
                                 cout << "G91" << endl;
                                 cout << "G1 Z+30" << endl;
                                 cout << "G90" << endl;
                                 cout << "G28 X0  ; home X axis" << endl;
                                 cout << "G28 Y0  ; home Y axis" << endl;
                                 cout << "M104 S0 T0 ; turn off extruder" << endl;
                                 cout << "M140 S-273.15" << endl;
                                 cout << "M107; Turn off fan" << endl;
                                 cout << "M84 ; disable motors" << endl;
                                 cout << "G28 X0  ; home X axis" << endl;
                                 cout << "G28 Y0  ; home Y axis" << endl;
                                 cout << "M84 ; disable motors" << endl;
								 *****/

/* fan control, turns the fan on if current z is >fanStart */
void Gcode::setFan(double z) 
{
	static double lastFan = 0;

	double fanspeed = CV.getFanSpeedAtZ(z);
	if (lastFan != fanspeed) {
		out1param("M106", 'S', round(fanspeed));
		lastFan = fanspeed;
	}
}

void Gcode::setPrint(double z) 
{
	static double lastPrint = 0;

	double printspeed = CV.getPrintSpeedAtZ(z);
	if (lastPrint != printspeed) {
		out1param("G1", 'F', round(printspeed));
		lastPrint = printspeed;
	}
}

void Gcode::retract() 
{
	out2param ( "G1", 'E', -CV.retractLength(), 'F', CV.retractSpeed(), true );
}

void Gcode::unretract() 
{
    out2param ("G1", 'E',  CV.retractLength(), 'F',  CV.printSpeed()); 
}

void Gcode::setBedTemp() 
{
   out1param ( "M190", 'S',  CV.bedTemp() );
}

void Gcode::turnBedOff() 
{
   out1param ( "M140", 'S', -273.15 );
}

void Gcode::setNozzleTemp() 
{
	out1param ("M109", 'S',  CV.eTemp() );
}

void Gcode::turnNozzleOff() 
{
	out1param ("M109", 'S',  0 );
}

void Gcode::beginPrint() 
{
	setBedTemp();
	startPrint();
	setNozzleTemp();
}

void Gcode::out0param(string gcode, bool last) 
{
	cout << gcode;
	if (last) cout << endl;
}

void Gcode::out1param(string gcode, char param, double value, 
                                    bool last) 
{
	out0param (gcode, false);
	cout << " " << param << value ;
	if (last) cout << endl;
}

void Gcode::out2param(string gcode, char param1, double value1, 
                                    char param2, double value2, 
									bool last) 
{
	out1param (gcode, param1, value1, false);
	cout << " " << param2 << value2 ;
	if (last) cout << endl;
}

void Gcode::out3param(string gcode, char param1, double value1, 
		                            char param2, double value2,
		                            char param3, double value3,
									bool last) 
{
	out2param (gcode, param1, value1, param2, value2, false);
	cout << " " << param3 << value3 ;
	if (last) cout << endl;
}

void Gcode::out4param(string gcode, char param1, double value1, 
		                            char param2, double value2,
		                            char param3, double value3,
		                            char param4, double value4,
									bool last) 
{
	out3param (gcode, param1, value1, param2, value2, param3, value3, false);
	cout << " " << param4 << value4 ;
	if (last) cout << endl;
}

void Gcode::paint3DPath(NonPlanarPath nonPlanarSection) 
{
	double extrusionRatio  = getExtrusionRatio();
	double extrusionFactor = CV.extrusionFactor();

	long nPoints = nonPlanarSection.size();
	/// move to start
	out4param("G0", 'X', nonPlanarSection[0].x,
				 'Y', nonPlanarSection[0].y,
				 'Z', nonPlanarSection[0].z,
				 'F', CV.travelSpeed());
	setPrintSpeed();
	unretract();
	for (long l=0; l<nPoints-1; l++) {
	 double strokeLen = nonPlanarSection[l].hypot(nonPlanarSection[l+1]);
	 out4param ( "G1", 'X', nonPlanarSection[l+1].x,
					   'Y', nonPlanarSection[l+1].y,
					   'Z', nonPlanarSection[l+1].z,
					   'E', strokeLen * extrusionRatio * extrusionFactor * nonPlanarSection[l+1].Efactor); 
	 setFan(nonPlanarSection[l+1].z);
	 setPrint(nonPlanarSection[l+1].z);
	}
	retract();
};

