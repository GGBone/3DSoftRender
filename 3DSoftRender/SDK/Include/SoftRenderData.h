#pragma once
#include "Dx11RenderLIB.h"
namespace Hikari

{
	class RendererData
	{
	public:
		RendererData(int width, int height, int numMultisamples, HWND handle);
		~RendererData();
		unsigned int* m_auiColorBuffer;
		int* FrameBuffer;
		int mWidth;
		int mHeight;
		int* mColorBuffer;
		HWND mHwnd;
		HDC mWindowDC, mMemoryDC;
		HBITMAP mHBitMap;
	private:
		bool InitDevice();
	};
}