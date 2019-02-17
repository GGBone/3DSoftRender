#include "LibApplicationPCH.h"
#include "WindowApplicationEngine.h"
#include "SceneGraph/Camera.h"
#include "Renderer/RenderWindow.h"
#include "SceneGraph/VisualEffectInstance.h"
using namespace Hikari;
ConfigurationSettings WindowApplicationEngine::g_Setting;

WindowApplicationEngine::WindowApplicationEngine(const char* windowTitle, int xPos, int yPos, int width, int height)
	:
	WindowApplicationBase(windowTitle, xPos, yPos, width, height),
	mainScene(nullptr)

{
}




WindowApplicationEngine::~WindowApplicationEngine()
{

	for (Event::ConnectionType& c : m_EventConnections)
	{
		c.disconnect();
	}
}

bool WindowApplicationEngine::OnInitialize(EventArgs& e)
{
	if (!WindowApplicationBase::OnInitialize(e))
		return false;

	m_EventConnections.push_back(
		mRenderWindow->m_PreRender += boost::bind(&WindowApplicationEngine::PreRender, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_Render += boost::bind(&WindowApplicationEngine::Render, this, _1));
	m_EventConnections.push_back(
		mRenderWindow->m_PostRender += boost::bind(&WindowApplicationEngine::PostRender, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_Close += boost::bind(&WindowApplicationEngine::QuitLights, this, _1));
	m_EventConnections.
		push_back(mRenderWindow->m_KeyPress += boost::bind(&WindowApplicationEngine::KeyPress, this, _1));
	m_EventConnections.push_back(
		mRenderWindow->m_MouseMoved += boost::bind(&WindowApplicationEngine::MouseMoved, this, _1));
	m_EventConnections.push_back(
		mRenderWindow->m_MouseButtonPressed += boost::bind(&WindowApplicationEngine::MouseButtonPressed, this, _1));
	m_EventConnections.push_back(
		mRenderWindow->m_MouseButtonReleased += boost::bind(&WindowApplicationEngine::MouseButtonReleased, this, _1));
	m_EventConnections.push_back(
		mRenderWindow->m_MouseWheel += boost::bind(&WindowApplicationEngine::MouseWheel, this, _1));


	return true;
}

void WindowApplicationEngine::OnTerminate(EventArgs& e)
{
	WindowApplicationBase::OnTerminate(e);
}


void WindowApplicationEngine::PreRender(RenderEventArgs& e)
{
}
void Hikari::WindowApplicationEngine::KeyPress(KeyEventArgs & e)
{

}

void WindowApplicationEngine::Render(RenderEventArgs& e)
{
	for each (std::shared_ptr<VisualEffectInstance> var in mInstance)
	{
		var->Render(e);
	}
}

void WindowApplicationEngine::PostRender(RenderEventArgs& e)
{
	RenderWindow& renderWindow = dynamic_cast<RenderWindow&>(const_cast<Object&>(e.Caller));
	renderWindow.Present();
}

void WindowApplicationEngine::QuitLights(WindowCloseEventArgs& e)
{
	Stop();
}


void WindowApplicationEngine::MouseMoved(MouseMotionEventArgs& e)
{
	
}

void WindowApplicationEngine::MouseButtonPressed(MouseButtonEventArgs& e)
{
	
}

void WindowApplicationEngine::MouseButtonReleased(MouseButtonEventArgs& e)
{
	
}

void WindowApplicationEngine::MouseWheel(MouseWheelEventArgs& e)
{
}
