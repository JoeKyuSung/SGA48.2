#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		ObjectDepot.Attach(hWnd);

		Tank* pTank = new Tank;
		pTank->SetPosition(Point(rc.width()/4, rc.center().y));
		pTank->SetFireDelay(500);

		ObjectDepot.push(pTank);

		st = ::GetTickCount();

		::SetTimer(hWnd, 0, 10, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);

      // remove objects...
      ObjectDepot.clear();

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO
		RECT rc;
		::GetClientRect(hWnd, &rc);

      ObjectDepot.Draw(hdc);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		ObjectDepot.Input(dt);
		ObjectDepot.Update(dt);

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
