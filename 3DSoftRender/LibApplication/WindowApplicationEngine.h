#pragma once
#include "WindowApplicationBase.h"
#include "ConfigurationSetting.h"
#include "Algebra/AVector.h"
#include "Algebra/Vector3.h"

namespace Hikari
{
	class VisualEffectInstance;
	class Scene;

	class WindowApplicationEngine : protected WindowApplicationBase
	{
	public:
		static ConfigurationSettings g_Setting;
	protected:
		bool OnInitialize(EventArgs& e) override;
		void OnTerminate(EventArgs& e) override;
		WindowApplicationEngine(const char* windowTitle, int xPos, int yPos, int width, int height);
		virtual ~WindowApplicationEngine();

	protected:
		virtual void PreRender(RenderEventArgs& e);
		virtual void Render(RenderEventArgs& e);
		virtual void PostRender(RenderEventArgs& e);
		virtual void QuitLights(WindowCloseEventArgs& e);
		virtual void KeyPress(KeyEventArgs& e);

		virtual void MouseMoved(MouseMotionEventArgs& e);
		virtual void MouseButtonPressed(MouseButtonEventArgs& e);
		virtual void MouseButtonReleased(MouseButtonEventArgs& e);
		virtual void MouseWheel(MouseWheelEventArgs& e);
		//The basic properties of the world
		AVector mWorldAixs[3];
		float mGravity{9.8f};
		Vector3f mGravityDirection{Vector3f(0.0f, -1.0f, 0.0f)};
		float mTemperature{25.0};
		Vector3f mWindDirection{Vector3f(0.0, .0f, .0f)};
		float mWindLevel{0.0f};
		//...

		//observer
		Camera* mCamera;

		//material
		std::shared_ptr<Scene> mainScene;

		std::shared_ptr<Scene> g_FullScreenQuad;

		std::vector<std::shared_ptr<VisualEffectInstance>> mInstance{};

	private:
		Event::ScopedConnections m_EventConnections{};
	};
}
