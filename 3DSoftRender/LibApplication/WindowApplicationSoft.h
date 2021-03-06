#ifndef WINDOWAPPLICATION2_H
#define WINDOWAPPLICATION2_H
#include "WindowApplicationBase.h"

namespace Hikari
{
	class WindowApplication2 : public WindowApplicationBase
	{
	public:

		class ColorRGB
		{
		public:
			ColorRGB(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0, unsigned char alpha = 255)
			{
				r = red;
				g = green;
				b = blue;
				a = alpha;
			}

			bool operator==(ColorRGB color) const
			{
				return b == color.b &&
					r == color.r &&
					g == color.g &&
					a == color.a;
			}

			bool operator!=(ColorRGB color) const
			{
				return a != color.a &&
					b != color.b &&
					r != color.r &&
					g != color.g;
			}

			unsigned char r, g, b, a;
		};

		WindowApplication2(const char* windowTitle, int xPos, int yPos, int width, int height,
		                   const ColorRGB& clearColor);
		virtual ~WindowApplication2();

		bool OnInitialize(EventArgs& e) override;
		void OnTerminate(EventArgs& e) override;
		void OnResize(int width, int height) override;
		void OnRender(RenderEventArgs& e) override;

		virtual void ScreenOverlay();

		void ClearScreen();


		void DoFlip(bool doFlip);
		bool& ClampToWindow();

		void SetPixel(int x, int y, ColorRGB color);

		void SetThickPixel(int x, int y, int thick, ColorRGB color);

		ColorRGB GetPixel(int x, int y) const;

		static void DrawLine(int x0, int y0, int x1, int y1, ColorRGB color);

		static void DrawRectangle(int xMin, int yMin, int xMax, int yMax, ColorRGB color, bool solid = false);

		static void DrawCircle(int xCenter, int yCenter, int radius, ColorRGB color, bool solid = false);

		void Fill(int x, int y, ColorRGB foreColor, ColorRGB backColor);

	protected:
		int mScreenWidth, mScreenHeight;

		ColorRGB* mScreen;
		bool mClampToWindow;
		bool mDoFlip;
		float mClearColor[4]{};
	};
}

#endif // !WINDOWAPPLICATION2_h
