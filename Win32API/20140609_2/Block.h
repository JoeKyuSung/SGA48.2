#pragma once

#include <Windows.h>
#include <sstream>
#include <tchar.h>
#include "BaseType.h"
#include "Object.h"
#include "Bullet.h"
#include "Tank.h"

class Block : public Object
{
public :
   Block();
   virtual ~Block();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();

   void SetSize(const LONG& s);

   const Rect* GetRect() const;
   int GetCount() const;

private :
   void _setRect();

private :
   LONG size;
   Rect rc[4];

   int hp;
};
