#include "LibApplicationPCH.h"
#include "WindowApplicationBase.h"
#include "Renderer/RenderWindow.h"

using namespace Hikari;

WindowApplicationBase::WindowApplicationBase(const char* windowTile, int xPos,
                                             int yPos, int width, int height)
	:
	mWindowTitle(windowTile),
	mXPosition(xPos),
	mYPosition(yPos),
	mWidth(width),
	mHeight(height),
	mAllowResize(true),
	mWindowID(0),
	m_bIsInitialized(false),
	m_bIsRunning(false),
	m_windowName(""),
	m_bTerminateDirectoryChangeThread(false)

{
}

WindowApplicationBase::~WindowApplicationBase()
= default;

bool WindowApplicationBase::OnInitialize(EventArgs& e)
{
	if (m_bIsInitialized)
		return true;
	mInitialize(e);
	m_bIsInitialized = true;
	return m_bIsInitialized;
}

void WindowApplicationBase::OnTerminate(EventArgs& e)
{
	mTerminate(e);
	m_pRenderDevice.reset();
	m_bTerminateDirectoryChangeThread = true;
	if (m_DirectoryChangeListenerThread.joinable())
	{
		m_DirectoryChangeListenerThread.join();
	}
	for (auto window : m_Windows)
	{
		window.second.reset();
	}
	m_Windows.clear();
}

void WindowApplicationBase::OnExit(EventArgs& e)
{
	mExit(e);
	while (!gs_WindowHandleMap.empty())
	{
		DestroyWindow((*gs_WindowHandleMap.begin()).first);
	}
	m_bIsRunning = false;
}


void WindowApplicationBase::OnUserEvent(UserEventArgs& e)
{
	mUserEvent(e);
}

void WindowApplicationBase::Stop()
{
	PostQuitMessage(0);
}

void WindowApplicationBase::OnFileChange(FileChangeEventArgs& e)
{
	mFileChanged(e);
}

const std::shared_ptr<Renderer> WindowApplicationBase::GetRenderer()
{
	return m_pRenderDevice;
}

void WindowApplicationBase::CheckFileChange()
{
	while (!m_bTerminateDirectoryChangeThread)
	{
		MutexLock lock(m_DirectoryChangeMutex);
		DWORD waitSignal = WaitForSingleObject(m_DirectoryChanges.GetWaitHandle(), 0);
		switch (waitSignal)
		{
		case WAIT_OBJECT_0:
			if (m_DirectoryChanges.CheckOverflow())
			{
				ReportError("Directory change occured. ");
			}
			else
			{
				DWORD action;
				std::wstring fileName;
				m_DirectoryChanges.Pop(action, fileName);
				FileChangeEventArgs::FileAction fileAction = FileChangeEventArgs::FileAction::Unknown;
				switch (action)
				{
				case FILE_ACTION_ADDED:
					fileAction = FileChangeEventArgs::FileAction::Added;
					break;
				case FILE_ACTION_REMOVED:
					fileAction = FileChangeEventArgs::FileAction::Removed;
					break;
				case FILE_ACTION_MODIFIED:
					fileAction = FileChangeEventArgs::FileAction::Modified;
					break;
				case FILE_ACTION_RENAMED_OLD_NAME:
					fileAction = FileChangeEventArgs::FileAction::RenameOld;
					break;
				case FILE_ACTION_RENAMED_NEW_NAME:
					fileAction = FileChangeEventArgs::FileAction::RenameNew;
					break;
				default:
					break;
				}
				FileChangeEventArgs fileChangeEventArgs(*this, fileAction, fileName);
			}
		default:
			break;
		}
		lock.unlock();
		Sleep(100);
	}
	int i = 3;
}


void WindowApplicationBase::OnResize(int width, int height)
{
	for (auto window : m_Windows)
	{
		std::shared_ptr<RenderWindow> pWindow = window.second;
		ResizeEventArgs e(*pWindow, width, height);

		pWindow->OnResize(e);
	}
}

