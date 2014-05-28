#include "BaseType.h"

Point::Point(const LONG& _x, const LONG& _y)
{
	x = _x;
	y = _y;
}
Point Point::operator + (const Point& o) const
{
	return Point(x + o.x, y + o.y);
}


Size::Size()
{
	cx = 0;
	cy = 0;
}
Size::Size(const LONG& w, const LONG& h)
{
	cx = w;
	cy = h;
}

Rect::Rect()
{
	left = top = right = bottom = 0;
}
Rect::Rect(const LONG& l, const LONG& t, const LONG& r, const LONG& b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}
Rect::Rect(const Point& pt, const Size& cs)
{
	left = pt.x - cs.cx/2;
	top = pt.y - cs.cy/2;
	right = left + cs.cx;
	bottom = top + cs.cy;
}

Point Rect::lefttop() const
{
	return Point(left, top);
}
Point Rect::rightbottom() const
{
	return Point(right, bottom);
}
Point Rect::center() const
{
	return Point((left+right)/2, (top+bottom)/2);
}
LONG Rect::width() const
{
	return (right - left);
}
LONG Rect::height() const
{
	return (bottom - top);
}
