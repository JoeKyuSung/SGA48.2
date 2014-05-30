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
Point Point::operator - (const Point& o) const
{
	return Point(x - o.x, y - o.y);
}
LONG Point::operator ^ (const Point& o) const
{
	Point d = *this - o;
	return (d.x*d.x + d.y*d.y);
}
Point Point::ToScreen(HWND hWnd) const
{
	Point tmp(*this);
	::ClientToScreen(hWnd, &tmp);
	return tmp;
}
Point Point::ToClient(HWND hWnd) const
{
	Point tmp(*this);
	::ScreenToClient(hWnd, &tmp);
	return tmp;
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
Rect::Rect(const Point& lt, const Point& rb)
{
	left = lt.x;
	top = lt.y;
	right = rb.x;
	bottom = rb.y;
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
Rect Rect::ToScreen(HWND hWnd) const
{
	Point lt = lefttop();
	Point rb = rightbottom();

	return Rect(lt.ToScreen(hWnd), rb.ToScreen(hWnd));
}
Rect Rect::ToClient(HWND hWnd) const
{
	Point lt = lefttop();
	Point rb = rightbottom();

	return Rect(lt.ToClient(hWnd), rb.ToClient(hWnd));
}
