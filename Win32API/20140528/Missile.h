#pragma once

#include <Windows.h>
#include "BaseType.h"

class Missile
{
public :
	Missile();
	~Missile();

public :
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void SetPosition(const Point& pt);
	void SetRadius(const LONG& r);
	void SetSpeed(const LONG& s);
	void SetAngle(const float& angle);

	Point GetPosition() const;
private :
	Point center;
	LONG radius;
	LONG speed;

	float theta;
};

class MissileManager
{
	enum { count = 100 };
private :
	MissileManager();
	~MissileManager();

public :
	static MissileManager& GetReference();

public :
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void push(Missile* pMissile);

private :
	Missile* depot[count];
};

#define MissileDepot MissileManager::GetReference()