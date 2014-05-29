#include "Tank.h"

Tank::Tank()
: radius(10)
, hOwner(NULL)
, speed(5)
, theta(0)
, input_dt(0), input_delay(100)
{
	_changepoint();
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
		theta -= float(speed);
	}
	if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
	{
		theta += float(speed);
	}
	if ((::GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000)
	{
		if (input_dt >= input_delay)
		{
			Missile* pMissile = new Missile;
			pMissile->SetPosition(ptEnd);
			pMissile->SetRadius(5);
			pMissile->SetAngle(theta);
			pMissile->SetSpeed(5);

			MissileDepot.push(pMissile);

			input_dt -= input_delay;
		}
	}

	input_dt += tick;
}
void Tank::Update(DWORD tick)
{
	// TODO
	_changepoint();
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

	_changepoint();
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
void Tank::_changepoint()
{
	ptEnd.x = LONG(center.x + 100*sin(theta*D2R));
	ptEnd.y = LONG(center.y - 100*cos(theta*D2R));
}
