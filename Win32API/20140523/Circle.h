#pragma once

#include <windows.h>

struct Point : public POINT
{
	Point(const LONG& _x = 0, const LONG& _y = 0);
};

class Circle
{
public :
	Circle();
	~Circle();

	void Draw(HDC);

	void SetColor(const COLORREF& clr);
	void SetCenter(const Point& pt);
	void SetRadius(const LONG& r);

private :
	Point center;
	LONG radius;
	COLORREF color;
};
