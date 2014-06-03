#include "Star.h"

StarManager::StarManager()
: hOwner(NULL)
{
	for (int i = 0; i < count; i++)
	{
		depot[i] = NULL;
	}
}
StarManager::~StarManager()
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
		{
			delete depot[i];
			depot[i] = NULL;
		}
	}
}
void StarManager::Attach(HWND hWnd)
{
	hOwner = hWnd;
}
void StarManager::Input(DWORD tick)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
		{
			depot[i]->Input(tick);
		}
	}
}
void StarManager::Update(DWORD tick)
{
	Rect rc;
	::GetClientRect(hOwner, &rc);

	for (int i = 0; i < count; i++)
	{
		if (depot[i])
		{
			depot[i]->Update(tick);

			Point pt = depot[i]->GetPosition();

			if (!::PtInRect(&rc, pt))
			{
				pop(i);
			}
		}
	}
}
void StarManager::Draw(HDC hdc)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
		{
			depot[i]->Draw(hdc);
		}
	}
}

void StarManager::push(Star* obj)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i] == NULL)
		{
			depot[i] = obj;
			break;
		}
	}
}
void StarManager::pop(const int& i)
{
	if (depot[i])
	{
		delete depot[i];
		depot[i] = NULL;
	}
}

