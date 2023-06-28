#include "Path.h"
#include <ranges>

Path Path::translate(double x, double y)
{
	for (auto &p : S ) {
	    p.translate(x, y);
	}
	return *this;
}

Path Path::scale(double x, double y)
{
    for (auto &p : S )
	{
	     p.scale(x,y);
	}
	return *this;
}

Path Path::reverse()
{
	point2D firstPoint = first();
	point2D lastPoint = last();
	double height = lastPoint.y - firstPoint.y;
	Path result;

	for ( auto &a : S | std::views::reverse )
	{
	    a.y = height-a.y;
		result.push_back(a);
	}
	return result;
}

Path Path::concat(Path &P) // add to end of current sequence
{
	PlanarSequence PS = P.getData();
	S.insert(S.end(), PS.begin(), PS.end());
	return *this;
}

Path Path::push_back(point2D p)
{
    S.push_back(p);
	return *this;
}

point2D Path::first()
{
    return S[0];
}

point2D Path::last()
{
    return S[S.size()-1];
}


