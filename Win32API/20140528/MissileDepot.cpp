#include "Missile.h"

MissileManager::MissileManager()
{
	for (int i = 0; i < count; i++)
	{
		depot[i] = NULL;
	}
}
MissileManager::~MissileManager()
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
			delete depot[i];
	}
}

MissileManager& MissileManager::GetReference()
{
	static MissileManager instance;
	return instance;
}

void MissileManager::Input(DWORD tick)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
			depot[i]->Input(tick);
	}
}
void MissileManager::Update(DWORD tick)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
		{
			depot[i]->Update(tick);

			if (depot[i]->GetPosition().x < 0 ||
				depot[i]->GetPosition().y < 0 ||
				depot[i]->GetPosition().x > 800 ||
				depot[i]->GetPosition().y > 400)
			{
				delete depot[i];
				depot[i] = NULL;
			}
		}
	}
}
void MissileManager::Draw(HDC hdc)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
			depot[i]->Draw(hdc);
	}
}

void MissileManager::push(Missile* pMissile)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i] == NULL)
		{
			depot[i] = pMissile;
			break;
		}
	}
}
