#include "GraphicsPCH.h"
#include "Renderer.h"
#include "Visual.h"
#include "RenderData.h"
#include "SoftRenderData.h"
#include "SoftRenderer.h"

using namespace Hikari;

void SoftRenderer::DrawPrimitive(const Visual* visual)
{
	//BitBlt(mData->mWindowDC, 0, 0, mWidth, mHeight, mData->mMemoryDC, 0, 0, SRCCOPY);

}

Hikari::SoftRenderer::SoftRenderer(SoftRenderData* input, int width, int height, int numMultisamples, HWND handle)
	:
	Renderer((RendererData*)(input)),
	mainFrameBuffer(width,height)
{
	Initialize(width, height, Texture::Format(), Texture::Format(), numMultisamples);
	mData = input;
}

void Hikari::SoftRenderer::SetCullState(CullState * cullState)
{
}

void Hikari::SoftRenderer::SetRenderTarget(SoftFrameBuffer * frameBuffer)
{
}

Hikari::SoftRenderer::~SoftRenderer()
{
}


void Hikari::SoftRenderer::ClearBuffers(int x, int y, int w, int h)
{
}

void Hikari::SoftRenderer::ClearDepthBuffer()
{
}

void Hikari::SoftRenderer::ClearStencilBuffer()
{
}

void Hikari::SoftRenderer::ClearBuffers()
{
}

void Hikari::SoftRenderer::ClearBackBuffer(int x, int y, int w, int h)
{
}

void Hikari::SoftRenderer::ClearDepthBuffer(int x, int y, int w, int h)
{
}

void Hikari::SoftRenderer::ClearStencilBuffer(int x, int y, int w, int h)
{
}
