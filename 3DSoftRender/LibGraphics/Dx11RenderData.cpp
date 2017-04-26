#include "RenderData.h"
#include "Dx11RenderLIB.h"
#include "Dx11RenderData.h"
#include "Dx11Renderer.h"
#include "RenderTarget.h"
using namespace Hikari;
Hikari::DirectRenderData::DirectRenderData(int width, int height, int numMultisamples, HWND handle)
	:mWidth(width),
	mHeight(height),
	mHwnd(handle)
{
}

Hikari::DirectRenderData::~DirectRenderData()
{
}

void Hikari::DirectRenderData::ResizeSwapChainBuffers(uint32_t width, uint32_t height)
{
	mImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);
	pBackBuffer = nullptr;
	g_pSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),(LPVOID*) &pBackBuffer);
	renderTarget->Resize(width, height);
}