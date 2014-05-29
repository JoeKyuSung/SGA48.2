#pragma once

#include <windows.h>
#include "BaseType.h"
#include "Missile.h"

class Tank
{
public :
	Tank();
	~Tank();

	void Attach(HWND);

	void Input(DWORD tick);
	void Update(DWORD tick);
	void Draw(HDC);

	void SetPosition(const Point& pt);
	void SetRadius(const LONG& r);
	void SetSpeed(const LONG& s);
	Point GetCenter() const;

private :
	void _changepoint();

private :
	HWND hOwner;

	Point center;
	LONG radius;

	LONG speed;
	Point ptEnd;

	float theta;

	DWORD input_dt;
	DWORD input_delay;
};
