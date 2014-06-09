#pragma once

#include "BaseType.h"
#include "Utility.hpp"

class Effect
{
public :
	Effect();
	~Effect();

	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void SetPosition(const Point& );
	void SetRadius(const float& );
	void SetAngle(const LONG& );
	void SetSpeed(const LONG& );

	Point GetPosition() const;
	float GetRadius() const;

private :
	Point center;
	float radius;
	LONG theta;
	LONG speed;
};

#include <list>

class EffectManager : public singleton<EffectManager>
{
	friend class singleton<EffectManager>;
	//typedef std::list<Effect*> EffectList;
	//typedef std::list<Effect*>::iterator EffectIter;
private :
	EffectManager();
	~EffectManager();

public :
	void Attach(HWND);

	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void push(Effect* );

private :
	HWND hOwner;
	std::list<Effect*> depot;
};

#define EffectDepot EffectManager::GetReference()