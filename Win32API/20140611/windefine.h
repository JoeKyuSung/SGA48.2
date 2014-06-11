#pragma once

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <list>
#include <sstream> // wostringstream
#include <iomanip> // setw, setfill
#include "BaseType.h"
#include "Utility.hpp"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

void DrawCard(HDC hdc, 
			  std::list<HBITMAP>& cardlist, 
			  const Rect& rcBox, 
			  const int& idx, 
			  const int& current,
			  const BYTE& alpha);
