#ifndef Application_H
#define Application_H
#include "Application.h"
namespace Hikari
{
	class Renderer;
	class WindowApplication :public Application
	{
	protected:
		WindowApplication(const char* windowTile, int xPos, int yPos, int width, int height, const Float4& clearColor);
	public:
		virtual ~WindowApplication();
		virtual int Main(int numArg, char** arguments);
		inline const char* GetWindowTitle()const;
		inline int GetXPosition()const;
		inline int GetYPosition()const;
		inline int GetWidth()const;
		inline int GetHeight()const;
		inline void SetWidth(int width);
		inline void SetHeight(int height);
		inline float GetAspectRatio()const;
		inline void SetWindowID(int windowID);
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

		inline virtual bool OnPassiveMotion(int x,int y);

		inline virtual bool OnMouseWheel(int button, int x, int y, unsigned int modifiers);




		void SetMousePosition(int x, int y);
		void GetMousePosition(int& x, int &y)const;

		//Font infomation
		//TO-DO
		//Font

		// Key identifiers.  These are platform-specific, so classes that
		// implement the WindowApplication interfaces must define these variables.
		// They are not defined by WindowApplication.
		int KEY_TERMINATE;  // default KEY_ESCAPE, redefine as desired
		static const int KEY_ESCAPE;
		static const int KEY_LEFT_ARROW;
		static const int KEY_RIGHT_ARROW;
		static const int KEY_UP_ARROW;
		static const int KEY_DOWN_ARROW;
		static const int KEY_HOME;
		static const int KEY_END;
		static const int KEY_PAGE_UP;
		static const int KEY_PAGE_DOWN;
		static const int KEY_INSERT;
		static const int KEY_DELETE;
		static const int KEY_F1;
		static const int KEY_F2;
		static const int KEY_F3;
		static const int KEY_F4;
		static const int KEY_F5;
		static const int KEY_F6;
		static const int KEY_F7;
		static const int KEY_F8;
		static const int KEY_F9;
		static const int KEY_F10;
		static const int KEY_F11;
		static const int KEY_F12;
		static const int KEY_BACKSPACE;
		static const int KEY_TAB;
		static const int KEY_ENTER;
		static const int KEY_RETURN;

		// Keyboard modifiers.
		static const int KEY_SHIFT;
		static const int KEY_CONTROL;
		static const int KEY_ALT;
		static const int KEY_COMMAND;

		// Mouse buttons.
		static const int MOUSE_LEFT_BUTTON;
		static const int MOUSE_MIDDLE_BUTTON;
		static const int MOUSE_RIGHT_BUTTON;

		// Mouse state.
		static const int MOUSE_UP;
		static const int MOUSE_DOWN;

		// Mouse modifiers.
		static const int MODIFIER_CONTROL;
		static const int MODIFIER_LBUTTON;
		static const int MODIFIER_MBUTTON;
		static const int MODIFIER_RBUTTON;
		static const int MODIFIER_SHIFT;

	protected:
		static int Run(int numArgument, char** arguments);

		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		Float4 mClearColor;
		bool mAllowResize;

		int mWindowID;
		Renderer* mRenderer;

		void ResetTime();
		void MeasureTime();
		void UpdateFrameCount();
		void DrawFrameRate(int, int, const float& color);
	
		double mLastTime, mAccumlatedTime, mFrameRate;
		int mFrameCount, mAccumuulatedFrameCount, mTimer, mMaxTimer;
	};
#include "WindowApplication.inl"

#define WINDOW_APPLICATION(classname) \
IMPLEMENT_INITIALIZE(classname);	\
IMPLEMENT_TERMINATE(classname);		\
\
void classname::Initialize()\
{\
	Application::Run = &WindowApplication::Run;\
TheApplication = new classname();\
	}\
\
void classname::Terminate()\
	{\
		delete(TheApplication);	\
	}
}

#endif