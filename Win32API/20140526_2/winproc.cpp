#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT ptEnd = {200+150,200};
	static LONG theta = 0;

	if (uMsg == WM_CREATE)
	{
		::SetTimer(hWnd, 0, 1000, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO.....
		RECT rc;
		::GetClientRect(hWnd, &rc);

		::Rectangle(hdc, 0, 0, 400, 400);
		::Ellipse(hdc, 0, 0, 400, 400);

		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptEnd.x, ptEnd.y);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		theta += 6;
		if (theta >= 360)
			theta = 0;

		LONG L = 150;
		const float D2R = float(M_PI/180);

		ptEnd.x = LONG(200 + L*cos(theta*D2R));
		ptEnd.y = LONG(200 - L*sin(theta*D2R));

		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}