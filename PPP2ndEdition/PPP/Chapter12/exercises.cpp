#include "Graphic/Graph.h"
#include "Graphic/Simple_window.h"

int main() 
{
	std::cout << "exercise numbers are the title numbers";

	//exercise 1------------------------------------
	Point tl{ 100,100 };
	Simple_window win{ tl, 800,600, "Window1" };
	

	Graph_lib::Rectangle r{ Point{100,250},200,100 };
	r.set_color(Color::blue);
	win.attach(r);

	Graph_lib::Polygon p;
	p.add(Point{ 350,250 });
	p.add(Point{ 550,250 });
	p.add(Point{ 550,350 });
	p.add(Point{ 350,350 });
	p.set_color(Color::red);
	win.attach(p);

	win.wait_for_button();
	//exercise 2--------------------------------------
	win.detach(r);
	win.detach(p);

	Graph_lib::Rectangle rectangle{ Point{100,250},100,30 };
	Text text{ Point{130,270}, "Howdy!" };

	win.attach(rectangle);
	win.attach(text);

	win.set_label("Window2");
	win.wait_for_button();
	//exercise 3---------------------------------------
	win.detach(rectangle);
	win.detach(text);

	Line m1{ Point{50,500},Point{50,350} };
	Line m2{ Point{50,350},Point{125,500} };
	Line m3{ Point{125,500},Point{200,350} };
	Line m4{ Point{200,350},Point{200,500} };
	m1.set_style(Line_style{ Line_style::solid,4 });
	m2.set_style(Line_style{ Line_style::solid,4 });
	m3.set_style(Line_style{ Line_style::solid,4 });
	m4.set_style(Line_style{ Line_style::solid,4 });

	Line t1{ Point{250,350},Point{350,350} };
	Line t2{ Point{300,500},Point{300,350} };
	t1.set_style(Line_style{ Line_style::solid,4 });
	t2.set_style(Line_style{ Line_style::solid,4 });

	Line h1{ Point{400,350},Point{400,500} };
	Line h2{ Point{400,425},Point{550,425} };
	Line h3{ Point{550,350},Point{550,500} };
	h1.set_style(Line_style{ Line_style::solid,4 });
	h2.set_style(Line_style{ Line_style::solid,4 }); 
	h3.set_style(Line_style{ Line_style::solid,4 });

	win.attach(m1);
	win.attach(m2);
	win.attach(m3);
	win.attach(m4);
	win.attach(t1);
	win.attach(t2);
	win.attach(h1);
	win.attach(h2);
	win.attach(h3);

	win.set_label("Window3");
	win.wait_for_button();
	//exercise 4---------------------------------------
	win.detach(m1);
	win.detach(m2);
	win.detach(m3);
	win.detach(m4);
	win.detach(t1);
	win.detach(t2);
	win.detach(h1);
	win.detach(h2);
	win.detach(h3);

	Graph_lib::Rectangle r1{ Point{100,100},100,100 };
	Graph_lib::Rectangle r2{ Point{200,100},100,100 };
	Graph_lib::Rectangle r3{ Point{300,100},100,100 };
	Graph_lib::Rectangle r4{ Point{100,200},100,100 };
	Graph_lib::Rectangle r5{ Point{200,200},100,100 };
	Graph_lib::Rectangle r6{ Point{300,200},100,100 };
	Graph_lib::Rectangle r7{ Point{100,300},100,100 };
	Graph_lib::Rectangle r8{ Point{200,300},100,100 };
	Graph_lib::Rectangle r9{ Point{300,300},100,100 };
	r1.set_fill_color(Color::white); r1.set_style(Line_style{ Line_style::solid,3 });
	r2.set_fill_color(Color::red); r2.set_style(Line_style{ Line_style::solid,3 });
	r3.set_fill_color(Color::white); r3.set_style(Line_style{ Line_style::solid,3 });
	r4.set_fill_color(Color::red); r4.set_style(Line_style{ Line_style::solid,3 });
	r5.set_fill_color(Color::white); r5.set_style(Line_style{ Line_style::solid,3 });
	r6.set_fill_color(Color::red); r6.set_style(Line_style{ Line_style::solid,3 });
	r7.set_fill_color(Color::white); r7.set_style(Line_style{ Line_style::solid,3 });
	r8.set_fill_color(Color::red); r8.set_style(Line_style{ Line_style::solid,3 });
	r9.set_fill_color(Color::white); r9.set_style(Line_style{ Line_style::solid,3 });

	win.attach(r1);
	win.attach(r2);
	win.attach(r3);
	win.attach(r4);
	win.attach(r5);
	win.attach(r6);
	win.attach(r7);
	win.attach(r8);
	win.attach(r9);

	win.set_label("Window4");
	win.wait_for_button();
}