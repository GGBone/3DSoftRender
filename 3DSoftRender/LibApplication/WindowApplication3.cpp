
#include "LibApplicationPCH.h"
#include "WindowApplication3.h"

Hikari::WindowApplication3::WindowApplication3(const char * windowTitle, int xPos, int yPos, int width, int height, const Float4& clearColor)
	:
	WindowApplication(windowTitle, xPos, yPos, width, height, clearColor)
{
}

Hikari::WindowApplication3::~WindowApplication3()
{
}

bool Hikari::WindowApplication3::OnInitialize()
{
	if (!WindowApplication::OnInitialize())
		return false;
	mCamera = new Camera4DV1;
	mRenderer->SetCamera(mCamera);
	return true;
}

void Hikari::WindowApplication3::OnTerminate()
{
	WindowApplication::OnTerminate();
}

bool Hikari::WindowApplication3::OnKeyDown(unsigned char key, int x, int y)
{
	return WindowApplication::OnKeyDown(key, x, y);
}

bool Hikari::WindowApplication3::OnMouseClick(int button, int state, int x, int y, unsigned int modifiers)
{
	return false;
}

bool Hikari::WindowApplication3::OnMotion(int button, int x, int y, unsigned int modifiers)
{
	return false;
}

bool Hikari::WindowApplication3::MoveCamera()
{
	return false;
}

void Hikari::WindowApplication3::MoveForward()
{
}

void Hikari::WindowApplication3::MoveBackward()
{
}

void Hikari::WindowApplication3::MoveUp()
{
}

void Hikari::WindowApplication3::MoveDown()
{
}

void Hikari::WindowApplication3::MoveLeft()
{
}

bool Hikari::WindowApplication3::MoveObject()
{
	return false;
}

void Hikari::WindowApplication3::RotateTrackBall(float x0, float y0, float x1, float y1)
{
}