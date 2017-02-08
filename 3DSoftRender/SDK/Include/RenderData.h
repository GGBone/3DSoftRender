#pragma once
#include "GraphicsLib.h"
#include <Windows.h>
namespace Hikari
{
	class RendererData
	{
	public:
		RendererData(int width, int heigh, HWND handle);
		virtual ~RendererData();
		 int mWidth;
		 int mHeight;
		 HWND mHwnd;
	};
}