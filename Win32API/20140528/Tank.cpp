#include "Tank.h"

Tank::Tank()
: radius(10)
, hOwner(NULL)
, speed(5)
, theta(0)
{
}
Tank::~Tank()
{
}
void Tank::Attach(HWND hWnd)
{
	hOwner = hWnd;
}
void Tank::Input(DWORD tick)
{
	// 0x8001
	if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
	{
		theta -= speed;
	}
	if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
	{
		theta += speed;
	}
	//::GetKeyState();
	//::GetKeyboardState();
}
void Tank::Update(DWORD tick)
{
	// TODO
	ptEnd.x = LONG(center.x + 100*cos((90-theta)*D2R));
	ptEnd.y = LONG(center.y - 100*sin((90-theta)*D2R));
}
void Tank::Draw(HDC hdc)
{
	::Ellipse(hdc, center.x - radius, center.y - radius,
		center.x + radius, center.y + radius);

	::MoveToEx(hdc, center.x, center.y, NULL);
	::LineTo(hdc, ptEnd.x, ptEnd.y);
}

void Tank::SetPosition(const Point& pt)
{
	center = pt;

	ptEnd.x = LONG(center.x + 100*cos((90-theta)*D2R));
	ptEnd.y = LONG(center.y - 100*sin((90-theta)*D2R));
}
void Tank::SetRadius(const LONG& r)
{
	radius = r;
}
void Tank::SetSpeed(const LONG& s)
{
	speed = s;
}
Point Tank::GetCenter() const
{
	return center;
}

