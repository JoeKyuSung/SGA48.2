#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;

	static HBITMAP hCard[3] = {0};

	static std::list<HBITMAP> cardlist;

	static int index = 0;
	static int current = 0;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

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
		//::SetTimer(hWnd, 0, 10, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		for (int i = 0; i < 3; i++)
		{
			::DeleteObject(hCard[i]);
		}

		//::KillTimer(hWnd, 0);

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

		BITMAP bm;
		::GetObject(hCard[0], sizeof(BITMAP), &bm);

		int cx = bm.bmWidth;
		int cy = bm.bmHeight;

		int x = (rc.width() - cx)/2;
		int y = (rc.height() - cy)/2;

		Rect rcBox(x, y, x+cx,y+cy);

		::DrawCard(hdc, cardlist, rcBox, current, current);


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
	//else if (uMsg == WM_TIMER)
	//{
	//	// TODO

	//	dt = ::GetTickCount() - st;
	//	st = ::GetTickCount();

	//	// redraw
	//	RECT rc;
	//	::GetClientRect(hWnd, &rc);
	//	::InvalidateRect(hWnd, &rc, TRUE);

	//	return 0;
	//}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
