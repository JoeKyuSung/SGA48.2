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

		HBRUSH hBrush = ::CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		HPEN hPen = ::CreatePen(PS_SOLID, 5, color);
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