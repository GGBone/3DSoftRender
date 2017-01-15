#ifndef  WINDOWAPPLICATION3_H
#define  WINDOWAPPLICATION3_H
#include "WindowApplication.h"

namespace Hikari
{
	class WindowApplication3 : public WindowApplication 
	{
	public:
		WindowApplication3(const char* windowTitle, int xPos, int yPos, int width, int height, const float& clearColor);
		virtual ~WindowApplication3();
		virtual bool OnInitialze();

		virtual void OnTerminate();
		virtual bool OnKeyDown(unsigned char key,int x,int y);

	};
}
#endif // ! WINDOWAPPICATION3_H
