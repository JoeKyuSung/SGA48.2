#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int radius = 20;
	const int count = 50;
	static Circle marble[count];
	static Point ptMouse;
	static Point ptEnd;
	static LONG theta = 0;

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
			marble[i].SetCenter(Point(rand()%width, rand()%(height-radius-150) + radius));
			marble[i].SetColor(RGB(rand()%156 + 100,rand()%156 + 100,rand()%156 + 100));
			marble[i].SetSpeed(rand()%20 + 5);
		}

		ptEnd = Point(rc.left + width/2, rc.top + height - 120);

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
		LONG width = rc.right - rc.left;
		LONG height = rc.bottom - rc.top;

		for (int i = 0; i < count; i++)
		{
			marble[i].Draw(hdc);
		}

		Point pt(rc.left + width/2, rc.top + height);

		::Ellipse(hdc, pt.x - 100, pt.y - 100,
			pt.x + 100, pt.y + 100);

		::MoveToEx(hdc, pt.x, pt.y, NULL);
		::LineTo(hdc, ptEnd.x, ptEnd.y);

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

		for (int i = 0; i < count; i++)
		{
			marble[i].Input(ptMouse);
		}

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_KEYDOWN)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		LONG width = rc.right - rc.left;
		LONG height = rc.bottom - rc.top;

		if (wParam == VK_LEFT)
		{
			theta -= 5;
			if (theta < -80)
			{
				theta = -80;
			}
		}
		else if (wParam == VK_RIGHT)
		{
			theta += 5;
			if (theta > 80)
			{
				theta = 80;
			}
		}

		Point cp(rc.left + width/2, rc.top + height);
		LONG L = 120;
		const float D2R = float(M_PI/180);

		LONG dx = LONG(L * cos((90 - theta)*D2R));
		LONG dy = LONG(L * sin((90 - theta)*D2R));

		ptEnd.x = cp.x + dx;
		ptEnd.y = cp.y - dy;

		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_KEYUP)
	{
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}