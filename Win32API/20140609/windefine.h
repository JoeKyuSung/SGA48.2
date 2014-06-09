#pragma once

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <sstream> // wostringstream
#include "BaseType.h"
#include "Utility.hpp"

enum mouse_state_id
{
	MS_NORMAL,
	MS_UP,
	MS_DOWN,
	MS_LEFT,
	MS_RIGHT,
	MS_MAX
};

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
