#pragma once
#include "Dx11RenderLIB.h"
#include "SoftFrameBuffer.h"
namespace Hikari

{
	class SoftRenderData
	{
	public:
		SoftRenderData(int width, int height, int numMultisamples, HWND handle);
		~SoftRenderData();
		
		SoftFrameBuffer* mainFrameBuffer;
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