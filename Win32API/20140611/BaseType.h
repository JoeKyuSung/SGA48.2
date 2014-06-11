#pragma once

#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define D2R (M_PI/180)

struct Point : public POINT
{
	Point();
	Point(const LONG& _x, const LONG& _y);

   Point operator + (const Point& o) const;
	Point operator - (const Point& o) const;
	LONG operator ^ (const Point& o) const;
};

struct Size : public SIZE
{
	Size();
	Size(const LONG& _cx, const LONG& _cy);
};

struct Rect : public RECT
{
	Rect();
	Rect(const LONG& l, const LONG& t, const LONG& r, const LONG& b);
   Rect(const Point& lt, const Point& rb);
	Rect(const Point& pt, const Size& cs);

	Point center() const;

	LONG width() const;
	LONG height() const;
   float radius() const;
};
