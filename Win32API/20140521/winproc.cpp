#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		// SendMessage
		// PostMessage
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

		::Rectangle(hdc, rc.left + 10, rc.top + 10,
			rc.right - 10, rc.bottom - 10);

		::Ellipse(hdc, rc.left + 10, rc.top + 10,
			rc.right - 10, rc.bottom - 10);

		::MoveToEx(hdc, rc.left, rc.top, NULL);
		::LineTo(hdc, rc.right/2, rc.bottom/2);
		::LineTo(hdc, rc.right, rc.top);

		::SetBkMode(hdc, TRANSPARENT);

		::DrawText(hdc, _T("hello Win32 HELL"), -1,
			&rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//::MoveToEx(hdc, rc.left, rc.top, NULL);
		//::LineTo(hdc, rc.right, rc.bottom);
		//::MoveToEx(hdc, rc.right, rc.top, NULL);
		//::LineTo(hdc, rc.left, rc.bottom);

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}