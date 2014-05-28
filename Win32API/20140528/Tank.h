#pragma once

#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "BaseType.h"

#define D2R float(M_PI/180)

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
	HWND hOwner;

	Point center;
	LONG radius;

	LONG speed;
	Point ptEnd;
	LONG theta;
};
