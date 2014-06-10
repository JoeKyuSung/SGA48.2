#include "Block.h"

Block::Block()
   : size(20), hp(100)
   , Object(OBJ_BLOCK, true)
{
   _setRect();
}
Block::~Block()
{
}

void Block::Input(DWORD)
{
}
void Block::Update(DWORD)
{
}
void Block::Draw(HDC hdc)
{
   for (int i = 0; i < hp/25 + 1; i++)
   {
      ::Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
   }

   std::wostringstream oss;
   oss << _T("hp : ") << hp;

   Rect rc = Rect(pos()-Point(size,2*size), pos()-Point(-size,size));
   ::DrawText(hdc, oss.str().c_str(), -1, &rc, DT_TOP);
}

bool Block::IsCollide(Object* obj)
{
   if (obj->type() == OBJ_TANK)
   {
      Tank* pTank = dynamic_cast<Tank*>(obj);
      Point pt = pTank->GetPosition();
      LONG r = pTank->GetRadius();
      for (int i = 0; i < hp/25 + 1; i++)
      {
         if (Collision(rc[i], pt, r))
            return true;
      }
   }
   else if (obj->type() == OBJ_BULLET)
   {
      Bullet* pBullet = dynamic_cast<Bullet*>(obj);
      Point pt = pBullet->GetPosition();
      LONG r = pBullet->GetRadius();
      for (int i = 0; i < hp/25 + 1; i++)
      {
         if (Collision(rc[i], pt, r))
            return true;
      }
   }

   return false;
}

void Block::DoBreak()
{
   hp -= 1;

   if (hp == 0)
      SetNeedToClean();
}

void Block::SetSize(const LONG& s)
{
   size = s;
   _setRect();
}

const Rect* Block::GetRect() const
{
   return rc;
}
int Block::GetCount() const
{
   return (hp/25);
}

void Block::_setRect()
{
   rc[0] = Rect(pos().x-size,pos().y-size,pos().x,pos().y);
   rc[1] = Rect(pos().x,pos().y,pos().x + size,pos().y + size);
   rc[2] = Rect(pos().x-size,pos().y,pos().x,pos().y + size);
   rc[3] = Rect(pos().x,pos().y-size,pos().x + size,pos().y);
}