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

	protected:
		static int mWidth;
		static int mHeight;
		static HWND mHwnd;
	};
}