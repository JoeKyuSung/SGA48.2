#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;

	static HBITMAP hCard[3] = {0};

	static std::list<HBITMAP> cardlist;

	static int index = 0;
	static int current = 0;

	static HDC hMainDC = NULL;
	static HDC hMemDC = NULL;
	static HBITMAP hMemBitmap = NULL;
	static HBITMAP hOldMemBitmap = NULL;

	static BYTE alpha = 0;
	static bool bPlus = true;

	static DWORD update_dt = 0;
	static DWORD update_delay = 1;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		hMainDC = ::GetDC(hWnd);
		hMemDC = ::CreateCompatibleDC(hMainDC);
		hMemBitmap = ::CreateCompatibleBitmap(hMainDC, rc.width(), rc.height());
		hOldMemBitmap = ::Select(hMemDC, hMemBitmap);

		for (int i = 0; i < 3; i++)
		{
			std::wostringstream oss;
			oss << std::setw(2) << std::setfill(L'0') << i+1 << _T(".bmp");

			hCard[i] = (HBITMAP)::LoadImage(NULL, oss.str().c_str(),
				IMAGE_BITMAP, 0, 0,
				LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);
		}

		cardlist.push_back(hCard[index++%3]);

		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 1, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		for (int i = 0; i < 3; i++)
		{
			::DeleteObject(hCard[i]);
		}

		::Select(hMemDC, hOldMemBitmap);
		::DeleteObject(hMemBitmap);
		::DeleteDC(hMemDC);
		::ReleaseDC(hWnd, hMainDC);

		::KillTimer(hWnd, 0);

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO
		Rect rc;
		::GetClientRect(hWnd, &rc);

		::SetDCBrushColor(hMemDC, RGB(255,255,255));
		::FillRect(hMemDC, &rc, (HBRUSH)::GetStockObject(DC_BRUSH));

		BITMAP bm;
		::GetObject(hCard[0], sizeof(BITMAP), &bm);

		int cx = bm.bmWidth;
		int cy = bm.bmHeight;

		int x = (rc.width() - cx)/2;
		int y = (rc.height() - cy)/2;

		Rect rcBox(x, y, x+cx,y+cy);

		::InflateRect(&rcBox, -rcBox.width()*0.1, -rcBox.height()*0.1);

		::DrawCard(hMemDC, cardlist, rcBox, current, current, 255);


		HBITMAP hImg = (HBITMAP)::LoadImage(NULL, _T("onepiece.bmp"),
			IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

		HDC hImgDC = ::CreateCompatibleDC(hMemDC);
		HBITMAP hOldImg = ::Select(hImgDC, hImg);

		::GetObject(hImg, sizeof(BITMAP), &bm);

		cx = bm.bmWidth;
		cy = bm.bmHeight;

		x = (rc.width() - cx)/2;
		y = (rc.height() - cy)/2;

		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = alpha;
		bf.AlphaFormat = 0;

		::GdiAlphaBlend(hMemDC, x, y, cx, cy,
			hImgDC, 0, 0, bm.bmWidth, bm.bmHeight, bf);

		::Select(hImgDC, hOldImg);
		::DeleteDC(hImgDC);

		::DeleteObject(hImg);

		::BitBlt(hdc, 0,0, rc.width(), rc.height(),
			hMemDC, 0, 0, SRCCOPY);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_KEYDOWN)
	{
		if ((::GetAsyncKeyState(VK_ADD) & 0x8000) == 0x8000)
		{
			cardlist.push_back(hCard[index++%3]);
		}
		if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
		{
			current--;
			if (current < 0)
				current = 0;
		}
		if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
		{
			current++;
			if (current >= cardlist.size())
				current = cardlist.size()-1;
		}

		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		if (update_dt > update_delay)
		{
			int count = update_dt / update_delay;

			for (int i = 0; i < count; i++)
			{
				if (bPlus)
					alpha++;
				else
					alpha--;

				if (alpha == 255)
					bPlus = false;
				else if (alpha == 0)
					bPlus = true;
			}

			update_dt %= update_delay;
		}

		update_dt += dt;

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
