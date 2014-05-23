#include "Circle.h"

Point::Point(const LONG& _x, const LONG& _y)
{
	x = _x;
	y = _y;
}

Circle::Circle()
: radius(10), color(RGB(0,0,0))
{
}
Circle::~Circle()
{
}

void Circle::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

	HPEN hPen = ::CreatePen(PS_SOLID, 1, color);
	HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

	::Ellipse(hdc, center.x - radius, center.y - radius,
		center.x + radius, center.y + radius);

	::SelectObject(hdc, hOldPen);
	::DeleteObject(hPen);

	::SelectObject(hdc, hOldBrush);
	::DeleteObject(hBrush);
}

void Circle::SetColor(const COLORREF& clr)
{
	color = clr;
}
void Circle::SetCenter(const Point& pt)
{
	center = pt;
}
void Circle::SetRadius(const LONG& r)
{
	radius = r;
}
