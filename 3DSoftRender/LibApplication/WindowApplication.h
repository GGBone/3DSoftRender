#ifndef WINDOWAPPLICATION_H
#define WINDOWAPPLICATION_H

#include "Application.h"
namespace Hikari
{
	class WindowApplication :public Application
	{
	protected:
		WindowApplication(const char* windowTile, int xPos, int yPos, int width, int height, const float& clearColor);
	public:
		virtual ~WindowApplication();
		virtual int Main(int numArg, char* arguments);
		
		inline const char* GetWindowTitle()const;
		inline int GetXPosition()const;
		inline int GetYPosition()const;
		inline int GetWidth()const;
		inline int GetHeight()const;
		inline float GetAspectRatio()const;
		inline void SetWindowID(int windowID)const;
		inline int GetWindowID()const;
		
		inline const Renderer* GetRenderer();

		virtual bool OnInitialize();
		virtual void OnTerminate();
		virtual void OnMove(int x, int y);
		virtual void OnResize(int windth, int height);
		inline virtual bool OnPrecreate();
		inline virtual void OnPreidle();
		inline virtual void OnDisplay();
		inline virtual void OnIdle();
		virtual bool OnKeyDown(unsigned char key, int x, int y);
		inline virtual bool OnKeyUp(unsigned char key, int x, int y);

		inline virtual bool OnSpecialKeyDown(int key, int x, int y);

		inline virtual bool OnSpecialKeyUp(int key, int x, int y);

		inline virtual bool OnMouseClick(int button,int state,int x, int y,unsigned int modifiers);

		inline virtual bool OnMotion(int button, int x, int y,unsigned int modifiers);

		inline virtual bool OnPassiveMotion(int button, int x, int y, unsigned int modifiers);

		inline virtual bool OnMouseWheel(int button, int x, int y, unsigned int modifiers);




		void SetMousePosition(int x, int y);
		void GetMousePosition(int& x, int &y)const;

		//Font infomation
		//TO-DO
		//Font

		int KEY_TERMINATE;



	protected:
		static int Run(int numArgument, char** arguments);

		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		float mClearColor;
		bool mAllowResize;

		int mWindowID;

		void ResetTime();
		void MeasureTime();
		void UpdateFrameCount();
		void DrawFrameRate(int, int, const float& color);
	};
#include "WindowApplication.inl"

#define WINDOW_APPLICATION(classname) \


}


#endif