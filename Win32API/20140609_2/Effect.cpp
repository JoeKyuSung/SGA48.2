#include "Effect.h"

Effect::Effect()
: update_dt(0), update_delay(100)
, Object(OBJ_EFFECT, false)
, speed(5)
{
}
Effect::~Effect()
{
}

void Effect::Input(DWORD)
{
}
void Effect::Update(DWORD tick)
{
	if (update_dt > update_delay)
	{
		radius -= 1;
		if (radius < 0)
		{
			SetNeedToClean();
		}

		update_dt -= update_delay;
	}

	update_dt += tick;

	pos().x = pos().x + speed*sin(theta*D2R);
	pos().y = pos().y - speed*cos(theta*D2R);
}
void Effect::Draw(HDC hdc)
{
	::Ellipse(hdc, pos().x - radius, pos().y - radius,
		pos().x + radius, pos().y + radius);
}

bool Effect::IsCollide(Object* )
{
	return false;
}

void Effect::DoBreak()
{
	// do nothing...
}

void Effect::SetRadius(const LONG& r)
{
	radius = r;
}
void Effect::SetAngle(const float& ang)
{
	theta = ang;
}

LONG Effect::GetRadius() const
{
	return radius;
}
