#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int radius = 20;
	const int count = 50;
	static Circle marble[count];
	static Point ptMouse;

	if (uMsg == WM_CREATE)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		LONG width = rc.right - rc.left;
		LONG height = rc.bottom - rc.top;

		for (int  i = 0; i < count; i ++)
		{
			marble[i].Attach(hWnd);
			marble[i].SetRadius(radius);
			marble[i].SetCenter(Point(rand()%width, rand()%(height-2*radius) + radius));
			marble[i].SetColor(RGB(rand()%256,rand()%256,rand()%256));
			marble[i].SetSpeed(rand()%30 + 10);
		}

		::SetTimer(hWnd, 0, 100, NULL);

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

		for (int i = 0; i < count; i++)
		{
			marble[i].Draw(hdc);
		}

		//TCHAR szText[10];
		//_stprintf(szText, _T("%d,%d"), ptMouse.x, ptMouse.y);

		std::wostringstream oss;
		oss << ptMouse.x << _T(", ") << ptMouse.y;

		::DrawText(hdc, oss.str().c_str(), -1, &rc, DT_TOP);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		for (int i = 0; i < count; i++)
		{
			marble[i].Update();
		}

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		ptMouse.x = GET_X_LPARAM(lParam);
		ptMouse.y = GET_Y_LPARAM(lParam);

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}