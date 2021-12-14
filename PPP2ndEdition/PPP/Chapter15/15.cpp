#include "15.h"
#include <iostream>

using namespace Graph_lib;
using namespace exercise;


Fuct::Fuct(Fct f, double r1, double r2, Point xy,
	int count, double xscale, double yscale) : function{ f }, r_min{ r1 }, r_max{ r2 }, count{ count }, xscale{ xscale }, yscale{ yscale }
	// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
	// x coordinates are scaled by xscale and y coordinates scaled by yscale
{
	if (r2 - r1 <= 0) error("bad graphing range");
	if (count <= 0) error("non-positive graphing count");
	double dist = (r2 - r1) / count;
	double r = r1;
	for (int i = 0; i < count; ++i) {
		Shape::add(Point{ xy.x + int(r * xscale),xy.y - int(f(r) * yscale) });
		r += dist;
	}
}

Fuct::Fuct(double (*f)(double), double r1, double r2, Point xy,
	int count, double xscale, double yscale) :
	Fuct{ static_cast<Fct>(f),r1,r2,xy,count,xscale,yscale }
{
}
