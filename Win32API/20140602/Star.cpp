#include "Star.h"

Star::Star()
: speed(5), size(100)
{
}
Star::~Star()
{
}

void Star::Input(DWORD)
{
}
void Star::Update(DWORD)
{
	size -= 5;

	center.x = center.x + speed*sin(theta*D2R);
	center.y = center.y - speed*cos(theta*D2R);
}
void Star::Draw(HDC hdc)
{
	HBITMAP hStar = (HBITMAP)::LoadImage(NULL,
		_T("star.bmp"), IMAGE_BITMAP, 0,0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap = ::Select(hBitmapDC, hStar);

	BITMAP bm;
	::GetObject(hStar, sizeof(BITMAP), &bm);
	int width = bm.bmWidth;
	int height = bm.bmHeight;

	::GdiTransparentBlt(hdc, center.x - width/2, center.y - height/2,
		int(width*size/100), int(height*size/100),
		hBitmapDC, 0, 0,
		width, height,
		RGB(255,255,255));

	::Select(hBitmapDC, hOldBitmap);
	::DeleteDC(hBitmapDC);

	if (hStar)
		::DeleteObject(hStar);
}

void Star::SetPosition(const Point& pt)
{
	center = pt;
}
void Star::SetAngle(const LONG& ang)
{
	theta = ang;
}
void Star::SetSpeed(const LONG& s)
{
	speed = s;
}

Point Star::GetPosition() const
{
	return center;
}

