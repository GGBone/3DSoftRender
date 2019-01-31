#include "LibApplicationPCH.h"
#include "WindowApplicationBase.h"
#include "Renderer/DxRenderer/Dx11Renderer.h"
#include "Renderer/DxRenderer/Dx11RenderWindow.h"
#include "Renderer/ProgressWindow.h"
#define WINDOW_RENDER "Main"
#define WINDOW_PROCESS "Processing"


using namespace Hikari;

BOOL StringToWString(const std::string& str, std::wstring& wstr)
{
	int nLen = (int)str.length();
	wstr.resize(nLen, L' ');

	int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

	if (nResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL WStringToString(const std::wstring& wstr, std::string& str)
{
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');

	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, nullptr,
	                                  nullptr);

	if (nResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}

std::string ConvertString(const std::wstring& wstring)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convertor;
	return convertor.to_bytes(wstring);
}

void ReportErrorAndThrow(const std::string& file, int line, const std::string& function, const std::string& message)
{
	std::stringstream ss;
	DWORD errorCode = GetLastError();
	LPSTR errorMessage = nullptr;
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
	               nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errorMessage, 0, nullptr);
	if (errorMessage)
	{
		ss << file << "(" << line << "): " << "error " << errorCode << ": " << errorMessage << std::endl;
		LocalFree(errorMessage);
	}
	else
		ss << file << "(" << line << "): " << message << std::endl;

	OutputDebugStringA(ss.str().c_str());
	MessageBoxA(nullptr, message.c_str(), function.c_str(), MB_ICONERROR);

	throw new std::exception(message.c_str());
}

//static bool gsIgnoreWindowDestroy = false;
//typedef std::map<HWND, std::shared_ptr<RenderWindow>> WindowHandleMap;
//static WindowHandleMap gs_WindowHandleMap;
//static float g_GameDeltaTime = 0.0f;
//static float g_AppcationTime = 0.0f;
//int64_t g_FrameCounter = 0L;

static MouseButtonEventArgs::MouseButton DecodeMouseButton(UINT messageID)
{
	MouseButtonEventArgs::MouseButton mouseButton = MouseButtonEventArgs::None;
	switch (messageID)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		{
			mouseButton = MouseButtonEventArgs::Left;
		}
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		{
			mouseButton = MouseButtonEventArgs::Right;
		}
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
		{
			mouseButton = MouseButtonEventArgs::Middel;
		}
		break;
	}

	return mouseButton;
}

void WindowApplicationBase::SetMousePosition(int x, int y)
{
	HWND hand = (HWND)IntToPtr(mWindowID);
	POINT point;
	point.x = (LONG)x;
	point.y = (LONG)y;
	SetCursorPos(point.x, point.x);
}

void WindowApplicationBase::GetMousePosition(int& x, int& y) const
{
	HWND handle = (HWND)IntToPtr(mWindowID);
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(handle, &point);
	x = (int)point.x;
	y = (int)point.y;
}

