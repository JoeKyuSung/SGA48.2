﻿#pragma once

#include <windows.h>
#include "BaseType.h"
#include "Utility.hpp"
#include "Object.h"
#include "Tank.h"
#include "Block.h"
#include "Effect.h"

class Bullet : public Object
{
public :
	Bullet();
	virtual ~Bullet();

public :
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();

	void SetRadius(const LONG& r);
	void SetAngle(const float& ang);
	void SetInitSpeed(const LONG& s);

	LONG GetRadius() const;

private :
	LONG radius;

	float angle;

	LONG init_speed_x;
	LONG init_speed_y;

	LONG speed_y;
};

