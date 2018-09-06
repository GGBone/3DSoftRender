#pragma once
#include "Renderer.h"
#include "SoftRenderData.h"
#include "SoftRenderer.h"
namespace Hikari

{
	class WinSoftRenderer : public SoftRenderer
	{

	private:
		SoftRenderData* mData;
		virtual void ClearSubBackBuffer(int iXMin, int iXMax, int iYMin, int iYMax);
		virtual void SetColorBuffer(int iX, int iY, int iIndex, const ColorRGBA& rkColor);


	public:
		WinSoftRenderer(SoftRenderData* data,HWND hWnd);
		~WinSoftRenderer();

		//2D
		virtual void Draw(const unsigned char* buffer);
		//text Drawing
		virtual int LoadFont(const char* acFace, int size, bool bBold, bool Italic);
		virtual void UnloadFont(int FontID);
		virtual bool SelectFont(int FontID);
		virtual void Draw(int x, int y, const ColorRGBA& rkColor, const char* acText);
		// back buffer handling
		virtual void DisplayBackBuffer();
		virtual void ClearBackBuffer();
	};
}