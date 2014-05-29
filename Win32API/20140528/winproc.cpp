#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Tank mine;
	static Tank other;
	static DWORD st = 0;
	static DWORD dt = 0;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		other.Attach(hWnd);
		other.SetPosition(Point(200, 200));
		other.SetRadius(50);
		other.SetKeyboard('A', 'D', VK_LSHIFT, 'W', 'S');

		mine.Attach(hWnd);
		mine.SetPosition(Point(600, 200));
		mine.SetRadius(50);

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

		mine.Draw(hdc);
		other.Draw(hdc);

		MissileDepot.Draw(hdc);


		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		mine.Input(dt);
		mine.Update(dt);

		other.Input(dt);
		other.Update(dt);

		MissileDepot.Input(dt);
		MissileDepot.Update(dt);

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