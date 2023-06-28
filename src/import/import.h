#ifndef IMPORT_INCLUDE
#define IMPORT_INCLUDE

#include <string>
#include "geometry2D.h"

class Import
{
    private:
	  string import_file;
	  Path   profile_sequence;
	  bool   readpoint ( FILE *, point2D& );
	public:
	  Import(string profile) : import_file(profile) {};
	  bool validate(); //make sure Y's increase only
      bool load();  // load profile_sequence from the file
	  Path getVal() { return profile_sequence; }
	  void print()  { cerr << profile_sequence; }
};

#endif
