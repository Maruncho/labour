#include "Graphic/Simple_window.h"
#include "Graphic/Graph.h"
#include "Graphic/Window.h"
#include "15.h"


using namespace Graph_lib;

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return pow(x, 2); }
double misc1(double x) { return sin(x) + cos(x); }
double misc2(double x) { return sin(x)*sin(x) + cos(x)*cos(x); }

int main()
{
	constexpr int max = 600;
	constexpr int offset = 100;
	constexpr int length = 400;
	constexpr Point center = { max / 2,max / 2 };
	constexpr int scale = 20;  //notch size
	constexpr int n_notches = length / scale;
	constexpr int n_min = -10;
	constexpr int n_max = 12;
	constexpr int n_points = 400;

	Graph_lib::Window win{ Point{100, 100},600,600,"Functions graphs." };

	Axis x{ Axis::x,Point{center.x - length / 2, center.y },length,n_notches,"1==20 pixels" };
	Axis y{ Axis::y,Point{center.x, center.y + length / 2 }, length, n_notches, "1==20 pixels" };

	x.Shape::set_color(Color::red);
	y.Shape::set_color(Color::red);
	x.notches.set_color(Color::dark_red);
	y.notches.set_color(Color::dark_red);
	x.label.set_color(Color::black);
	y.label.set_color(Color::black);

	x.label.move(-150, 0);

	win.attach(x);
	win.attach(y);

	//----------------------------

	//dark blue sine function
	exercise::Fuct f1{ sin, n_min, n_max, center, n_points, scale, scale };
	win.attach(f1);
	f1.set_color(Color::dark_blue);

	//dark yellow cosine function
	exercise::Fuct f2{ cos, n_min, n_max, center, n_points, scale, scale };
	win.attach(f2);
	f2.set_color(Color::dark_yellow);

	//magenta sine + cosine function
	exercise::Fuct f3{ misc1, n_min, n_max, center, n_points, scale, scale };
	win.attach(f3);
	f3.set_color(Color::magenta);

	//dark magenta sine^2 + cosine^2 function
	exercise::Fuct f4{ misc2, n_min, n_max, center, n_points, scale, scale };
	win.attach(f4);
	f4.set_color(Color::dark_magenta);
	
	//keep running
	Graph_lib::gui_main();
}