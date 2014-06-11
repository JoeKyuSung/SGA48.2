﻿#include "windefine.h"

void DrawCard(HDC hdc, 
			  std::list<HBITMAP>& cardlist, 
			  const Rect& rcBox, 
			  const int& idx, 
			  const int& current)
{
	// 왼쪽 있냐
	if (idx - 1 >= 0 && idx-1 < current)
	{
		Rect rcLeft = rcBox;
		::OffsetRect(&rcLeft, -rcBox.width()/2, 0);
		::InflateRect(&rcLeft, -rcLeft.width()*0.1, -rcLeft.height()*0.1);
		DrawCard(hdc, cardlist, rcLeft, idx-1, current);
	}

	// 오른쪽 있냐
	if (idx + 1 < cardlist.size() && idx+1 > current)
	{
		Rect rcRight = rcBox;
		::OffsetRect(&rcRight, rcBox.width()/2, 0);
		::InflateRect(&rcRight, -rcRight.width()*0.1, -rcRight.height()*0.1);
		DrawCard(hdc, cardlist, rcRight, idx+1, current);
	}

	// 내꺼 그려라.
	std::list<HBITMAP>::iterator it = cardlist.begin();
	std::advance(it, idx);
	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap = ::Select(hBitmapDC, (*it));

	BITMAP bm;
	::GetObject(*it, sizeof(BITMAP), &bm);


	::StretchBlt(hdc, rcBox.left, rcBox.top, rcBox.width(), rcBox.height(),
		hBitmapDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	::Select(hBitmapDC, hOldBitmap);
	::DeleteDC(hBitmapDC);
}
