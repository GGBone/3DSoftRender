#include "LibApplicationPCH.h"
#include "WindowApplication.h"

#include "Dx11RenderData.h"

#include "Dx11Renderer.h"
#include "Renderer.h"


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

void Hikari::WindowApplication::GetMousePosition(int & x, int & y) const
{
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
	break;
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
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

