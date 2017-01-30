#pragma once
#include "WindowApplication.h"

namespace Hikari
{
	class WindowApplication3 : public WindowApplication 
	{
	public:
		WindowApplication3(const char* windowTitle, int xPos, int yPos, int width, int height, const Float4& clearColor);
		virtual ~WindowApplication3();
		virtual bool OnInitialize();
		virtual void OnTerminate();
		virtual bool OnKeyDown(unsigned char key,int x,int y);
	};
}
