#include "Graphic/Graph.h"
using namespace Graph_lib;
namespace exercise {

	struct Arc : Shape {
		Arc(Point p, int ww, int hh);
		Arc(Point p, int ww, int hh, int start, int end);
		Arc(Point p, int r);
		Arc(Point p, int r, int start, int end);

		Point center() const;
		int height() const { return h; };
		int width() const { return w; };

		void draw_lines() const;

	private:
		int h;
		int w;
		int s = 0;
		int e = 180;
	};


	struct Box : Shape {
		Box(Point p, int a, int b);
		Box(Point p, int a, int b, int r);

		void draw_lines() const;

	private:
		Lines sides;
		Vector_ref<Arc> corners;
		int r = 10;
	};

}