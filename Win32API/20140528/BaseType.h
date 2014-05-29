#pragma once

#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define D2R float(M_PI/180)

struct Point : public POINT
{
	Point(const LONG& _x = 0, const LONG& _y = 0);

	Point operator + (const Point& o) const;
};

struct Size : public SIZE
{
	Size();
	Size(const LONG& w, const LONG& h);
};

struct Rect : public RECT
{
	Rect();
	Rect(const LONG& l, const LONG& t, const LONG& r, const LONG& b);
	Rect(const Point& pt, const Size& cs);

	Point lefttop() const;
	Point rightbottom() const;
	Point center() const;
	LONG width() const;
	LONG height() const;
};