#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;

	static HBITMAP hStar = NULL;
	static Point ptMouse;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		hStar = (HBITMAP)::LoadImage(NULL, _T("star.bmp"),
			IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);

		ptMouse = Point(rc.center().x, 0);

		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 50, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);

		::DeleteObject(hStar);

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

		BITMAP bm;

		::GetObject(hStar, sizeof(BITMAP), &bm);
		int width = bm.bmWidth;
		int height = bm.bmHeight;

		// draw image...
		HDC hBitmapDC = ::CreateCompatibleDC(hdc);
		HBITMAP hOldStar = ::Select(hBitmapDC, hStar);

		::GdiTransparentBlt(hdc, ptMouse.x - width/2,
			ptMouse.y - height/2, width, height, 
			hBitmapDC, 0, 0,
			width, height,
			RGB(255,255,255));

		//::BitBlt(hdc, ptMouse.x - width/2,
		//	ptMouse.y - height/2, width, height, hBitmapDC, 0, 0, SRCCOPY);

		::Select(hBitmapDC, hOldStar);
		::DeleteDC(hBitmapDC);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		//::GetCursorPos(&ptMouse);
		//ptMouse = ptMouse.ToClient(hWnd);

		// redraw
		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		// TODO
		ptMouse.x += 5;
		ptMouse.y += 5;

		if (!::PtInRect(&rc, ptMouse))
		{
			ptMouse.x = rand()%rc.width();
			ptMouse.y = 0;
		}

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		// redraw
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

