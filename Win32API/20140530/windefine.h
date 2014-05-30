#pragma once

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <sstream> // wostringstream
#include "BaseType.h"
#include "Utility.hpp"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
Point follow(Point& dest, const Point& src);
