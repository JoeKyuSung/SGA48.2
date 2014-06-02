#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static const int count = 15;
	static Point ptMouse[count];
	static LONG radius = 50;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);


		st = ::GetTickCount();
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

		for (int i = count-1; i >= 0; i--)
		{
			BYTE g = 17*i; // 17*15 = 255
			BYTE b = g;

			HBRUSH hBrush = ::CreateSolidBrush(RGB(255,g,b));
			HBRUSH hOldBrush = ::Select(hdc, hBrush);

			HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(255,g,b));
			HPEN hOldPen = ::Select(hdc, hPen);

			int r = radius - (2*i);
			::Ellipse(hdc, ptMouse[i].x - r,
				ptMouse[i].y - r,
				ptMouse[i].x + r,
				ptMouse[i].y + r);

			::Select(hdc, hOldPen);
			::DeleteObject(hPen);

			::Select(hdc, hOldBrush);
			::DeleteObject(hBrush);

		}


		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		::GetCursorPos(&ptMouse[0]);
		ptMouse[0] = ptMouse[0].ToClient(hWnd);

		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		Point tmp = ptMouse[0];
		for (int i = 1; i < count; i++)
		{
			tmp = follow(ptMouse[i], tmp);
		}

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

Point follow(Point& dest, const Point& src)
{
	Point tmp = dest;
	dest = src;

	return tmp;
}