#include "Circle.h"

Point::Point(const LONG& _x, const LONG& _y)
{
	x = _x;
	y = _y;
}

Circle::Circle()
: radius(10), color(RGB(0,0,0))
, hOwner(NULL), speed(10)
, bSelect(false)
{
}
Circle::~Circle()
{
}
void Circle::Attach(HWND hWnd)
{
	hOwner = hWnd;
}
void Circle::Input(const Point& pt)
{
	LONG dx = center.x - pt.x;
	LONG dy = center.y - pt.y;

	float L = sqrt(float(dx*dx + dy*dy));

	if (L > radius)
		bSelect = false;
	else
		bSelect = true;
}
void Circle::Update()
{
	if (bSelect)
		SetColor(RGB(0,0,0));

	RECT rc;
	::GetClientRect(hOwner, &rc);
	LONG height = rc.bottom - rc.top;

	if (center.x + speed - radius > rc.right)
	{
		center.x = rc.left - radius;
		center.y = rand()%(height-radius-150) + radius;
	}
	else
	{
		center.x += speed;
	}
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
void Circle::SetSpeed(const LONG& s)
{
	speed = s;
}
Point Circle::GetCenter() const
{
	return center;
}

