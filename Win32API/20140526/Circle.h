#pragma once

#include <windows.h>
#include <math.h>

struct Point : public POINT
{
	Point(const LONG& _x = 0, const LONG& _y = 0);
};

class Circle
{
public :
	Circle();
	~Circle();

	void Attach(HWND);

	void Input(const Point& pt);
	void Update();
	void Draw(HDC);

	void SetColor(const COLORREF& clr);
	void SetCenter(const Point& pt);
	void SetRadius(const LONG& r);
	void SetSpeed(const LONG& s);
	Point GetCenter() const;

private :
	HWND hOwner;

	Point center;
	LONG radius;
	COLORREF color;

	LONG speed;

	bool bSelect;
};
