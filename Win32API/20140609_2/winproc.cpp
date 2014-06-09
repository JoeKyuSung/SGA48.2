#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;

	static Point ptMouse;

	static int stateMouse = MS_NORMAL;

	static LONG x[MS_MAX] = {0,50,100,150,200};

	static HBITMAP hCursor = NULL;

	static bool bClipCursor = true;

	// memory DC
	static HDC hMainDC = NULL;
	static HDC hMemDC = NULL;
	static HBITMAP hMemBitmap = NULL;
	static HBITMAP hOldMemBitmap = NULL;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		hMainDC = ::GetDC(hWnd);
		hMemDC = ::CreateCompatibleDC(hMainDC);
		hMemBitmap = ::CreateCompatibleBitmap(hMainDC, rc.width(), rc.height());
		hOldMemBitmap = ::Select(hMemDC, hMemBitmap);

		hCursor = (HBITMAP)::LoadImage(NULL, _T("cursor.bmp"), IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

		st = ::GetTickCount();
		//::SetTimer(hWnd, 0, 30, NULL);

		Point c = rc.center().ToScreen(hWnd);
		::SetCursorPos(c.x, c.y);

		::ShowCursor(FALSE);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		if (hCursor)
			::DeleteObject(hCursor);

		::Select(hMemDC, hOldMemBitmap);
		::DeleteObject(hMemBitmap);
		::DeleteDC(hMemDC);
		::ReleaseDC(hWnd, hMainDC);

		//::KillTimer(hWnd, 0);

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
		::SetDCBrushColor(hMemDC, RGB(200,255,200));
		::FillRect(hMemDC, &rc, (HBRUSH)::GetStockObject(DC_BRUSH));

		HDC hBitmapDC = ::CreateCompatibleDC(hdc);
		HBITMAP hOldBitmap = ::Select(hBitmapDC, hCursor);

		::GdiTransparentBlt(hMemDC, ptMouse.x - 25, ptMouse.y - 25, 50, 50,
			hBitmapDC, x[stateMouse], 0, 50, 50, RGB(255,255,255));

		::Select(hBitmapDC, hOldBitmap);
		::DeleteDC(hBitmapDC);

		::BitBlt(hdc, 0, 0, rc.width(), rc.height(),
			hMemDC, 0, 0, SRCCOPY);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		if (bClipCursor)
		{
			::GetCursorPos(&ptMouse);
			ptMouse = ptMouse.ToClient(hWnd);

			const LONG margin = 10;

			if (ptMouse.y < rc.top + margin)
			{
				stateMouse = MS_UP;
			}
			else if (ptMouse.y > rc.bottom - margin)
			{
				stateMouse = MS_DOWN;
			}
			else if (ptMouse.x < rc.left + margin)
			{
				stateMouse = MS_LEFT;
			}
			else if (ptMouse.x > rc.right - margin)
			{
				stateMouse = MS_RIGHT;
			}
			else
			{
				stateMouse = MS_NORMAL;
			}
		}

		// redraw
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_KEYDOWN)
	{
		if ((::GetAsyncKeyState(VK_ESCAPE) & 0x8000) == 0x8000)
		{
			if (bClipCursor)
			{
				::ClipCursor(NULL);

				::ShowCursor(TRUE);
			}
			else
			{
				Rect rc;
				::GetClientRect(hWnd, &rc);
				::ClipCursor(&rc.ToScreen(hWnd));

				::ShowCursor(FALSE);
			}

			bClipCursor = !bClipCursor;
		}

		return 0;
	}
	//else if (uMsg == WM_TIMER)
	//{
	//	// TODO

	//	dt = ::GetTickCount() - st;
	//	st = ::GetTickCount();

	//	// redraw
	//	Rect rc;
	//	::GetClientRect(hWnd, &rc);
	//	::InvalidateRect(hWnd, &rc, TRUE);

	//	return 0;
	//}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

