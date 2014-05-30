#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static Point ptMouse;
	static LONG radius = 20;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);


		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 10, NULL);

		::ShowCursor(FALSE);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::ShowCursor(TRUE);

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

		HBRUSH hBrush = ::CreateSolidBrush(RGB(255,0,0));
		HBRUSH hOldBrush = ::Select(hdc, hBrush);

		HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(255,0,0));
		HPEN hOldPen = ::Select(hdc, hPen);

		::Ellipse(hdc, ptMouse.x - radius,
			ptMouse.y - radius,
			ptMouse.x + radius,
			ptMouse.y + radius);

		::Select(hdc, hOldPen);
		::DeleteObject(hPen);

		::Select(hdc, hOldBrush);
		::DeleteObject(hBrush);


		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO

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