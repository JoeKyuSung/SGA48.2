#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;

	if (uMsg == WM_CREATE)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		ObjectDepot.Attach(hWnd);

      Tank* pTank = new Tank;
      pTank->SetPosition(Point(rc.width()/4, rc.center().y));
      pTank->SetKeyMapping(VK_LCONTROL, 'A','D','W','S');

      ObjectDepot.push(pTank);

      pTank = new Tank;
      pTank->SetPosition(Point(rc.width()*3/4, rc.center().y));
      pTank->SetKeyMapping(VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN);

      ObjectDepot.push(pTank);

      for (int i = 0; i < 4; i++)
      {
         Block* pBlock = new Block;
         pBlock->SetPosition(Point(rand()%rc.width(), rand()%rc.height()));
         pBlock->SetSize(40);

         ObjectDepot.push(pBlock);
      }

		st = ::GetTickCount();

		::SetTimer(hWnd, 0, 10, NULL);

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);

      // remove objects...
      ObjectDepot.clear();

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO
		RECT rc;
		::GetClientRect(hWnd, &rc);

      ObjectDepot.Draw(hdc);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		ObjectDepot.Input(dt);
		ObjectDepot.Update(dt);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		// redraw
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
