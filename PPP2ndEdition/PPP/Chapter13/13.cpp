#include "13.h"
#include <iostream>

using namespace Graph_lib;
using namespace exercise;

Arc::Arc(Point p, int ww, int hh)
	:w{ ww }, h{ hh } 
{
	add(Point{ p.x - w, p.y - h });
}

Arc::Arc(Point p, int ww, int hh, int start, int end)
	: w{ ww }, h{ hh }, s{start}, e{end}
{
	add(Point{ p.x - w, p.y - h });
}

Arc::Arc(Point p, int r)
	: w{ r }, h{ r }
{
	add(Point{ p.x - w, p.y - h });
}

Arc::Arc(Point p, int r, int start, int end)
	: w{ r }, h{ r }, s{ start }, e{ end }
{
	add(Point{ p.x - w, p.y - h });
}

Point Arc::center() const {
	return Point{ point(0).x + w, point(0).y + h };
}

void Arc::draw_lines() const {
	if (color().visibility())
		fl_arc(point(0).x, point(0).y, w+w, h+h,s,e);
}

//---------------------------------------------------------


Box::Box(Point p, int w, int h)
{
	sides.add(Point{ p.x + r, p.y }, Point{ p.x + w - r, p.y });    // top
	sides.add(Point{ p.x + w, p.y + r }, Point{ p.x + w, p.y + h - r });  // right
	sides.add(Point{ p.x + w - r, p.y + h }, Point{ p.x + r, p.y + h });  // bottom
	sides.add(Point{ p.x, p.y + h - r }, Point{ p.x, p.y + r });      // left

	corners.push_back(new Arc{ Point{p.x + w - r, p.y + r}, r, 0, 90 });        // tr
	corners.push_back(new Arc{ Point{p.x + r, p.y + r}, r, 90, 180 });        // tl
	corners.push_back(new Arc{ Point{p.x + r, p.y + h - r}, r, 180, 270 });     // bl
	corners.push_back(new Arc{ Point{p.x + w - r, p.y + h - r}, r, 270, 360 });   // br
}

Box::Box(Point p, int w, int h, int rr)
	:r{ rr }
{
	sides.add(Point{ p.x + r, p.y }, Point{ p.x + w - r, p.y });    // top
	sides.add(Point{ p.x + w, p.y + r }, Point{ p.x + w, p.y + h - r });  // right
	sides.add(Point{ p.x + w - r, p.y + h }, Point{ p.x + r, p.y + h });  // bottom
	sides.add(Point{ p.x, p.y + h - r }, Point{ p.x, p.y + r });      // left

	corners.push_back(new Arc{ Point{p.x + w - r, p.y + r}, r, 0, 90 });        // tr
	corners.push_back(new Arc{ Point{p.x + r, p.y + r}, r, 90, 180 });        // tl
	corners.push_back(new Arc{ Point{p.x + r, p.y + h - r}, r, 180, 270 });     // bl
	corners.push_back(new Arc{ Point{p.x + w - r, p.y + h - r}, r, 270, 360 });   // br
}

void Box::draw_lines() const {
	sides.draw_lines();
	for (int i = 0; i < corners.size(); ++i)
		corners[i].draw_lines();
}


