#include "Application\LibApplicationPCH.h"
#include "Application\WindowApplicationEngine.h"
#include "Graphics\Camera.h"
#include "Graphics\RenderWindow.h"
using namespace Hikari;
ConfigurationSettings WindowApplicationEngine::g_Setting;
Hikari::WindowApplicationEngine::WindowApplicationEngine(const char * windowTitle, int xPos, int yPos, int width, int height)
	:
	WindowApplicationBase(windowTitle, xPos, yPos, width, height),
	mainScene(nullptr),
	mCamera(nullptr)

{
}


void WindowApplicationEngine::KeyPress(KeyEventArgs & e)
{
	static float speed = 1.f;
	switch (e.Key)
	{
	case KeyCode::W:
		mCamera->Walk(speed*0.2f);

		break;
	case KeyCode::S:
		mCamera->Walk(-speed*0.2f);

		break;

	case KeyCode::A:
		mCamera->Strafe(-speed*0.2f);

		break;

	case KeyCode::D:
		mCamera->Strafe(speed*0.2f);

		break;
	default:
		break;
	}
	mCamera->UpdateViewMatrix();
}

Hikari::WindowApplicationEngine::~WindowApplicationEngine()
{
	delete mCamera;

	for (Event::ConnectionType& c : m_EventConnections)
	{
		c.disconnect();
	}
}

bool Hikari::WindowApplicationEngine::OnInitialize(EventArgs& e)
{
	if (!WindowApplicationBase::OnInitialize(e))
		return false;
	mCamera = new Camera;

	m_EventConnections.push_back(mRenderWindow->m_PreRender += boost::bind(&WindowApplicationEngine::PreRender, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_Render += boost::bind(&WindowApplicationEngine::Render, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_PostRender += boost::bind(&WindowApplicationEngine::PostRender, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_Close += boost::bind(&WindowApplicationEngine::QuitLights, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_KeyPress += boost::bind(&WindowApplicationEngine::KeyPress, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_MouseMoved += boost::bind(&WindowApplicationEngine::MouseMoved, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_MouseButtonPressed += boost::bind(&WindowApplicationEngine::MouseButtonPressed, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_MouseButtonReleased += boost::bind(&WindowApplicationEngine::MouseButtonReleased, this, _1));
	m_EventConnections.push_back(mRenderWindow->m_MouseWheel += boost::bind(&WindowApplicationEngine::MouseWheel, this, _1));


	return true;
}

void Hikari::WindowApplicationEngine::OnTerminate(EventArgs& e)
{
	WindowApplicationBase::OnTerminate(e);
}



void WindowApplicationEngine::PreRender(RenderEventArgs & e)
{

}

void WindowApplicationEngine::Render(RenderEventArgs & e)
{
	e.Camera = mCamera;
	for each (std::shared_ptr<VisualEffectInstance> var in mInstance)
	{
		var->Render(e);
	}
}

void WindowApplicationEngine::PostRender(RenderEventArgs & e)
{
	RenderWindow& renderWindow = dynamic_cast<RenderWindow&>(const_cast<Object&>(e.Caller));
	renderWindow.Present();
}

void WindowApplicationEngine::QuitLights(WindowCloseEventArgs & e)
{
	Stop();
}



void WindowApplicationEngine::MouseMoved(MouseMotionEventArgs & e)
{
	if (e.LeftButton)
	{
		mCamera->OnArcRotate(e);
	}

	if (e.RightButton)
	{
		mCamera->OnMouseMoved(e);
	}

	mCamera->UpdateViewMatrix();

}

void WindowApplicationEngine::MouseButtonPressed(MouseButtonEventArgs & e)
{
	if (e.RightButton)
	{
		mCamera->OnMousePressed(e);
	}

	mCamera->UpdateViewMatrix();

}

void WindowApplicationEngine::MouseButtonReleased(MouseButtonEventArgs & e)
{

	mCamera->OnMouseReleased(e);
	mCamera->UpdateViewMatrix();

}

void WindowApplicationEngine::MouseWheel(MouseWheelEventArgs & e)
{
}



