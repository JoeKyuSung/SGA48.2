#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (uMsg == WM_CREATE)
	{
		::SetTimer(hWnd, 0, 10, NULL);

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




		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO



		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}