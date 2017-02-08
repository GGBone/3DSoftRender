#include "WinSoftRenderer.h"
using namespace Hikari;
void Hikari::WinSoftRenderer::ClearSubBackBuffer(int iXMin, int iXMax, int iYMin, int iYMax)
{
}
void Hikari::WinSoftRenderer::SetColorBuffer(int iX, int iY, int iIndex, const ColorRGBA & rkColor)
{
}
Hikari::WinSoftRenderer::WinSoftRenderer(SoftRenderData* data, HWND hWnd)
	:SoftRenderer(data,data->mWidth,data->mHeight,0, hWnd)
{
	mainFrameBuffer.mWindowDC = GetDC(hWnd);
	mainFrameBuffer.mMemoryDC = CreateCompatibleDC(mainFrameBuffer.mWindowDC);

	const size_t uiLength = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD*);
	char* acBitMapInfo = new char[uiLength];
	memset(acBitMapInfo, 0, uiLength);
	BITMAPINFOHEADER& bmih = *(BITMAPINFOHEADER*)acBitMapInfo;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = mWidth;
	bmih.biHeight = mHeight;
	bmih.biPlanes = 1;
	bmih.biBitCount = 32;
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = mWidth*mHeight;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrImportant = 0;
	bmih.biClrUsed = 0;

	unsigned int* BackColorBuffer = 0;
	mainFrameBuffer.mHBitMap = CreateDIBSection(mainFrameBuffer.mMemoryDC, (CONST BITMAPINFO*)acBitMapInfo,
		DIB_RGB_COLORS, (void**)&BackColorBuffer, 0, 0);
	delete[] acBitMapInfo;
	SelectObject(mainFrameBuffer.mMemoryDC, mainFrameBuffer.mHBitMap);
	mainFrameBuffer.mColorBuffer->mData = BackColorBuffer;

	unsigned int* puiColorBuffer = BackColorBuffer;
	unsigned char ucR = (unsigned char)(255.0f*1.0f);
	unsigned char ucG = (unsigned char)(255.0f*0.5f);
	unsigned char ucB = (unsigned char)(255.0f*0.5f);
	unsigned char ucA = (unsigned char)(255.0f*1.0f);
	unsigned int m_uiBackgroundColor = (ucB | (ucG << 8) | (ucR << 16) | (ucA << 24));

	for (int i = 0; i < mWidth*mHeight; i++)
	{
		*puiColorBuffer++ = m_uiBackgroundColor;
	}
	BitBlt(mainFrameBuffer.mWindowDC, 0, 0, mWidth, mHeight, mainFrameBuffer.mMemoryDC, 0, 0, SRCCOPY);

	SetRenderTarget(0);
}

Hikari::WinSoftRenderer::~WinSoftRenderer()
{
	/*delete mData->mainFrameBuffer;
	delete mData->mColorBuffer;
	DeleteDC(mData->mMemoryDC);
	DeleteObject(mData->mHBitMap);
	ReleaseDC(mData->mHwnd, mData->mWindowDC);*/
}

void Hikari::WinSoftRenderer::Draw(const unsigned char * buffer)
{
}

int Hikari::WinSoftRenderer::LoadFont(const char * acFace, int size, bool bBold, bool Italic)
{
	return 0;
}

void Hikari::WinSoftRenderer::UnloadFont(int FontID)
{
}

bool Hikari::WinSoftRenderer::SelectFont(int FontID)
{
	return false;
}

void Hikari::WinSoftRenderer::Draw(int x, int y, const ColorRGBA & rkColor, const char * acText)
{
}

void Hikari::WinSoftRenderer::DisplayBackBuffer()
{
	BitBlt(mainFrameBuffer.mWindowDC, 0, 0, mWidth, mHeight, mainFrameBuffer.mMemoryDC, 0, 0, SRCCOPY);

}

void Hikari::WinSoftRenderer::ClearBackBuffer()
{
	Buffer* colorBuffer = mData->mainFrameBuffer->GetColorBuffer();

}
