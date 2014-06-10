#include "Bullet.h"

Bullet::Bullet()
   : Object(OBJ_BULLET, true)
{
}
Bullet::~Bullet()
{
}
void Bullet::Input(DWORD)
{
}
void Bullet::Update(DWORD)
{
	// TODO
	Effect* pObj = new Effect;
	pObj->SetPosition(pos());
	pObj->SetRadius(radius/2);
	pObj->SetAngle(rand()%360);

	ObjectDepot.push(pObj);

	speed_y += 1;

	pos().x = pos().x + init_speed_x;
	pos().y = pos().y + speed_y;
}
void Bullet::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(255,255,0));
	HBRUSH hOldBrush = ::Select(hdc, hBrush);

	::Ellipse(hdc, pos().x - radius, pos().y - radius,
		pos().x + radius, pos().y + radius);

	::Select(hdc, hOldBrush);
	::DeleteObject(hBrush);
}

bool Bullet::IsCollide(Object* obj)
{
   if (obj->type() == OBJ_TANK)
   {
      return obj->IsCollide(this);
   }
   else if (obj->type() == OBJ_BLOCK)
   {
      return obj->IsCollide(this);
   }

   return false;
}
void Bullet::DoBreak()
{
   SetNeedToClean();
   //ObjectDepot.pop(this);
}

void Bullet::SetRadius(const LONG& r)
{
	radius = r;
}
void Bullet::SetAngle(const float& ang)
{
	angle = ang;
}
void Bullet::SetInitSpeed(const LONG& s)
{
	init_speed_x = s*sin(angle*D2R);
	init_speed_y = -s*cos(angle*D2R);

	speed_y = init_speed_y;
}
LONG Bullet::GetRadius() const
{
	return radius;
}
