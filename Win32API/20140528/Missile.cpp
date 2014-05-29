#include "Missile.h"

Missile::Missile()
: radius(5)
, speed(5)
, theta(0)
{
}
Missile::~Missile()
{
}

void Missile::Input(DWORD)
{
}
void Missile::Update(DWORD)
{
	// TODO
	center.x = center.x + LONG(speed*sin(theta*D2R));
	center.y = center.y - LONG(speed*cos(theta*D2R));
}
void Missile::Draw(HDC hdc)
{
	::Ellipse(hdc, center.x - radius, center.y - radius,
		center.x + radius, center.y + radius);
}

void Missile::SetPosition(const Point& pt)
{
	center = pt;
}
void Missile::SetRadius(const LONG& r)
{
	radius = r;
}
void Missile::SetSpeed(const LONG& s)
{
	speed = s;
}
void Missile::SetAngle(const float& angle)
{
	theta = angle;
}
Point Missile::GetPosition() const
{
	return center;
}
