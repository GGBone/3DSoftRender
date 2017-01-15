#include "LibApplicationPCH.h"
#include "WindowApplication3.h"

Hikari::WindowApplication3::WindowApplication3(const char * windowTitle, int xPos, int yPos, int width, int height, const float & clearColor)
:
	WindowApplication(windowTitle,xPos,yPos,width,height,clearColor)
{
}

Hikari::WindowApplication3::~WindowApplication3()
{
}

bool Hikari::WindowApplication3::OnInitialze()
{
	return false;
}

void Hikari::WindowApplication3::OnTerminate()
{
	WindowApplication::OnTerminate();
}

bool Hikari::WindowApplication3::OnKeyDown(unsigned char key, int x, int y)
{
	return WindowApplication::OnKeyDown(key,x,y);
}
