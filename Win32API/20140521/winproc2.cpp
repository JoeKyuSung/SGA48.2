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

		BYTE r = rand()%256;
		BYTE g = rand()%256;
		BYTE b = rand()%256;

		COLORREF color = RGB(r,g,b);

		RECT rc;
		::GetClientRect(hWnd, &rc);

		const LONG size = 100;
		POINT center = {(rc.left + rc.right)/2,
						(rc.top + rc.bottom)/2};

		HBRUSH hBrush = ::CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		HPEN hPen = ::CreatePen(PS_SOLID, 5, color);
		HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

		::Rectangle(hdc, center.x - size/2, center.y - size/2,
			center.x + size/2, center.y + size/2);

		::SelectObject(hdc, hOldPen);
		::DeleteObject(hPen);

		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}