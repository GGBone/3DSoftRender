#include "GraphicsPCH.h"
#include "SoftRenderData.h"
Hikari::RendererData::RendererData(int width, int height, int numMultisamples, HWND handle)
	:mHwnd(handle),
	mWidth(width),
	mHeight(height)
{
	InitDevice();
}

bool Hikari::RendererData::InitDevice()
{

	mWindowDC = GetDC(mHwnd);
	mMemoryDC = CreateCompatibleDC(mWindowDC);

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
	mHBitMap = CreateDIBSection(mMemoryDC, (CONST BITMAPINFO*)acBitMapInfo,
		DIB_RGB_COLORS, (void**)&BackColorBuffer, 0, 0);
	delete[] acBitMapInfo;
	SelectObject(mMemoryDC, mHBitMap);
	m_BackColorBuffer = BackColorBuffer;

	unsigned int* puiColorBuffer = m_BackColorBuffer;
	unsigned char ucR = (unsigned char)(255.0f*1.0f);
	unsigned char ucG = (unsigned char)(255.0f*0.5f);
	unsigned char ucB = (unsigned char)(255.0f*0.5f);
	unsigned char ucA = (unsigned char)(255.0f*1.0f);
	unsigned int m_uiBackgroundColor = (ucB | (ucG << 8) | (ucR << 16) | (ucA << 24));
	
	for (int i = 0; i < mWidth*mHeight; i++)
	{
		*puiColorBuffer++ = m_uiBackgroundColor;
	}
	BitBlt(mWindowDC, 0, 0, mWidth / 2, mHeight / 2, mMemoryDC, 0, 0, SRCCOPY);
	
	return true;
}

Hikari::RendererData::~RendererData()
{

}