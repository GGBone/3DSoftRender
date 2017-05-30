#include "LibApplicationPCH.h"
#include "WindowApplication.h"

#include "Dx11RenderData.h"

#include "Dx11Renderer.h"
#include "Renderer.h"


using namespace Hikari;

const int WindowApplication::KEY_ESCAPE = VK_ESCAPE;
const int WindowApplication::KEY_LEFT_ARROW = VK_LEFT;
const int WindowApplication::KEY_RIGHT_ARROW = VK_RIGHT;
const int WindowApplication::KEY_UP_ARROW = VK_UP;
const int WindowApplication::KEY_DOWN_ARROW = VK_DOWN;
const int WindowApplication::KEY_HOME = VK_HOME;
const int WindowApplication::KEY_END = VK_END;
const int WindowApplication::KEY_PAGE_UP = VK_PRIOR;
const int WindowApplication::KEY_PAGE_DOWN = VK_NEXT;
const int WindowApplication::KEY_INSERT = VK_INSERT;
const int WindowApplication::KEY_DELETE = VK_DELETE;
const int WindowApplication::KEY_F1 = VK_F1;
const int WindowApplication::KEY_F2 = VK_F2;
const int WindowApplication::KEY_F3 = VK_F3;
const int WindowApplication::KEY_F4 = VK_F4;
const int WindowApplication::KEY_F5 = VK_F5;
const int WindowApplication::KEY_F6 = VK_F6;
const int WindowApplication::KEY_F7 = VK_F7;
const int WindowApplication::KEY_F8 = VK_F8;
const int WindowApplication::KEY_F9 = VK_F9;
const int WindowApplication::KEY_F10 = VK_F10;
const int WindowApplication::KEY_F11 = VK_F11;
const int WindowApplication::KEY_F12 = VK_F12;
const int WindowApplication::KEY_BACKSPACE = VK_BACK;
const int WindowApplication::KEY_TAB = VK_TAB;
const int WindowApplication::KEY_ENTER = VK_RETURN;
const int WindowApplication::KEY_RETURN = VK_RETURN;

const int WindowApplication::KEY_SHIFT = VK_SHIFT;
const int WindowApplication::KEY_CONTROL = VK_CONTROL;
const int WindowApplication::KEY_ALT = 0;      // not currently handled
const int WindowApplication::KEY_COMMAND = 0;  // not currently handled

const int WindowApplication::MOUSE_LEFT_BUTTON = 0;
const int WindowApplication::MOUSE_MIDDLE_BUTTON = 1;
const int WindowApplication::MOUSE_RIGHT_BUTTON = 2;
const int WindowApplication::MOUSE_UP = 0;
const int WindowApplication::MOUSE_DOWN = 1;

const int WindowApplication::MODIFIER_CONTROL = MK_CONTROL;
const int WindowApplication::MODIFIER_LBUTTON = MK_LBUTTON;
const int WindowApplication::MODIFIER_MBUTTON = MK_MBUTTON;
const int WindowApplication::MODIFIER_RBUTTON = MK_RBUTTON;
const int WindowApplication::MODIFIER_SHIFT = MK_SHIFT;

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

