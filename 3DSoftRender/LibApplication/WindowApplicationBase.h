#pragma once
#include "Application.h"
#define ENABLE_BOOST
#define FREEIMAGE_LIB
#define ENABLE_ASSIMP
#include "Event.h"
#include "ReadDirectoryChanges.h"

#undef ENABLE_ASSIMP
#undef FREEIMAGE_LIB
#undef ENABLE_BOOST
extern LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hikari
{
	class UserEventArgs;
	class FileChangeEventArgs;
	class Renderer;
	class RenderWindow;
	class ProgressWindow;
	static bool gsIgnoreWindowDestroy = false;
	typedef std::map<HWND, std::shared_ptr<RenderWindow>> WindowHandleMap;
	static WindowHandleMap gs_WindowHandleMap;
	static float g_GameDeltaTime = 0.0f;
	static float g_AppcationTime = 0.0f;
	static int64_t g_FrameCounter = 0;

	class WindowApplicationBase : public Application
	{
	protected:
		WindowApplicationBase(const char* windowTile, int xPos, int yPos, int width, int height);
	public:
		virtual ~WindowApplicationBase();
		virtual int Main(int numArg, char** arguments);
		const char* GetWindowTitle() const { return mWindowTitle.c_str(); }
		int GetXPosition() const { return mYPosition; }
		int GetYPosition() const { return mXPosition; }
		int GetWidth() const { return mWidth; }
		int GetHeight() const { return mHeight; }
		void SetWidth(int width) { mWidth = width; }
		void SetHeight(int height) { mHeight = height; }
		static float GetAspectRatio() { return 0.0f; }
		void SetWindowID(int windowID) { mWindowID = windowID; }
		int GetWindowID() const { return mWindowID; }
		HINSTANCE GetModuleHandle() const { return m_hInstance; }
		inline const std::shared_ptr<Renderer> GetRenderer();
		void CheckFileChange();
		void SetMousePosition(int x, int y);
		void GetMousePosition(int& x, int& y) const;
		void OnFileChange(FileChangeEventArgs& e);
		void OnUserEvent(UserEventArgs& e);

		virtual void Stop();
		Event mInitialize;
		UpdateEvent mUpdate;

		//Exit the application
		Event mExit;

		//This event is called when the application is going to be terminated
		Event mTerminate;

		//This event is called when the application has been terminated
		Event mTerminated;

		FileChangeEvent mFileChanged;

		UserEvent mUserEvent;

	protected:
		static int Run(int numArgument, char** arguments);

		std::string mWindowTitle;
		int mXPosition, mYPosition, mWidth, mHeight;
		bool mAllowResize;

		int mWindowID;

		static void ResetTime();
		static void MeasureTime();
		static void UpdateFrameCount();
		void DrawFrameRate(int, int, const float& color);

		double mLastTime{}, mAccumlatedTime{}, mFrameRate{};
		int mFrameCount{}, mAccumuulatedFrameCount{}, mTimer{}, mMaxTimer{};


		virtual bool OnInitialize(EventArgs& e);
		virtual void OnTerminate(EventArgs& e);
		virtual void OnExit(EventArgs& e);


		virtual void OnResize(int windth, int height);

		virtual bool OnPrecreate(EventArgs& e);
		virtual void OnPreIdle(EventArgs& e);
		virtual void OnUpdate(UpdateEventArgs& e);

		virtual void OnRender(RenderEventArgs& e);

		//virtual void OnMouseFocus(EventArgs& e);//Default when you focus the app's menu
		//virtual void OnMouseLeave(EventArgs& e);//Default when you unfocus the app's menu
		//virtual void OnMouseWheel(MouseWheelEventArgs& e);
		//virtual void OnMouseBlur(EventArgs& e);
		//virtual void OnMouseMoved(MouseMotionEventArgs& e);
		//virtual void OnMouseButtonPressed(MouseButtonEventArgs& e);
		//virtual void OnMouseButtonReleased(MouseButtonEventArgs& e);
		//virtual void OnMotionMove(MouseMotionEventArgs& e);

		void RegisterDirectojryChangeListener(const std::wstring& dir, bool recursive);

		std::shared_ptr<Renderer> m_pRenderDevice;

		std::shared_ptr<RenderWindow> mRenderWindow;
		std::shared_ptr<ProgressWindow> mProgressWindow;
	private:
		void CreateRenderWindow(const std::string& title, int width, int height);

		void CreateProgressWindow(const std::string& title, int width, int height);
		float m_floatTime{};
		bool m_bIsInitialized;
		bool m_bIsRunning;
		std::string m_windowName;
		HINSTANCE m_hInstance{};
		//Directory change listener
		CReadDirectoryChanges m_DirectoryChanges;


		//Thread to run directory change listener
		std::thread m_DirectoryChangeListenerThread;

		//Thread to protect changes to dictory change listener
		typedef std::recursive_mutex Mutex;

		typedef std::unique_lock<Mutex> MutexLock;
		Mutex m_DirectoryChangeMutex;

		//Flag to terminate directory change thread.
		std::atomic<bool> m_bTerminateDirectoryChangeThread;

		typedef std::map<std::string, std::shared_ptr<RenderWindow>> WindowMap;
		WindowMap m_Windows{};
	};


#define WINDOW_APPLICATION(classname) \
IMPLEMENT_INITIALIZE(classname);	\
IMPLEMENT_TERMINATE(classname);		\
\
void classname::Initialize()\
{\
	Application::Run = &WindowApplicationBase::Run;\
TheApplication = new classname();\
	}\
\
void classname::Terminate()\
	{\
		delete(TheApplication);	\
	}
}
