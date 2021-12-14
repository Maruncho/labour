#include <iostream>
#include "Graphic/Graph.h"

using namespace Graph_lib;
namespace exercise {

	struct Fuct : Shape {
		Fuct(Fct f, double r1, double r2, Point orig,
			int count = 100, double xscale = 25, double yscale = 25);
		Fuct(double (*f)(double), double r1, double r2, Point xy, int count, double xscale, double yscale);

		void reset_range(double min, double max) { r_min = min; r_max = max; }
		void reset_count(int c) { count = c; }
		void reset_scale(double x, double y) { xscale = x; yscale = y; }

	private:
		Fct function;
		double r_min;
		double r_max;
		int count;
		double xscale;
		double yscale;
	};

}