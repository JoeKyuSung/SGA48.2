#include "Tank.h"

Tank::Tank()
: radius(50), length(70)
, fire_dt(0), fire_delay(500)
, key_fire(VK_SPACE), key_left(VK_LEFT)
, key_right(VK_RIGHT), key_forward(VK_UP)
, key_backward(VK_DOWN)
, key_powerup(VK_ADD), key_powerdown(VK_SUBTRACT)
, hp_total(100), hp_current(100), hp_color(RGB(255,0,0))
, theta(0)
, power(10)
, Object(OBJ_TANK, true)
{
	_changepoint();
}
Tank::~Tank()
{
}

void Tank::Input(DWORD tick)
{
	// 0x8001
	if ((::GetAsyncKeyState(key_left) & 0x8000) == 0x8000)
	{
		theta -= 5;
	}
	if ((::GetAsyncKeyState(key_right) & 0x8000) == 0x8000)
	{
		theta += 5;
	}
	if ((::GetAsyncKeyState(key_forward) & 0x8000) == 0x8000)
	{
		pos().x = pos().x + 4*sin(theta*D2R);
		pos().y = pos().y - 4*cos(theta*D2R);
	}
	if ((::GetAsyncKeyState(key_backward) & 0x8000) == 0x8000)
	{
		pos().x = pos().x - 2*sin(theta*D2R);
		pos().y = pos().y + 2*cos(theta*D2R);
	}
	if ((::GetAsyncKeyState(key_powerup) & 0x8000) == 0x8000)
	{
		power++;
	}
	if ((::GetAsyncKeyState(key_powerdown) & 0x8000) == 0x8000)
	{
		power--;
	}

	if ((::GetAsyncKeyState(key_fire) & 0x8000) == 0x8000)
	{
		if (fire_dt > fire_delay)
		{
			Bullet* pMissile = new Bullet;
			pMissile->SetPosition(ptEnd);
			pMissile->SetRadius(10);
			pMissile->SetAngle(float(theta));
			pMissile->SetInitSpeed(power);

			ObjectDepot.push(pMissile);

			fire_dt = 0;
		}
	}

	fire_dt += tick;

	//::GetKeyState();
	//::GetKeyboardState();
}
void Tank::Update(DWORD)
{
	_changepoint();
}
void Tank::Draw(HDC hdc)
{
	::Ellipse(hdc, pos().x - radius, pos().y - radius,
		pos().x + radius, pos().y + radius);

	const int margin = 30;

	::Rectangle(hdc, pos().x - radius, 
		pos().y - radius - margin,
		pos().x + radius,
		pos().y - radius - margin + 20);

	HBRUSH hBrush = ::CreateSolidBrush(hp_color);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

	::Rectangle(hdc, pos().x - radius, 
		pos().y - radius - margin,
		pos().x - radius + (2*radius)*hp_current/hp_total,
		pos().y - radius - margin + 20);

	::SelectObject(hdc, hOldBrush);
	::DeleteObject(hBrush);

	::MoveToEx(hdc, pos().x, pos().y, NULL);
	::LineTo(hdc, ptEnd.x, ptEnd.y);

}

bool Tank::IsCollide(Object* obj)
{
   if (obj->type() == OBJ_BULLET)
   {
      Bullet* pBullet = dynamic_cast<Bullet*>(obj);
      Point pt = pBullet->GetPosition();
      LONG r = pBullet->GetRadius();

      return Collision(pos(), radius, pt, r);
   }
   else if (obj->type() == OBJ_BLOCK)
   {
      return obj->IsCollide(this);
   }

   return false;
}
void Tank::DoBreak()
{
   AddHealth(-1);
}

void Tank::SetRadius(const LONG& r)
{
	radius = r;
}
void Tank::SetLength(const LONG& l)
{
	length = l;
}
void Tank::SetFireDelay(const DWORD& d)
{
	fire_delay = d;
}
void Tank::SetKeyMapping(const int& fire,
					   const int& left,
					   const int& right,
					   const int& forward,
					   const int& backward)
{
	key_fire = fire;
	key_left = left;
	key_right = right;
	key_forward = forward;
	key_backward = backward;
}
void Tank::AddHealth(const int& diff)
{
	hp_current += diff;

	if (hp_current < 0)
		hp_current = 0;
	else if (hp_current > hp_total)
		hp_current = hp_total;
}

LONG Tank::GetRadius() const
{
   return radius;
}

void Tank::_changepoint()
{
	ptEnd.x = LONG(pos().x + length*sin(theta*D2R));
	ptEnd.y = LONG(pos().y - length*cos(theta*D2R));
}
