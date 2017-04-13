#pragma once
#include "WindowApplication.h"

namespace Hikari
{
	class WindowApplication3 : public WindowApplication
	{
	public:
		WindowApplication3(const char* windowTitle, int xPos, int yPos, int width, int height, const Float4& clearColor);
		virtual ~WindowApplication3();
		virtual bool OnInitialize();
		virtual void OnTerminate();
		virtual bool OnKeyDown(unsigned char key, int x, int y);
		virtual bool OnMouseClick(int button, int state, int x, int y, unsigned int modifiers);
		virtual bool OnMotion(int button, int x, int y, unsigned int modifiers);
	protected:
		virtual bool MoveCamera();
		virtual void MoveForward();
		virtual void MoveBackward();
		virtual void MoveUp();
		virtual void MoveDown();
		virtual void MoveLeft();
		Camera* mCamera;
		AVector mWorldAixs[3];
		bool MoveObject();
		void RotateTrackBall(float x0, float y0, float x1, float y1);
		HMatrix mSaveRotate;
	};
}
