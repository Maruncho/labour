#include "Graphic/Graph.h"
#include "Graphic/Simple_window.h"
#include "13.h"

using namespace exercise;
int main()
{
	Simple_window win{ Point{100,100},800,600,"Window" };

	//ellipse 200x100 drawn from 0 to 200 degrees
	exercise::Arc ex{ Point{400,300}, 200,100, 0, 200};

	win.attach(ex);
	ex.set_color(Color::black);
	win.wait_for_button();

	//box 400x200 with corners with radius 80
	exercise::Box box{ Point{100,200},400,200,80 };
	win.attach(box);
	box.set_color(Color::black);
	win.wait_for_button();
}