void Hikari::WindowApplication::GetMousePosition(int & x, int & y) const
{
	HWND handle = (HWND)IntToPtr(mWindowID);
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(handle, &point);
	x = (int)point.x;
	y = (int)point.y;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WindowApplication* theApp =
		(WindowApplication*)Application::TheApplication;
	if (!theApp || !theApp->GetWindowID())
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	switch (msg)
	{
	case WM_COMMAND:

		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		theApp->OnDisplay();
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_ERASEBKGND:
	{
		return 1;
	}
	case WM_MOVE:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		theApp->OnMove(xPos, yPos);
		return 0;
	}
	case WM_SIZE:
	{
		int width = (int)(LOWORD(lParam));
		int height = (int)(HIWORD(lParam));
		theApp->OnResize(width, height);
		return 0;
	}
	case WM_CHAR:
	{
		unsigned char key = (unsigned char)(char)wParam;
		if (key == theApp->KEY_TERMINATE)
		{
			PostQuitMessage(0);
			return 0;
		}
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hWnd, &point);
		int xPos = (int)point.x;
		int yPos = (int)point.y;
		theApp->OnKeyDown(key, xPos, yPos);
		return 0;
	}
	case WM_KEYDOWN:
	{
		int virtKey = int(wParam);

		// Get cursor position client coordinates.
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hWnd, &point);
		int xPos = (int)point.x;
		int yPos = (int)point.y;

		if ((VK_F1 <= virtKey && virtKey <= VK_F12)
			|| (VK_PRIOR <= virtKey && virtKey <= VK_DOWN)
			|| (virtKey == VK_INSERT) || (virtKey == VK_DELETE)
			|| (virtKey == VK_SHIFT) || (virtKey == VK_CONTROL))
		{
			theApp->OnSpecialKeyDown(virtKey, xPos, yPos);
		}
		return 0;
	}
	case WM_KEYUP:
	{
		int virtKey = (int)wParam;

		// get the cursor position in client coordinates
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hWnd, &point);
		int xPos = (int)point.x;
		int yPos = (int)point.y;

		if ((VK_F1 <= virtKey && virtKey <= VK_F12)
			|| (VK_PRIOR <= virtKey && virtKey <= VK_DOWN)
			|| (virtKey == VK_INSERT) || (virtKey == VK_DELETE)
			|| (virtKey == VK_SHIFT) || (virtKey == VK_CONTROL))
		{
			theApp->OnSpecialKeyUp(virtKey, xPos, yPos);
		}
		else
		{
			theApp->OnKeyUp((unsigned char)virtKey, xPos, yPos);
		}
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		theApp->OnMouseClick(WindowApplication::MOUSE_LEFT_BUTTON,
			WindowApplication::MOUSE_DOWN, xPos, yPos,
			(unsigned int)wParam);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		theApp->OnMouseClick(WindowApplication::MOUSE_LEFT_BUTTON,
			WindowApplication::MOUSE_UP, xPos, yPos,
			(unsigned int)wParam);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		theApp->OnMouseClick(WindowApplication::MOUSE_MIDDLE_BUTTON,
			WindowApplication::MOUSE_DOWN, xPos, yPos,
			(unsigned int)wParam);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		theApp->OnMouseClick(WindowApplication::MOUSE_MIDDLE_BUTTON,
			WindowApplication::MOUSE_UP, xPos, yPos,
			(unsigned int)wParam);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		theApp->OnMouseClick(WindowApplication::MOUSE_RIGHT_BUTTON,
			WindowApplication::MOUSE_DOWN, xPos, yPos,
			(unsigned int)wParam);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		theApp->OnMouseClick(WindowApplication::MOUSE_RIGHT_BUTTON,
			WindowApplication::MOUSE_UP, xPos, yPos,
			(unsigned int)wParam);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));

		int button = -1;
		if (wParam & MK_LBUTTON)
		{
			button = WindowApplication::MOUSE_LEFT_BUTTON;
		}
		else if (wParam & MK_MBUTTON)
		{
			button = WindowApplication::MOUSE_MIDDLE_BUTTON;
		}
		else if (wParam & MK_RBUTTON)
		{
			button = WindowApplication::MOUSE_RIGHT_BUTTON;
		}

		if (button >= 0)
		{
			theApp->OnMotion(button, xPos, yPos, (unsigned int)wParam);
		}
		else
		{
			theApp->OnPassiveMotion(xPos, yPos);
		}

		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		short sWParam = (short)(HIWORD(wParam));
		int delta = ((int)sWParam) / WHEEL_DELTA;
		int xPos = (int)(LOWORD(lParam));
		int yPos = (int)(HIWORD(lParam));
		unsigned int modifiers = (unsigned int)(LOWORD(wParam));
		theApp->OnMouseWheel(delta, xPos, yPos, modifiers);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(WM_QUIT);
		return 0;
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
int WindowApplication::Main(int, char**)
{
	WindowApplication* theApp = (WindowApplication*)TheApplication;


	WNDCLASSEX WndCls = { 0 };
	
	WndCls.cbSize = sizeof(WndCls);
	WndCls.style = CS_VREDRAW | CS_HREDRAW;
	WndCls.lpfnWndProc = WinProc;
	WndCls.hInstance = 0;
	WndCls.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndCls.cbClsExtra = 0;
	WndCls.cbWndExtra = 0;

	WndCls.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	WndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndCls.hIconSm = LoadIcon(0, IDI_APPLICATION);
	WndCls.lpszClassName = TEXT("Main");
	WndCls.lpszMenuName = NULL;
	if (!RegisterClassEx(&WndCls))
		return -1;
	DWORD dwStyle;
	if (mAllowResize)
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwStyle = WS_OVERLAPPED | WS_CAPTION;
	}
	RECT rect = {0,0,theApp->GetWidth(),theApp->GetHeight()};
	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, TEXT("MAIN"), TEXT("ZJ"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left,
		rect.bottom - rect.top, NULL, NULL, 0, NULL);
	theApp->SetWindowID(PtrToInt(hWnd));

	//Initialize By DX
	/*SoftRenderData inputData(theApp->GetWidth(), theApp->GetHeight(), 0, hWnd);
	mRenderer = new WinSoftRenderer(&inputData,hWnd);*/
	DirectRenderData inputData(theApp->GetWidth(), theApp->GetHeight(), 0, hWnd);

	mRenderer = new DirectRenderer(theApp->GetWidth(), theApp->GetHeight(),0, hWnd);

	if (theApp->OnInitialize())
	{
		MSG msg;
		theApp->OnPreidle();
		ShowWindow(hWnd, SW_SHOW);
		
		UpdateWindow(hWnd);
		
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				theApp->OnIdle();
		}
	}
	
	theApp->OnTerminate();
	
	return 0;
}

