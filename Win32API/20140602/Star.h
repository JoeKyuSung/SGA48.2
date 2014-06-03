#pragma once

#include <Windows.h>
#include <tchar.h>
#include "BaseType.h"
#include "Utility.hpp"

class Star
{
public :
	Star();
	~Star();

public :
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void SetPosition(const Point& );
	void SetAngle(const LONG& );
	void SetSpeed(const LONG& );

	Point GetPosition() const;

private :
	Point center;
	LONG theta;
	LONG speed;

	int size;
};

class StarManager : public singleton<StarManager>
{
	friend class singleton<StarManager>;
	enum { count = 100 };
private :
	StarManager();
	~StarManager();

public :
	void Attach(HWND);

	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void push(Star* );
	void pop(const int& );

private :
	HWND hOwner;
	Star* depot[count];
};

#define StarDepot StarManager::GetReference()