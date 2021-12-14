#include "../std_lib_facilities.h"
#include "Graphic/Graph.h"
#include "Graphic/Simple_window.h"

int main()
{


    Point tl{ 100,100 };

    Simple_window win{ tl,600,400,"Canvas#1" };

    win.wait_for_button();

    Axis xa{ Axis::x,Point{20,350},300,30,"x axis" };
    win.attach(xa);
    win.set_label("Canvas#2");
    win.wait_for_button();

    Axis ya{ Axis::y,Point{20,350},300,30,"y axis" };
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);
    win.attach(ya);
    win.set_label("Canvas#3");
    win.wait_for_button();

    Function sine{ sin,0,100,Point{20,300},1000,50,50 };
    sine.set_color(Color::magenta);
    win.attach(sine);
    win.set_label("Canvas#4");
    win.wait_for_button();

    Graph_lib::Polygon poly;
    poly.add(Point{ 300,200 });
    poly.add(Point{ 350,100 });
    poly.add(Point{ 400,200 });
    poly.set_color(Color::red);
    poly.set_fill_color(Color::white);
    poly.set_style(Line_style(Line_style::dash, 4));
    win.attach(poly);
    win.set_label("Canvas#5");
    win.wait_for_button();

    Graph_lib::Rectangle r{ Point{200,200},100,50 };
    r.set_color(Color::dark_yellow);
    r.set_fill_color(Color::yellow);
    r.set_style(Line_style(Line_style::solid, 1));
    win.attach(r);
    win.set_label("Canvas#6");
    win.wait_for_button();

    Graph_lib::Closed_polyline closed;
    closed.add(Point{ 100,50 });
    closed.add(Point{ 200,50 });
    closed.add(Point{ 200,100 });
    closed.add(Point{ 100,100 });
    closed.add(Point{ 50,75 });
    closed.set_fill_color(Color::green);
    closed.set_color(Color::dark_green);
    win.attach(closed);
    win.set_label("Canvas#7");
    win.wait_for_button();

    Text t{ Point{150,150}, "Hello, graphical world!" };
    win.attach(t);
    win.set_label("Canvas#8");
    win.wait_for_button();

    t.set_font(Font::times_bold_italic);
    t.set_font_size(20);
    win.set_label("Canvas#9");
    win.wait_for_button();

    Image ii{ Point{100,50}, "image.jpg" };
    win.attach(ii);
    win.set_label("Canvas#10");
    win.wait_for_button();

    ii.move(100, 200);
    win.set_label("Canvas#11");
    win.wait_for_button();

    Circle c{ Point{100,200},50 };
    c.set_color(Color::dark_green);
    Graph_lib::Ellipse e{ Point{100,200}, 75, 25 };
    e.set_color(Color::blue);
    Mark m{ Point{100,200}, 'o' };
    win.attach(c);
    win.attach(e);
    win.attach(m);
    win.set_label("Canvas#12");
    win.wait_for_button();

    ostringstream oss;
    oss << "screen size: " << x_max() << "*" << y_max() << "; window size: " << win.x_max() << "*" << win.y_max();
    Text sizes{ Point{100,20}, oss.str() };
    win.attach(sizes);
    win.set_label("Canvas#13");
    win.wait_for_button();

    Image cal{ Point{400,20},"snow_cpp.gif" };
    cal.set_mask(Point{ 40,40 }, 200, 150);
    win.attach(cal);
    win.set_label("Canvas#14");
    win.wait_for_button();
}