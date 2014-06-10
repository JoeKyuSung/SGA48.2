#include "BaseType.h"

Point::Point()
{
	x = y = 0;
}
Point::Point(const LONG& _x, const LONG& _y)
{
	x = _x;
	y = _y;
}
Point Point::operator + (const Point& o) const
{
   return Point(x+o.x, y+o.y);
}
Point Point::operator - (const Point& o) const
{
	return Point(x-o.x, y-o.y);
}
LONG Point::operator ^ (const Point& o) const
{
	// a^2 + b^2 = c^2
	Point d = *this - o;
	return (d.x*d.x + d.y*d.y);
}

Size::Size()
{
	cx = cy = 0;
}
Size::Size(const LONG& _cx, const LONG& _cy)
{
	cx = _cx;
	cy = _cy;
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
Rect::Rect(const Point& lt, const Point& rb)
{
   left = lt.x;
   top = lt.y;
   right = rb.x;
   bottom = rb.y;
}
Rect::Rect(const Point& pt, const Size& cs)
{
	left = pt.x - cs.cx/2;
	top = pt.y - cs.cy/2;
	right = left + cs.cx;
	bottom = top + cs.cy;
}
Point Rect::center() const
{
	return Point((left+right)/2, (top+bottom)/2);
}

LONG Rect::width() const
{
	return (right-left);
}
LONG Rect::height() const
{
	return (bottom - top);
}
float Rect::radius() const
{
   return sqrt(float(width()*width() + height()*height()))/2;
}