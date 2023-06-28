#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "import.h"


using namespace std;

bool Import::readpoint (FILE *F, point2D& out)
{
  int c;

  while ((c=fgetc(F))!='[' && c!= EOF) 
          ;
  int converted = fscanf(F, "%lF,%lF]", &(out.x), &(out.y));
  return (converted > 0);
}

bool Import::validate()
{
   // make sure each point has a higher Y than the previous
   double lastY = -1;
   for (auto &p : profile_sequence.getData() )
   {
   	   if (lastY > p.y) {
		  cerr << "validation failing, lastY is : " << lastY
		       << "this y: " << p.y << endl;
	      return false;
	   }
	   lastY = p.y;
   }
   return true;
}



bool Import::load()
{
	point2D P;
    if ( 0 != access ( import_file.c_str(), R_OK )) {
	   cerr << "ERROR: cannot access input file: " << import_file <<  " ( "
	        << strerror(errno) << endl;
	   return false;
    }

	FILE *import = fopen ( import_file.c_str(), "r" ); // we're pretty sure this will work;
	if (!import) { cerr << "unexpected file open failure" << endl; return false; }

	while (readpoint ( import, P ))
	     profile_sequence.push_back(P);

	fclose(import);
	if (!validate())
	{
		cerr << "dataset fails validation" << endl;
        return false;
	}
	return true;
}

