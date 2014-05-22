#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int count = 10;
	static POINT pt[count];
	const LONG radius = 30;

	if (uMsg == WM_CREATE)
	{

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InflateRect(&rc, -radius, -radius);

		LONG cx = rc.right - rc.left;
		LONG cy = rc.bottom - rc.top;

		for (int i = 0; i < count; i++)
		{
			pt[i].x = rand()%cx + radius;
			pt[i].y = rand()%cy + radius;
		}

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO.....
		for (int i = 0; i < count; i++)
		{
			::Ellipse(hdc, pt[i].x - radius,
							pt[i].y - radius,
							pt[i].x + radius,
							pt[i].y + radius);
		}

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}