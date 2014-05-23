#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int count = 10;
	static Point pt[count];

	if (uMsg == WM_CREATE)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		LONG width = rc.right - rc.left;
		LONG height = rc.bottom - rc.top;

		for (int  i = 0; i < count; i ++)
		{
			pt[i] = Point(rand()%width, rand()%height);
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
			Circle one;
			one.SetRadius(30);
			one.SetCenter(pt[i]);
			one.SetColor(RGB(rand()%256,rand()%256,rand()%256));

			one.Draw(hdc);
		}

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}