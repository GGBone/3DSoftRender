#include "GraphicsPCH.h"
#include "Renderer.h"
#include "Visual.h"
#include "SoftRenderData.h"
using namespace Hikari;

Renderer::Renderer(RendererData& input, int width, int height, Texture::Format colorFormat, Texture::Format depthStencilFormat, int numMultisamples)
{
	Initialize(width, height, Texture::Format(), Texture::Format(), numMultisamples);
	mData = &input;
	float color[] = { 1,0,0,1 };
}
Renderer::~Renderer()
{
	
}
void Renderer::DrawPrimitive(const Visual* visual)
{
	BitBlt(mData->mWindowDC, 0, 0, mWidth, mHeight, mData->mMemoryDC, 0, 0, SRCCOPY);

}