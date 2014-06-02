#pragma once

#include <windows.h>

template<typename GDIObject>
GDIObject Select(HDC hdc, GDIObject obj)
{
	return (GDIObject)::SelectObject(hdc, obj);
}