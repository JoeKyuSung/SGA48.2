#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT ptHour;
	static POINT ptMinute;
	static POINT ptSecond;
	static LONG thetaHour = 0;
	static LONG thetaMinute = 0;
	static LONG thetaSecond = 0;

	static DWORD update_dt = 0;
	static DWORD update_delay = 1000;
	static DWORD start = 0;
	static bool bClock = false;
	static int nCount = 0;
	static COLORREF color = RGB(255,255,255);

	if (uMsg == WM_CREATE)
	{
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

		HBRUSH hBrush = ::CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		::Rectangle(hdc, 0, 0, 400, 400);
		::Ellipse(hdc, 0, 0, 400, 400);

		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);

		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptHour.x, ptHour.y);

		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptMinute.x, ptMinute.y);

		::MoveToEx(hdc, 200, 200, NULL);
		::LineTo(hdc, ptSecond.x, ptSecond.y);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		SYSTEMTIME st;
		
		//::GetSystemTime(&st);
		::GetLocalTime(&st);

		if (!bClock && st.wMinute == 0 && st.wSecond == 0)
		{
			color = RGB(255,0,0);
			bClock = true;
			nCount = (st.wHour%12 == 0)? 11 : st.wHour%12 - 1;
			start = ::GetTickCount();
			::SetTimer(hWnd, 1, 2000, NULL);
		}

		if (bClock)
		{

			if (update_dt > update_delay)
			{
				if (color == RGB(255,255,255))
					color = RGB(255,0,0);
				else
					color = RGB(255,255,255);

				update_dt -= update_delay;
			}

			update_dt += ::GetTickCount() - start;
			start = ::GetTickCount();
		}

		if (wParam == 0)
		{
			thetaHour = LONG((st.wHour%12)*30
						+ float(st.wMinute)/2 
						+ float(st.wSecond)/120
						+ float(st.wMilliseconds)/120000);

			thetaMinute = LONG(st.wMinute*6 
						+ float(st.wSecond)/10
						+ float(st.wMilliseconds)/10000);

			thetaSecond = LONG(st.wSecond*6
						+ float(st.wMilliseconds)*6/1000);

			LONG LHour = 80;
			LONG LMinute = 100;
			LONG LSecond = 150;

			const float D2R = float(M_PI/180);

			ptHour.x = LONG(200 + LHour*cos((90-thetaHour)*D2R));
			ptHour.y = LONG(200 - LHour*sin((90-thetaHour)*D2R));

			ptMinute.x = LONG(200 + LMinute*cos((90-thetaMinute)*D2R));
			ptMinute.y = LONG(200 - LMinute*sin((90-thetaMinute)*D2R));

			ptSecond.x = LONG(200 + LSecond*cos((90-thetaSecond)*D2R));
			ptSecond.y = LONG(200 - LSecond*sin((90-thetaSecond)*D2R));

			// redraw
			RECT rc;
			::GetClientRect(hWnd, &rc);
			::InvalidateRect(hWnd, &rc, TRUE);
		}
		else if (wParam == 1)
		{
			nCount--;
			if (nCount <= 0)
			{
				color = RGB(255,255,255);
				bClock = false;
				::KillTimer(hWnd, 1);
			}
		}

		return 0;
	}
	else if (uMsg == WM_SIZE)
	{
		DWORD dwStyle = WS_OVERLAPPEDWINDOW;
		dwStyle &= ~WS_MAXIMIZEBOX;
		dwStyle &= ~WS_THICKFRAME;
		RECT rc = {0,0,400,400};

		::AdjustWindowRect(&rc, dwStyle, FALSE);

		::SetWindowPos(hWnd, NULL, rc.left, rc.top,
			rc.right-rc.left, rc.bottom-rc.top, 
			SWP_NOZORDER | SWP_NOMOVE);
		//::SetWindowPlacement();
		//::MoveWindow();

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}