#include <unistd.h>
#include <stdlib.h>
#include <iomanip>

#include "readConfig.h"
#include "geometry.h"
#include "import.h"
#include "circular_profile.h"
#include "gcode.h"

int spinner_debug = 0; // tisk tisk, a global variable!
                       // set to 1 for progress messages.
using namespace std;


void usage()
{
   cerr << "usage: spinner [-c <config> ] "
           "[ -p <profile> ] [ -s <startgcode>] [-e endgcode]" 
		   " -m "
		   "\nwhere -m = make profile mode"
		   << endl;
   exit(1);
}

static bool checkAccess(string filename)
{
   if ( 0 != access(filename.c_str(), R_OK) ) {
       cerr << "file " << filename << " is not available" << endl;
	   return false;
   }
   return true;
} 

int main(int argc, char *argv[])
{
   
   string settings_filename("spinner_config.json"),
          gcode_start_filename("spinner_start.gcode"),
          gcode_end_filename("spinner_end.gcode"),
          profile_data_filename("spinner_profile.data");

   int opt;
   while ((opt = getopt(argc, argv, "dc:s:e:p:")) != -1) {
         switch(opt) 
		 {
		    case 'c':   settings_filename.assign(optarg); 
			            break;
			case 'd':   spinner_debug = 1;
			            break;
			case 's':   gcode_start_filename.assign(optarg); 
			            break;
			case 'e':   gcode_end_filename.assign(optarg); 
			            break;
			case 'p':   profile_data_filename.assign(optarg); 
			            break;
			default:    usage();
		 }
   }

   if ( ! (checkAccess ( settings_filename )     &&
           checkAccess ( profile_data_filename ) &&
		   checkAccess ( gcode_start_filename )  &&
		   checkAccess ( gcode_end_filename ) ) ) {
	   return 1;
   }

   //std::cout << std::fixed;
   std::cout << std::setprecision(8);

   Config CV(settings_filename);
   Import I(profile_data_filename);
   I.load();

   Gcode G(CV, gcode_start_filename, gcode_end_filename);

   G.beginPrint();

   NonPlanarPath prime = spiral_profile ( I.getVal(), CV, 0 );
//   translate(prime, CV.bedsizeX()/2, CV.bedsizeY()/2, 0);
   (void) G.paint3DPath ( prime );

   NonPlanarPath wee = spiral_profile ( I.getVal(), CV, 1 );
//   translate(wee, CV.bedsizeX()/2, CV.bedsizeY()/2, 0);
   (void) G.paint3DPath ( wee );

   G.endPrint();

   return 0;
}

