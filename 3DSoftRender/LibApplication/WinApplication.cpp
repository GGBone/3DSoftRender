#include "LibApplicationPCH.h"
#include "WindowApplication.h"
#include <Windows.h>
#include <WinUser.h>

using namespace Hikari;

const int WindowApplication::KEY_ESCAPE = VK_ESCAPE;
//...

#ifndef MOUSE_WHEEL
#define MOUSE_WHEEL 0x020A
#endif

#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif

static bool gsIgnoreWindowDestroy = false;

void WindowApplication::SetMousePosition(int x, int y)
{
	HWND hand = (HWND)IntToPtr(mWindowID);
	POINT point;
	point.x = (LONG)x;
	point.y = (LONG)y;
	SetCursorPos(point.x, point.x);
	
}

