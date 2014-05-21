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

		RECT rc;
		::GetClientRect(hWnd, &rc);

		HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		HPEN hPen = ::CreatePen(PS_SOLID, 5, RGB(255,0,0));
		HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

		::Rectangle(hdc, rc.left+10, rc.top+10,
			rc.right-10, rc.bottom-10);

		::SelectObject(hdc, hOldPen);
		::DeleteObject(hPen);

		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}