namespace Hikari
{
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		std::shared_ptr<RenderWindow> pWindow = nullptr;
		WindowHandleMap::iterator iter = gs_WindowHandleMap.find(hWnd);
		if (iter != gs_WindowHandleMap.end())
		{
			pWindow = iter->second;
		}
		if (pWindow != nullptr)
		{
			switch (msg)
			{
			case WM_PAINT:
				{
					PAINTSTRUCT ps;
					BeginPaint(hWnd, &ps);

					EndPaint(hWnd, &ps);
				}
				break;

			case WM_SIZE:
				{
					int width = (int)(LOWORD(lParam));
					int height = (int)(HIWORD(lParam));
					ResizeEventArgs resizeEventArgs(*pWindow, width, height);
					pWindow->OnResize(resizeEventArgs);
				}
				break;
			case WM_CHAR:
				{
					unsigned char key = (unsigned char)(char)wParam;

					POINT point;
					GetCursorPos(&point);
					ScreenToClient(hWnd, &point);
					int xPos = (int)point.x;
					int yPos = (int)point.y;
					return 0;
				}
			case WM_KEYDOWN:
				{
					MSG charMsg;
					unsigned int c = 0;
					if (PeekMessage(&charMsg, hWnd, 0, 0, PM_NOREMOVE) && charMsg.message == WM_CHAR)
					{
						GetMessage(&charMsg, hWnd, 0, 0);
						c = static_cast<UINT>(charMsg.wParam);
					}
					bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
					bool control = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;

					bool alt = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;

					KeyCode key = (KeyCode)wParam;

					unsigned int scanCode = (lParam & 0x00FF0000) >> 16;
					KeyEventArgs keyEvents(*pWindow, key, c, KeyEventArgs::Pressed, control, shift, alt);
					pWindow->OnKeyPressed(keyEvents);
				}
				break;
			case WM_KEYUP:
				{
				}
				break;
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
				{
					bool lButton = (wParam & MK_LBUTTON) != 0;
					bool mButton = (wParam & MK_MBUTTON) != 0;
					bool rButton = (wParam & MK_RBUTTON) != 0;
					bool shift = (wParam & MK_SHIFT) != 0;
					bool control = (wParam & MK_CONTROL) != 0;
					int xPos = (int)(LOWORD(lParam));
					int yPos = (int)(HIWORD(lParam));
					MouseButtonEventArgs mouseButtonEventArgs(*pWindow, hWnd, DecodeMouseButton(msg),
					                                          MouseButtonEventArgs::Pressed, lButton, mButton, rButton,
					                                          control, shift, xPos, yPos);
					pWindow->OnMouseButtonPressed(mouseButtonEventArgs);
					return 0;
				}
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
				{
					bool lButton = (wParam & MK_LBUTTON) != 0;
					bool mButton = (wParam & MK_MBUTTON) != 0;
					bool rButton = (wParam & MK_RBUTTON) != 0;
					bool shift = (wParam & MK_SHIFT) != 0;
					bool control = (wParam & MK_CONTROL) != 0;
					int xPos = (int)(LOWORD(lParam));
					int yPos = (int)(HIWORD(lParam));
					MouseButtonEventArgs mouseButtonEventArgs(*pWindow, hWnd, DecodeMouseButton(msg),
					                                          MouseButtonEventArgs::Released, lButton, mButton, rButton,
					                                          control, shift, xPos, yPos);
					pWindow->OnMouseButtonReleased(mouseButtonEventArgs);


					return 0;
				}

			case WM_MOUSEMOVE:
				{
					bool lButton = (wParam & MK_LBUTTON) != 0;
					bool rButton = (wParam & MK_RBUTTON) != 0;
					bool mButtom = (wParam & MK_MBUTTON) != 0;
					bool shift = (wParam & MK_SHIFT) != 0;
					bool control = (wParam & MK_CONTROL) != 0;

					int xPos = (int)(LOWORD(lParam));
					int yPos = (int)(HIWORD(lParam));

					MouseMotionEventArgs mouseMotionEventArgs(*pWindow, lButton, mButtom, rButton, control, shift, xPos,
					                                          yPos);
					pWindow->OnMouseMoved(mouseMotionEventArgs);

					return 0;
				}
			case WM_MOUSEWHEEL:
				{
					short sWParam = (short)(HIWORD(wParam));
					float delta = ((int)sWParam) / (float)WHEEL_DELTA;

					short keyStates = (short)(LOWORD(wParam));

					bool lButton = (keyStates & MK_LBUTTON) != 0;
					bool rButton = (keyStates & MK_RBUTTON) != 0;
					bool mButton = (keyStates & MK_MBUTTON) != 0;
					bool shift = (keyStates & MK_SHIFT) != 0;
					bool control = (keyStates & MK_CONTROL) != 0;

					int xPos = (int)(LOWORD(lParam));
					int yPos = (int)(HIWORD(lParam));

					POINT clientToScreenPoint;
					clientToScreenPoint.x = xPos;
					clientToScreenPoint.y = yPos;
					ScreenToClient(hWnd, &clientToScreenPoint);
					MouseWheelEventArgs mouseWheelEventArgs(*pWindow, delta, lButton, mButton, rButton, control, shift,
					                                        (int)clientToScreenPoint.x, (int)clientToScreenPoint.y);

					pWindow->OnMouseWheel(mouseWheelEventArgs);
					return 0;
				}
				break;
			case WM_CLOSE:
				{
					WindowCloseEventArgs windowCloseEvent(*pWindow);
					pWindow->OnClose(windowCloseEvent);
					if (windowCloseEvent.ConfirmClose)

					{
						ShowWindow(hWnd, SW_HIDE);
					}
				}
				break;
			case WM_DESTROY:
				{
					WindowHandleMap::iterator iter = gs_WindowHandleMap.find(hWnd);
					if (iter != gs_WindowHandleMap.end())
					{
						gs_WindowHandleMap.erase(iter);
					}
				}
				break;
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
				break;
			}
		}
		else
		{
			switch (msg)
			{
			case WM_CREATE:
				break;
			default:
				{
					return DefWindowProc(hWnd, msg, wParam, lParam);
				}
				break;
			}
		}
		return 0;
	}

	static void FreeImageErrorHandle(FREE_IMAGE_FORMAT fif, const char* message)
	{
		ReportError(message);
	}
}

