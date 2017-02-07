#include "WinSoftRenderer.h"
using namespace Hikari;
Hikari::WinSoftRenderer::WinSoftRenderer(SoftRenderData * data, HWND hWnd)
	:SoftRenderer(data,data->mWidth,data->mHeight,0,mData->mHwnd)
{
	SetRenderTarget(0);
}

Hikari::WinSoftRenderer::~WinSoftRenderer()
{
	delete mData->mainFrameBuffer;
	delete mData->mColorBuffer;
	DeleteDC(mData->mMemoryDC);
	DeleteObject(mData->mHBitMap);
	ReleaseDC(mData->mHwnd, mData->mWindowDC);
}

void Hikari::WinSoftRenderer::ClearBackBuffer()
{
	Buffer* colorBuffer = mData->mainFrameBuffer->GetColorBuffer();

	colorBuffer->SetData(mData->mColorBuffer);
}
