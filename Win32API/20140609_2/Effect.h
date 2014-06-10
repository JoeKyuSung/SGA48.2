#pragma once

#include "BaseType.h"
#include "Object.h"

class Effect : public Object
{
public :
	Effect();
	~Effect();

	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);

	virtual bool IsCollide(Object* );

	virtual void DoBreak();

	void SetRadius(const LONG& r);
	void SetAngle(const float& ang);

	LONG GetRadius() const;

private :
	LONG theta;
	LONG radius;

	DWORD update_dt;
	DWORD update_delay;

	LONG speed;
};