int WindowApplicationBase::Main(int, char**)
{
	WindowApplicationBase* theApp = (WindowApplicationBase*)TheApplication;

	Assimp::Logger::LogSeverity logServity = Assimp::Logger::NORMAL;
	unsigned int logStreams = aiDefaultLogStream_FILE;
#if _DEBUG
	logServity = Assimp::Logger::VERBOSE;
	logStreams |= aiDefaultLogStream_DEBUGGER | aiDefaultLogStream_STDOUT;
#endif
	Assimp::DefaultLogger::create("assimp.log", logServity, logStreams);
	FreeImage_Initialise();
	FreeImage_SetOutputMessage(FreeImageErrorHandle);

	m_hInstance = ::GetModuleHandle(nullptr);

	WNDCLASSEX WndCls = {0};

	WndCls.cbSize = sizeof(WndCls);
	WndCls.style = CS_VREDRAW | CS_HREDRAW;
	WndCls.lpfnWndProc = WinProc;
	WndCls.hInstance = m_hInstance;
	WndCls.hCursor = LoadCursor(m_hInstance, IDC_ARROW);
	WndCls.cbClsExtra = 0;
	WndCls.cbWndExtra = 0;

	WndCls.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);

	WndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndCls.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);
	WndCls.lpszClassName = TEXT(WINDOW_RENDER);
	WndCls.lpszMenuName = nullptr;
	if (!RegisterClassEx(&WndCls))
	{
		ReportError("Failed to register main render windows");
		return -1;
	}

	WNDCLASSEX proceWnd = {0};

	proceWnd.cbSize = sizeof(WndCls);
	proceWnd.style = CS_VREDRAW | CS_HREDRAW;
	proceWnd.lpfnWndProc = WinProc;
	proceWnd.hInstance = m_hInstance;
	proceWnd.hCursor = LoadCursor(m_hInstance, IDC_ARROW);
	proceWnd.cbClsExtra = 0;
	proceWnd.cbWndExtra = 0;

	proceWnd.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);

	proceWnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	proceWnd.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);
	proceWnd.lpszClassName = TEXT(WINDOW_PROCESS);
	proceWnd.lpszMenuName = nullptr;
	if (!RegisterClassEx(&proceWnd))
	{
		ReportError("Failed to register process render windows");
		return -1;
	}

	m_pRenderDevice = std::make_shared<DirectRenderer>(*this);
	//m_DirectoryChangeListenerThread = std::thread(&WindowApplicationBase::CheckFileChange,this);

	CreateRenderWindow("Render", mWidth, mHeight);
	CreateProgressWindow("Progress", 256, 40);
	mProgressWindow->SetTotalProgress(6.f);
	mProgressWindow->ShowWindow();

	m_pRenderDevice->mLoadingProgress += boost::bind(&ProgressWindow::UpdateProgress, mProgressWindow.get(), _1);
	Timer elapseTime;
	OnInitialize(EventArgs(*this));
	m_bIsRunning = true;
	MSG msg;
	while (m_bIsRunning)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				EventArgs args(*this);
				OnExit(args);
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		{
			g_GameDeltaTime = elapseTime.GetElapsedTime();
			g_AppcationTime += g_GameDeltaTime;
			++g_FrameCounter;
			UpdateEventArgs updateArgs(*this, g_GameDeltaTime, g_AppcationTime);
			OnUpdate(updateArgs);
			RenderEventArgs renderArgs(*this, g_GameDeltaTime, g_AppcationTime, g_FrameCounter);
			OnRender(renderArgs);
		}
	}
	OnTerminate(EventArgs(*this));
	return static_cast<int>(msg.wParam);
}

void WindowApplicationBase::CreateRenderWindow(const std::string& title, int width, int height)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CXSCREEN);
	RECT rect = {0, 0, screenWidth, screenHeight};

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	int windowX = (screenWidth - mWidth) / 2;
	int windowY = (screenHeight - mHeight) / 2;

	HWND hWnd = CreateWindowExA(NULL, (WINDOW_RENDER), title.c_str(),
	                            WS_OVERLAPPEDWINDOW | WS_VISIBLE, windowX, windowY, mWidth,
	                            mHeight, nullptr, nullptr, m_hInstance, nullptr);
	if (!hWnd)
	{
		ReportError("Failed to create render window");
	}

	//Create RenderWindows
	m_windowName = "Render Window";
	mRenderWindow = std::make_shared<Dx11RenderWindow>(*this, hWnd,
	                                                   std::dynamic_pointer_cast<DirectRenderer>(
		                                                   std::shared_ptr<Renderer>(m_pRenderDevice)), m_windowName,
	                                                   mWidth, mHeight);


	m_Windows.insert(WindowMap::value_type(m_windowName, mRenderWindow));
	gs_WindowHandleMap.insert(WindowHandleMap::value_type(hWnd, mRenderWindow));

	if (m_bIsInitialized)
	{
		EventArgs eventArgs(*this);
		mRenderWindow->OnInitialize(eventArgs);
	}
	UpdateWindow(hWnd);
}

void WindowApplicationBase::CreateProgressWindow(const std::string& title, int width, int height)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CXSCREEN);
	RECT rect = {0, 0, width, height};

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	int windowX = (screenWidth - width) / 2;
	int windowY = (screenHeight - height) / 2;

	HWND hWnd = CreateWindowExA(NULL, (WINDOW_PROCESS), title.c_str(),
	                            WS_OVERLAPPEDWINDOW | WS_VISIBLE, windowX, windowY, width,
	                            height, nullptr, nullptr, m_hInstance, nullptr);
	if (!hWnd)
	{
		ReportError("Failed to create process window");
	}

	mProgressWindow = std::make_shared<ProgressWindow>(*this, title, hWnd, width, height);

	m_Windows.insert(WindowMap::value_type(title, mProgressWindow));
	gs_WindowHandleMap.insert(WindowHandleMap::value_type(hWnd, mProgressWindow));
	UpdateWindow(hWnd);
}
