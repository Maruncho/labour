#include "Graphic/GUI.h"
#include <stdexcept>

using namespace Graph_lib;

struct My_window : Window {
	My_window(Point p, int w, int h, const string& title);
	void wait_for_button();
private:
	Button quit_button;
	void quit() { hide(); }
	
	
	Button next_button;
	void next() { button_pushed = true; }
	bool button_pushed;
};

My_window::My_window(Point p, int w, int h, const string& title)
	:Window{ p,w,h,title },
	next_button{Point {x_max()-70,0},70,20,"Next",
[](Address, Address pw) { reference_to<My_window>(pw).next(); } },
	quit_button{Point{x_max()-150,0},70,20,"Quit",
[](Address, Address pw) { reference_to<My_window>(pw).quit(); } }
{
	button_pushed = false;
	attach(next_button);
	attach(quit_button);
	
}

 void My_window::wait_for_button() 
 {

	 while (!button_pushed)
		 Fl::wait();
	 button_pushed = false;
	 Fl::redraw();
}

 //--------------------------------------------



int main() {
	try {
		My_window win{ Point{100,100},600,400,"my_window" };
		Graph_lib::gui_main(); //keep open
	}
	catch (exception & e) {
		cerr << "Exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception!?" << '\n';
		return 2;
	}
}