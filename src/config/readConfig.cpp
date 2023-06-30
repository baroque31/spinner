#include "readConfig.h"
#include "geometry3D.h"

using namespace std;

Config::Config(std::string filename)
{
  std::ifstream ifs;
  ifs.open(filename);

  if (ifs.good())
  {
	  Json::CharReaderBuilder builder;
	  builder["collectComments"] = true;
	  JSONCPP_STRING errs;
	  if (!parseFromStream(builder, ifs, &C, &errs)) {
		std::cout << errs << std::endl;
	  }
  }

  fanSpeeds();
  printSpeeds();
  fanStarts();

}

vector<double> Config::getlist(string name)
{
     Json::Value listval = C[name];
	 vector<double> D;

	 // cerr << "gathering list: " << endl;
	 for (int i=0; i<listval.size(); i++) {
	     D.push_back(listval[i].asDouble());
		 // cerr << listval[i].asDouble() << " ";
	 }

	 return D;
}

vector<double>
Config::fanStarts()
{
	fanstarts = getlist("fanStarts");
	if (validate_starts())
	    return fanstarts;
    exit(1);
}

vector<double>
Config::fanSpeeds()
{
	return fanspeeds = getlist("fanSpeeds");
}

vector<double>
Config::printSpeeds()
{
	return printspeeds = getlist("printSpeeds");
}

bool Config::validate_starts()
{
   double lastZ = -1;
   for (auto &a : fanstarts)
       if (lastZ >= a) {
		  cerr << "fan starts are not increasing" << endl;
	      return false;
       }

   if ( fanstarts.size() != fanspeeds.size()  ||
        fanstarts.size() != printspeeds.size() ) {
		cerr << "fanstarts, fanspeeds, and printspeeds entries must have the same number of elements" << endl;
		return false;
   }
   return true;
}


double Config::getPrintSpeedAtZ(double Z)
{
	   double value = 0;
	   int i=0;
       for (i=0; i<fanstarts.size(); i++) {
	       if (Z > fanstarts[i])
		      value = printspeeds[i];
	   }
	   return value;
}

double Config::getFanSpeedAtZ(double Z)
{
	   double value = 0;
	   int i=0;
       for (i=0; i<fanstarts.size(); i++) {
	       if (Z > fanstarts[i])
		      value = fanspeeds[i];
	   }
	   return value;
}


