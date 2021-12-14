#include "Graphic/Graph.h"
#include "Graphic/Simple_window.h"

int main()
{
	Simple_window win{ Point{100,100},800,1000,"Window" };

	Graph_lib::Lines lines{};
	int h = 0;
	int v = 0;

	for (int i = 0; i <= 8; i++) 
		lines.add(Point{ 0,h + i * 100 }, Point{ win.x_max(),h + i * 100 });
	for (int i = 0; i <= 8; i++)
		lines.add(Point{ h + i * 100,0 }, Point{ h + i * 100,win.x_max() });
	
	lines.set_color(Color::black);
	win.attach(lines);
	win.wait_for_button();

	Vector_ref<Graph_lib::Rectangle> rec;
	Point p{ 0,0 };
	for (int i = 0; i < 8; i++) {
		rec.push_back(new Graph_lib::Rectangle{ Point{p},100,100 });
		rec[i].set_fill_color(Color::red);
		rec[i].set_color(Color::Transparency::invisible);
		win.attach(rec[i]);
		p.x += 100; p.y += 100;
	}
	win.wait_for_button();

	Image img1{ Point{0,200},"agif.gif" };
	Image img2{ Point{200,400},"agif.gif" };
	Image img3{ Point{400,600},"agif.gif" };
	win.attach(img1);
	win.attach(img2);
	win.attach(img3);

	win.wait_for_button();
	Image img{ Point{0,0},"100.jpg" };
	img.set_mask(Point{ 0,0 }, 100, 100);
	win.attach(img);
	bool newLine = 0; //fixed a bug where you need to click 2x to move when on new line
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if(!newLine)
				win.wait_for_button();
			newLine = false;
			img.move(100, 0);
		}
		img.move(-800, 100);
		win.wait_for_button();
		newLine = 1;
	}
}