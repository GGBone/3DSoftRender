#include "LibApplicationPCH.h"
#include "WindowApplication.h"
using namespace Hikari;
WindowApplication::WindowApplication(const char * windowTile, int xPos,
	int yPos, int width, int height, const Float4& clearColor)
	:
	mWindowTitle(windowTile),
	mXPosition(xPos),
	mYPosition(yPos),
	mWidth(width),
	mHeight(height),
	mClearColor(),
	mAllowResize(true),
	mWindowID(0)
	
{
}

Hikari::WindowApplication::~WindowApplication()
{
}

inline bool Hikari::WindowApplication::OnPrecreate()
{
	return true;
}

inline void Hikari::WindowApplication::OnPreidle()
{
	//mRender->ClearBuffer
}

inline void Hikari::WindowApplication::OnDisplay()
{
}

inline void Hikari::WindowApplication::OnIdle()
{
}

bool Hikari::WindowApplication::OnKeyDown(unsigned char key, int x, int y)
{
	return false;
}

inline bool Hikari::WindowApplication::OnKeyUp(unsigned char key, int x, int y)
{
	return false;
}

inline bool Hikari::WindowApplication::OnSpecialKeyDown(int key, int x, int y)
{
	return false;
}

inline bool Hikari::WindowApplication::OnSpecialKeyUp(int key, int x, int y)
{
	return false;
}

inline bool Hikari::WindowApplication::OnMouseClick(int button, int state, int x, int y, unsigned int modifiers)
{
	return false;
}

inline bool Hikari::WindowApplication::OnMotion(int button, int x, int y, unsigned int modifiers)
{
	return false;
}

inline bool Hikari::WindowApplication::OnPassiveMotion(int,int)
{
	return false;
}

inline bool Hikari::WindowApplication::OnMouseWheel(int button, int x, int y, unsigned int modifiers)
{
	return false;
}
inline bool Hikari::WindowApplication::OnInitialize()
{
	mRenderer->SetClearColor(mClearColor);
	return true;
}

void Hikari::WindowApplication::OnTerminate()
{
}

void Hikari::WindowApplication::OnMove(int x, int y)
{
}

void Hikari::WindowApplication::OnResize(int windth, int height)
{
}

int Hikari::WindowApplication::Run(int numArgument, char ** arguments)
{
	WindowApplication *theApp = static_cast<WindowApplication*>(TheApplication);

	return theApp->Main(numArgument,arguments);
}

void Hikari::WindowApplication::ResetTime()
{
}

void Hikari::WindowApplication::MeasureTime()
{
}

void Hikari::WindowApplication::UpdateFrameCount()
{
}

void Hikari::WindowApplication::DrawFrameRate(int, int, const float & color)
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
