#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int count = 100;
	static POINT pt[count];
	const LONG radius = 30;

	if (uMsg == WM_CREATE)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InflateRect(&rc, -radius, -radius);

		LONG cx = rc.right - rc.left;
		LONG cy = rc.bottom - rc.top;

		for (int i = 0; i < count; i++)
		{
			pt[i].x = rand()%cx + radius;
			pt[i].y = rand()%cy + radius;
		}

		pt[0].x = (rc.left + rc.right)/2;

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
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
		LONG a = (rc.left + rc.right)/2;

		for (int i = 0; i < count; i++)
		{
			if (a > pt[i].x)
			{
				HBRUSH hBrush = ::CreateSolidBrush(RGB(255,0,0));
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

				HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(255,120,120));
				HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

				::Ellipse(hdc, pt[i].x - radius,
								pt[i].y - radius,
								pt[i].x + radius,
								pt[i].y + radius);

				::SelectObject(hdc, hOldPen);
				::DeleteObject(hPen);

				::SelectObject(hdc, hOldBrush);
				::DeleteObject(hBrush);
			}
			else if (a == pt[i].x)
			{
				HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

				HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(120,120,255));
				HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

				::Rectangle(hdc, pt[i].x - radius,
								pt[i].y - radius,
								pt[i].x + radius,
								pt[i].y + radius);

				::SelectObject(hdc, hOldPen);
				::DeleteObject(hPen);

				::SelectObject(hdc, hOldBrush);
				::DeleteObject(hBrush);

				hBrush = ::CreateSolidBrush(RGB(255,0,0));
				hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

				hPen = ::CreatePen(PS_SOLID, 1, RGB(255,120,120));
				hOldPen = (HPEN)::SelectObject(hdc, hPen);

				::Ellipse(hdc, pt[i].x - radius,
								pt[i].y - radius,
								pt[i].x + radius,
								pt[i].y + radius);

				::SelectObject(hdc, hOldPen);
				::DeleteObject(hPen);

				::SelectObject(hdc, hOldBrush);
				::DeleteObject(hBrush);

			}
			else
			{
				HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

				HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(120,120,255));
				HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

				::Rectangle(hdc, pt[i].x - radius,
								pt[i].y - radius,
								pt[i].x + radius,
								pt[i].y + radius);

				::SelectObject(hdc, hOldPen);
				::DeleteObject(hPen);

				::SelectObject(hdc, hOldBrush);
				::DeleteObject(hBrush);
			}

		}

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}