bool WindowApplicationBase::OnPrecreate(EventArgs& e)
{
	assert(0);
	return false;
}

void WindowApplicationBase::OnPreIdle(EventArgs& e)
{
	assert(0);
}

void WindowApplicationBase::OnUpdate(UpdateEventArgs& e)
{
	mUpdate(e);
}

void WindowApplicationBase::OnRender(RenderEventArgs& e)
{
	for (auto window : m_Windows)
	{
		std::shared_ptr<RenderWindow> pWindow = window.second;
		pWindow->OnPreRender(e);
		pWindow->OnRender(e);
		pWindow->OnPostRender(e);
	}
}

//
//void Hikari::WindowApplicationBase::OnMouseFocus(EventArgs & e)
//{
//	for (auto window : m_Windows)
//	{
//		std::shared_ptr<RenderWindow> pWindow = window.second;
//		pWindow->OnMouseFocus(e);
//	}
//}
//
//void Hikari::WindowApplicationBase::OnMouseLeave(EventArgs & e)
//{
//	for (auto window : m_Windows)
//	{
//		std::shared_ptr<RenderWindow> pWindow = window.second;
//		pWindow->OnMouseLeave(e);
//	}
//}
//
//void Hikari::WindowApplicationBase::OnMouseWheel(MouseWheelEventArgs & e)
//{
//	for (auto window : m_Windows)
//	{
//		std::shared_ptr<RenderWindow> pWindow = window.second;
//		pWindow->OnMouseWheel(e);
//	}
//}
//
//void Hikari::WindowApplicationBase::OnMouseBlur(EventArgs & e)
//{
//	assert(0);
//}
//
//void Hikari::WindowApplicationBase::OnMouseMoved(MouseMotionEventArgs & e)
//{
//	for (auto window : m_Windows)
//	{
//		std::shared_ptr<RenderWindow> pWindow = window.second;
//		pWindow->OnMouseMoved(e);
//	}
//}
//
//void Hikari::WindowApplicationBase::OnMouseButtonPressed(MouseButtonEventArgs & e)
//{
//	for (auto window : m_Windows)
//	{
//		std::shared_ptr<RenderWindow> pWindow = window.second;
//		pWindow->OnMouseButtonPressed(e);
//	}
//}
//
//void Hikari::WindowApplicationBase::OnMouseButtonReleased(MouseButtonEventArgs & e)
//{
//	for (auto window : m_Windows)
//	{
//		std::shared_ptr<RenderWindow> pWindow = window.second;
//		pWindow->OnMouseButtonReleased(e);
//	}
//}
//
//void Hikari::WindowApplicationBase::OnMotionMove(MouseMotionEventArgs & e)
//{
//	for (auto window : m_Windows)
//	{
//		std::shared_ptr<RenderWindow> pWindow = window.second;
//		pWindow->OnMouseMoved(e);
//	}
//}
//

void WindowApplicationBase::RegisterDirectojryChangeListener(const std::wstring& dir, bool recursive)
{
	MutexLock lock(m_DirectoryChangeMutex);
	m_DirectoryChanges.AddDictory(dir, recursive, FILE_NOTIFY_CHANGE_LAST_WRITE);
}


int WindowApplicationBase::Run(int numArgument, char** arguments)
{
	WindowApplicationBase* theApp = static_cast<WindowApplicationBase*>(TheApplication);

	return theApp->Main(numArgument, arguments);
}

void WindowApplicationBase::ResetTime()
{
	assert(0);
}

void WindowApplicationBase::MeasureTime()
{
	assert(0);
}

void WindowApplicationBase::UpdateFrameCount()
{
	assert(0);
}

void WindowApplicationBase::DrawFrameRate(int, int, const float& color)
{
	if (mAccumlatedTime > 0.0f)
	{
		mFrameRate = mAccumuulatedFrameCount / mAccumlatedTime;
	}
	else
		mFrameRate = 0.0f;

	char message[256];
	sprintf(message, "fps: %.llf", mFrameRate);
	//mRender
}
