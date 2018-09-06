#pragma once
#include "Core.h"
#include "Renderer.h"
#include "Graphics.h"

namespace Hikari
{
#define NUM_SUPPORTED_JOYSTICKS 16

	class RenderWindow : public Object
	{
	DECLARE_NAMES;
	DECLARE_RTTI;
	public:
		virtual void ShowWindow() = 0;
		virtual void HideWindow() = 0;
		virtual void CloseWindows() = 0;

		const std::string& GetWindowsName() const;
		int GetWindowWidth() const;
		int GetWindowHeight() const;

		bool IsVSync() const;


		Event m_Initialize{};
		Event m_Terminate{};

		WindowCloseEvent m_Close{};
		Event m_InputFocus{};
		Event m_InputBlur{};
		Event m_Minmize{};
		Event m_Restore{};
		Event m_Expose{};

		UpdateEvent m_Update{};

		RenderEvent m_PreRender{};
		RenderEvent m_Render{};
		RenderEvent m_PostRender{};
		//Keyboard
		KeyboardEvent m_KeyPress{};
		KeyboardEvent m_KeyRelease{};

		Event m_KeyboardBlur{};

		//Mouse Event
		MouseMotionEvent m_MouseMoved{};
		MouseButtonEvent m_MouseButtonPressed{};
		MouseButtonEvent m_MouseButtonReleased{};
		MouseWheelEvent m_MouseWheel{};

		Event m_MouseLeave{};
		Event m_MouseFocus{};
		Event m_MouseBlur{};

		//Joystrick
		JoystickButtonEvent m_JoystickByfferPressed{};
		JoystickButtonEvent m_JoystickByfferReleased{};
		JoystickPOVEvent m_JoystickPOV{};
		JoystickAxisEvent m_JoystickAxis{};

		ResizeEvent m_Resize{};

		void SetRenderer(std::shared_ptr<Renderer> render) { m_Renderer = render; }

		virtual void OnClose(WindowCloseEventArgs& e);

		virtual void Present() = 0;

		virtual std::shared_ptr<RenderTarget> GetRenderTarget() = 0;


	protected:
		friend class WindowApplicationBase;

		friend LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		RenderWindow(WindowApplicationBase& application, const std::string& windowsName, int windowWidth,
		             int windowHeight, bool vSync = false);
		virtual ~RenderWindow();
		WindowApplicationBase& GetApplication();

		virtual void OnKeyPressed(KeyEventArgs& e);
		virtual void OnInitialize(EventArgs& e);
		virtual void OnUpdate(UpdateEventArgs& e);
		virtual void OnResize(ResizeEventArgs& e);
		virtual void OnTerminate(EventArgs& e);

		virtual void OnPreRender(RenderEventArgs& e);
		virtual void OnRender(RenderEventArgs& e);
		virtual void OnPostRender(RenderEventArgs& e);


		virtual void OnMouseMoved(MouseMotionEventArgs& e);
		virtual void OnMouseButtonPressed(MouseButtonEventArgs& e);
		virtual void OnMouseButtonReleased(MouseButtonEventArgs& e);
		virtual void OnMouseWheel(MouseWheelEventArgs& e);
		virtual void OnMouseLeave(EventArgs& e);
		virtual void OnMouseFocus(EventArgs& e);
		bool IsSync() const;

		static void ProcessJoySticks();
		WindowApplicationBase& m_application;
		int m_iWindowWidth;
		int m_iWindowHeight;
		bool m_vSync;
		std::string m_sWindowName;
		int m_PreviousMousePosition[2]{};
		JOYINFOEX m_PreviousJoystickInfo[NUM_SUPPORTED_JOYSTICKS]{};
		bool m_bInClientRect;
		bool m_bHasKeyboardFocus;
		std::shared_ptr<Renderer> m_Renderer{};
		Event::ScopedConnections m_EventConnections{};
	};
}
