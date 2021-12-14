
#include "Graphic/GUI.h"

using namespace Graph_lib;

struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);
private:
	Open_polyline lines;
	Menu color_menu;
	Button color_menu_button;
	Menu style_menu;
	Button style_menu_button;
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	static void cb_red(Address, Address pw) { reference_to<Lines_window>(pw).red_pressed(); }
	static void cb_blue(Address, Address pw) { reference_to<Lines_window>(pw).blue_pressed(); }
	static void cb_black(Address, Address pw) { reference_to<Lines_window>(pw).black_pressed(); }

	void red_pressed() { change_color(Color::red); color_hide_menu(); }
	void blue_pressed() { change_color(Color::blue); color_hide_menu(); }
	void black_pressed() { change_color(Color::black); color_hide_menu(); }

	static void cb_solid(Address, Address pw) { reference_to<Lines_window>(pw).solid_pressed(); }
	static void cb_dash(Address, Address pw) { reference_to<Lines_window>(pw).dash_pressed(); }
	static void cb_dot(Address, Address pw) { reference_to<Lines_window>(pw).dot_pressed(); }

	void solid_pressed() { change_style(Line_style::solid); style_hide_menu(); }
	void dash_pressed() { change_style(Line_style::dash); style_hide_menu(); }
	void dot_pressed() { change_style(Line_style::dot); style_hide_menu(); }

	void change_color(Color c) { lines.set_color(c); redraw(); }
	void change_style(Line_style l) { lines.set_style(l); redraw(); }
	void color_hide_menu() { color_menu.hide(); color_menu_button.show(); style_menu_button.show(); }
	void color_menu_pressed() { color_menu_button.hide(); style_menu.hide(); style_menu_button.show(); color_menu.show(); }
	void style_hide_menu() { style_menu.hide(); style_menu_button.show(); }
	void style_menu_pressed() { style_menu_button.hide(); style_menu.show(); color_menu.hide(); color_menu_button.show(); }

	void next();
	void quit();
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	next_button{ Point{x_max() - 150,0},70,20,"Next point",
		[](Address, Address pw) { reference_to<Lines_window>(pw).next(); } },
	quit_button{ Point{x_max() - 70,0},70,20,"Quit",
		[](Address, Address pw) { reference_to<Lines_window>(pw).quit(); } },
	next_x{ Point{x_max() - 310,0},50,20,"next x:" },
	next_y{ Point{x_max() - 210,0},50,20,"next y:" },
	xy_out{ Point{100,0}, 100, 20, "current (x,y):" },
	style_menu{ Point{x_max() - 70,60},70,20,Menu::vertical,"style" },
	style_menu_button{ Point{x_max() - 80,60}, 80,20,"style menu",
		[](Address,Address pw) { reference_to<Lines_window>(pw).style_menu_pressed(); } },
	color_menu{ Point{x_max() - 70,40},70,20,Menu::vertical,"color" },
	color_menu_button{ Point{x_max() - 80,30}, 80,20,"color menu",
		[](Address,Address pw) { reference_to<Lines_window>(pw).color_menu_pressed(); } }
{	
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");
	style_menu.attach(new Button{ Point{ 0,0 },0,0,"solid",cb_solid });
	style_menu.attach(new Button{ Point{ 0,0 },0,0,"dash",cb_dash });
	style_menu.attach(new Button{ Point{ 0,0 },0,0,"dot",cb_dot });
	attach(style_menu);
	style_menu.hide();
	attach(style_menu_button);
	color_menu.attach(new Button{ Point{ 0,0 },0,0,"red",cb_red });
	color_menu.attach(new Button{ Point{ 0,0 },0,0,"blue",cb_blue });
	color_menu.attach(new Button{ Point{ 0,0 },0,0,"black",cb_black });
	attach(color_menu);
	color_menu.hide();
	attach(color_menu_button);
	attach(lines);
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();

	lines.add(Point{ x,y });

	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

void Lines_window::quit()
{
	hide();
}

int main() {
	try {
		Lines_window win{ Point{100,100},600,400,"lines" };
		return gui_main();
	}
	catch (exception & e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
}