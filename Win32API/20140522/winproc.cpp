#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO.....

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}