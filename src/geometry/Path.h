#include "point2D.h"
#include <vector>

class Path 
{
	public:
	    typedef vector<point2D> PlanarSequence;
    private:
	    PlanarSequence S;
	public:
	    Path() {};
	    Path(PlanarSequence P) : S(P) {};
        Path translate(double x, double y);
		Path scale(double x, double y);
		Path reverse();
		Path concat(Path &P); // add to end of current sequence
		Path push_back(point2D p); // add to end of current sequence
		PlanarSequence getData() { return S; };
		point2D first();
		point2D last();
		friend ostream& operator<<(ostream &os, Path& P)
		{
			 for (auto &a : P.S)   
		         os << a;
			 return os;
	    }
};

