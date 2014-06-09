#include "Effect.h"

Effect::Effect()
{
}
Effect::~Effect()
{
}

void Effect::Input(DWORD tick)
{
}
void Effect::Update(DWORD tick)
{
	center.x = LONG(center.x + speed*sin(theta*D2R));
	center.y = LONG(center.y - speed*cos(theta*D2R));

	radius = radius*0.99;
}
void Effect::Draw(HDC hdc)
{
	::Ellipse(hdc, center.x - radius, center.y - radius,
		center.x + radius, center.y + radius);
}

void Effect::SetPosition(const Point& pt)
{
	center = pt;
}
void Effect::SetRadius(const float& r)
{
	radius = r;
}
void Effect::SetAngle(const LONG& ang)
{
	theta = ang;
}
void Effect::SetSpeed(const LONG& s)
{
	speed = s;
}

Point Effect::GetPosition() const
{
	return center;
}
float Effect::GetRadius() const
{
	return radius;
}
