#include "Effect.h"

EffectManager::EffectManager()
{
}
EffectManager::~EffectManager()
{
}

void EffectManager::Attach(HWND hWnd)
{
}

void EffectManager::Input(DWORD tick)
{
	std::list<Effect*>::iterator it;
	for (it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->Input(tick);
	}
}
void EffectManager::Update(DWORD tick)
{
}
void EffectManager::Draw(HDC hdc)
{
}

void EffectManager::push(Effect* pObj)
{
}
