#include "LibApplicationPCH.h"
#include "WindowApplicationSoft.h"
using namespace Hikari;

WindowApplication2::
WindowApplication2(const char* windowTitle, int xPos, int yPos, int width, int height, const ColorRGB& clearColor)
	: WindowApplicationBase(windowTitle, xPos, yPos, width - (width % 4), height),
	  mScreenWidth(0),
	  mScreenHeight(0),
	  mScreen(nullptr),
	  mClampToWindow(true),
	  mDoFlip(false)
{
}

WindowApplication2::~WindowApplication2()
= default;

bool WindowApplication2::OnInitialize(EventArgs& e)
{
	if (!WindowApplicationBase::OnInitialize(e))
	{
		return false;
	}
	mScreenHeight = GetHeight();
	mScreenWidth = GetWidth();
	mScreen = new ColorRGB[mScreenWidth * mScreenHeight];
	ClearScreen();
	return true;
}

void WindowApplication2::OnTerminate(EventArgs& e)
{
	delete mScreen;
	WindowApplicationBase::OnTerminate(e);
}

void WindowApplication2::OnResize(int width, int height)
{
}

void WindowApplication2::OnRender(RenderEventArgs& e)
{
	WindowApplicationBase::OnRender(e);
}

void WindowApplication2::ScreenOverlay()
{
}

void WindowApplication2::ClearScreen()
{
	unsigned char r = (unsigned char)(255.0f * mClearColor[0]);
	unsigned char g = (unsigned char)(255.0f * mClearColor[1]);
	unsigned char b = (unsigned char)(255.0f * mClearColor[2]);
	unsigned char a = (unsigned char)(255.0f * mClearColor[3]);
	ColorRGB color(r, g, b, a);
	ColorRGB* current = mScreen;
	const int iMax = mWidth * mHeight;
	for (int i = 0; i < iMax; i++)
	{
		*current = color;
	}
}

void WindowApplication2::DoFlip(bool doFlip)
{
	mDoFlip = doFlip;
}

bool& WindowApplication2::ClampToWindow()
{
	return mClampToWindow;
	// TODO: 在此处插入 return 语句
}

void WindowApplication2::SetPixel(int x, int y, ColorRGB color)
{
	if (mClampToWindow)
	{
		if (0 <= x && x < mWidth && 0 <= y && y < mHeight)
		{
			mScreen[x + mWidth * y] = color;
		}
	}
	else
		mScreen[x + mWidth * y] = color;
}

void WindowApplication2::SetThickPixel(int x, int y, int thick, ColorRGB color)
{
	for (int dy = -thick; dy <= thick; ++dy)
	{
		for (int dx = -thick; dx <= thick; ++dx)
		{
			SetPixel(x + dx, y + dy, color);
		}
	}
}

WindowApplication2::ColorRGB WindowApplication2::GetPixel(int x, int y) const
{
	if (mClampToWindow)
	{
		if (0 <= x && x < mWidth && 0 <= y && y <= mHeight)
		{
			return mScreen[x + mWidth * y];
		}
		return ColorRGB(0, 0, 0, 0);
	}
	return mScreen[x + mWidth * y];
}

void WindowApplication2::DrawLine(int x0, int y0, int x1, int y1, ColorRGB color)
{
}

void WindowApplication2::DrawRectangle(int xMin, int yMin, int xMax, int yMax, ColorRGB color, bool solid)
{
}

void WindowApplication2::DrawCircle(int xCenter, int yCenter, int radius, ColorRGB color, bool solid)
{
}

void WindowApplication2::Fill(int x, int y, ColorRGB foreColor, ColorRGB backColor)
{
	int xMax = mWidth, yMax = mHeight;
	int stackSize = xMax * yMax;
	int* xStack = new int[stackSize];
	int* yStack = new int[stackSize];

	int top = 0;
	xStack[top] = x;
	yStack[top] = y;
	while (top >= 0)
	{
		x = xStack[top];
		y = yStack[top];

		SetPixel(x, y, foreColor);

		int xp1 = x + 1;
		if (xp1 < xMax && GetPixel(xp1, y) == backColor)
		{
			top++;
			xStack[top] = xp1;
			yStack[top] = y;
			continue;
		}
		int xm1 = x - 1;
		if (0 <= xm1 && GetPixel(xm1, y) == backColor)
		{
			top++;
			xStack[top] = xm1;
			xStack[top] = y;
			continue;
		}
		int yp1 = y + 1;
		if (yp1 < yMax && GetPixel(x, xp1) == backColor)
		{
			top++;
			xStack[top] = x;
			yStack[top] = yp1;
			continue;
		}
		int ym1 = y - 1;
		if (0 <= ym1 && GetPixel(x, ym1) == backColor)
		{
			top++;
			xStack[top] = x;
			yStack[top] = ym1;
			continue;
		}
		top--;
	}
	delete[] xStack;
	delete[] yStack;
}
