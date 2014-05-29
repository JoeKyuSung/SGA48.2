#include "Tank.h"

Tank::Tank()
: radius(10)
, hOwner(NULL)
, rotate_speed(5)
, move_speed(5)
, theta(0)
, input_dt(0), input_delay(100)
, key_left(VK_LEFT)
, key_right(VK_RIGHT)
, key_fire(VK_SPACE)
, key_forward(VK_UP)
, key_backward(VK_DOWN)
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
	if ((::GetAsyncKeyState(key_left) & 0x8000) == 0x8000)
	{
		theta -= float(rotate_speed);
	}
	if ((::GetAsyncKeyState(key_right) & 0x8000) == 0x8000)
	{
		theta += float(rotate_speed);
	}
	if ((::GetAsyncKeyState(key_fire) & 0x8000) == 0x8000)
	{
		if (input_dt >= input_delay)
		{
			Missile* pMissile = new Missile;
			pMissile->SetPosition(ptEnd);
			pMissile->SetRadius(5);
			pMissile->SetAngle(theta);
			pMissile->SetSpeed(5);

			MissileDepot.push(pMissile);

			input_dt = 0;
		}
	}
	if ((::GetAsyncKeyState(key_forward) & 0x8000) == 0x8000)
	{
		center.x = center.x + move_speed*sin(theta*D2R);
		center.y = center.y - move_speed*cos(theta*D2R);
	}
	if ((::GetAsyncKeyState(key_backward) & 0x8000) == 0x8000)
	{
		center.x = center.x - move_speed*sin(theta*D2R);
		center.y = center.y + move_speed*cos(theta*D2R);
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
void Tank::SetRotateSpeed(const LONG& s)
{
	rotate_speed = s;
}
void Tank::SetMoveSpeed(const LONG& s)
{
	move_speed = s;
}
Point Tank::GetCenter() const
{
	return center;
}
void Tank::SetKeyboard(const int& left, 
					   const int& right, 
					   const int& fire,
					   const int& forward,
					   const int& backward)
{
	key_left = left;
	key_right = right;
	key_fire = fire;
	key_forward = forward;
	key_backward = backward;
}
void Tank::_changepoint()
{
	ptEnd.x = LONG(center.x + 100*sin(theta*D2R));
	ptEnd.y = LONG(center.y - 100*cos(theta*D2R));
}
