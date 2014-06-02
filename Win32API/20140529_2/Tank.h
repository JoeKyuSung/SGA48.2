#pragma once

#include <windows.h>
#include "BaseType.h"
#include "Object.h"
#include "Bullet.h"
#include "Block.h"
#include "Collision.h"

class Tank : public Object
{
public :
	Tank();
	virtual ~Tank();

public :
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();

	void SetRadius(const LONG& r);
	void SetLength(const LONG& l);
	void SetFireDelay(const DWORD& d);
	void SetKeyMapping(const int& fire,
					   const int& left,
					   const int& right,
					   const int& forward,
					   const int& backward);

	void AddHealth(const int& diff);

   LONG GetRadius() const;

private :
	void _changepoint();

private :
	Point ptEnd;
	LONG radius;
	LONG length;

	LONG theta;

	// fire 
	DWORD fire_dt;
	DWORD fire_delay;

	int key_fire;
	int key_left;
	int key_right;
	int key_forward;
	int key_backward;

	int hp_total;
	int hp_current;
	COLORREF hp_color;
};
