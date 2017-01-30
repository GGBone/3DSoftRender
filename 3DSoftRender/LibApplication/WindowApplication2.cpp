#include "LibApplicationPCH.h"
#include "WindowApplication2.h"
using namespace Hikari;

Hikari::WindowApplication2::
WindowApplication2(const char * windowTitle, int xPos, int yPos, int width, int height, const Float4 & clearColor)
	:WindowApplication(windowTitle, xPos, yPos, width - (width % 4), height, clearColor),
	mScreenWidth(0),
	mScreenHeight(0),
	mScreen(0),
	mClampToWindow(true),
	mDoFlip(false)
{
	
}

Hikari::WindowApplication2::~WindowApplication2()
{
}

bool Hikari::WindowApplication2::OnInitialize()
{
	if (!WindowApplication::OnInitialize())
	{
		return false;
	}
	mScreenHeight = GetHeight();
	mScreenWidth = GetWidth();
	mScreen = new ColorRGB[mScreenWidth * mScreenHeight];
	ClearScreen();
	return true;
}

void Hikari::WindowApplication2::OnTerminate()
{
	delete mScreen;
	WindowApplication::OnTerminate();
}

void Hikari::WindowApplication2::OnResize(int width, int height)
{
}

void Hikari::WindowApplication2::OnDisplay()
{

}

void Hikari::WindowApplication2::ScreenOverlay()
{
}

void Hikari::WindowApplication2::ClearScreen()
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

void Hikari::WindowApplication2::DoFlip(bool doFlip)
{
	mDoFlip = doFlip;
}

bool & Hikari::WindowApplication2::ClampToWindow()
{
	return mClampToWindow;
	// TODO: 在此处插入 return 语句
}

void Hikari::WindowApplication2::SetPixel(int x, int y, ColorRGB color)
{
	if (mClampToWindow)
	{
		if (0 <= x&& x < mWidth && 0 <= y && y < mHeight)
		{
			mScreen[x + mWidth*y] = color;
		}
	}
	else
		mScreen[x + mWidth * y] = color;
}

void Hikari::WindowApplication2::SetThickPixel(int x, int y, int thick, ColorRGB color)
{
	for (int dy = -thick; dy <= thick;++dy)
	{
		for (int dx = -thick; dx <= thick; ++dx)
		{
			SetPixel(x + dx, y + dy, color);
		}
	}
}

WindowApplication2::ColorRGB Hikari::WindowApplication2::GetPixel(int x, int y) const
{
	if (mClampToWindow)
	{
		if (0 <= x && x < mWidth && 0 <= y && y <= mHeight)
		{
			return mScreen[x + mWidth*y];
		}
		else return ColorRGB(0, 0, 0, 0);
	}
	else 
		return mScreen[x + mWidth*y];
}

void Hikari::WindowApplication2::DrawLine(int x0, int y0, int x1, int y1, ColorRGB color)
{
}

void Hikari::WindowApplication2::DrawRectangle(int xMin, int yMin, int xMax, int yMax, ColorRGB color, bool solid)
{
}

void Hikari::WindowApplication2::DrawCircle(int xCenter, int yCenter, int radius, ColorRGB color, bool solid)
{
}

void Hikari::WindowApplication2::Fill(int x, int y, ColorRGB foreColor, ColorRGB backColor)
{
	int xMax = mWidth, yMax = mHeight;
	int stackSize = xMax * yMax;
	int * xStack = new int[stackSize];
	int * yStack = new int[stackSize];

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

