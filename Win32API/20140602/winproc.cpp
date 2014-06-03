#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;

	static Point ptMouse;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		StarDepot.Attach(hWnd);

		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 30, NULL);

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
		Rect rc;
		::GetClientRect(hWnd, &rc);

		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO.....
		HDC hMemDC = ::CreateCompatibleDC(hdc);
		HBITMAP hMemBitmap = ::CreateCompatibleBitmap(hdc, rc.width(), rc.height());
		HBITMAP hOldMemBitmap = ::Select(hMemDC, hMemBitmap);

		StarDepot.Draw(hMemDC);

		::BitBlt(hdc, 0, 0, rc.width(), rc.height(),
			hMemDC, 0, 0, SRCCOPY);

		::Select(hMemDC, hOldMemBitmap);
		::DeleteObject(hMemBitmap);
		::DeleteDC(hMemDC);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		// redraw
		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		Star* pStar = new Star;
		pStar->SetPosition(ptMouse);
		pStar->SetAngle(rand()%360);
		pStar->SetSpeed(rand()%15 + 15);

		StarDepot.push(pStar);

		StarDepot.Input(dt);
		StarDepot.Update(dt);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		// redraw
		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

