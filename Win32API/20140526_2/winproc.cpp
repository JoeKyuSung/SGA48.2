#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT ptHour;
	static POINT ptMinute;
	static POINT ptSecond;
	static LONG thetaHour = 0;
	static LONG thetaMinute = 0;
	static LONG thetaSecond = 0;

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

		::Rectangle(hdc, 0, 0, 400, 400);
		::Ellipse(hdc, 0, 0, 400, 400);

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

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}