#ifndef READCONFIG_INCLUDE
#define READCONFIG_INCLUDE

#include "json/json.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class Config
{
    private:
        Json::Value C;
		std::vector<double> getlist(std::string name);
		std::vector<double> fanstarts;
		std::vector<double> fanspeeds;
		std::vector<double> printspeeds;
		bool validate_starts();

    public:
		Config(std::string filename);

		double bedsizeX()        { return C.get("bedsizeX",          200).asDouble(); }
		double bedsizeY()        { return C.get("bedsizeY",          200).asDouble(); }
		double bedTemp()         { return C.get("bedTemp",            40).asDouble(); }
		double eTemp()           { return C.get("eTemp",             200).asDouble(); }
		double travelSpeed()     { return C.get("travelSpeed",      1000).asDouble(); }
		std::vector<double> printSpeeds();
		double printSpeed()      { return C.get("printSpeed",       1000).asDouble(); }
		double retractLength()   { return C.get("retractLength",       2).asDouble(); }
		double retractSpeed()    { return C.get("retractSpeed",     2000).asDouble(); }
		std::vector <double> fanStarts();
		std::vector <double> fanSpeeds();
		double getPrintSpeedAtZ(double Z);
		double getFanSpeedAtZ(double Z);
		double nozzleSize()      { return C.get("nozzleSize",       0.80).asDouble(); }
		double layerHeight()     { return C.get("layerHeight",       0.5).asDouble(); }
		double overhang()        { return C.get("overhang", nozzleSize()/2).asDouble(); }
		double filamentDiameter(){ return C.get("filamentDiameter", 1.75).asDouble(); }
		double extrusionFactor() { return C.get("extrusionFactor",  0.85).asDouble(); }
		double sides()           { return C.get("sides",             360).asDouble(); }
		int shells()             { return C.get("shells",             1).asInt(); }
};


#endif
