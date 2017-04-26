#pragma once
#include "Dx11RenderLIB.h"
namespace Hikari
{
	class DirectRenderer;
	class RenderTarget;
	class DirectRenderData
	{
	public:
		DirectRenderData(int width, int height, int numMultisamples, HWND handle);
		~DirectRenderData();

		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mImmediateContext = nullptr;
		IDXGISwapChain* g_pSwapChain = nullptr;
		ID3D11Texture2D* pBackBuffer = nullptr;
		RenderTarget* renderTarget;

		void ResizeSwapChainBuffers(uint32_t width, uint32_t height);
		D3D11_VIEWPORT vp;
		int mWidth;
		int mHeight;
		HWND mHwnd;
	};
}