#include "GraphicsPCH.h"
#include "RenderWindow.h"
#include "WindowApplicationBase.h"

using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Object, RenderWindow);
IMPLEMENT_RTTI(Hikari, Object, RenderWindow);

void RenderWindow::OnKeyPressed(KeyEventArgs& e)
{
	m_KeyPress(e);
}

RenderWindow::RenderWindow(WindowApplicationBase& application, const std::string& windowsName, int windowWidth,
                           int windowHeight, bool vSync)
	: m_application(application),
	  m_iWindowWidth(windowWidth),
	  m_iWindowHeight(windowHeight),
	  m_vSync(vSync),
	  m_sWindowName(m_sWindowName),
	  m_bInClientRect(false),
	  m_bHasKeyboardFocus(false)

{
	m_PreviousMousePosition[0] = 0.0f;
	m_PreviousMousePosition[1] = 0.0f;
	memset(m_PreviousJoystickInfo, 0, sizeof(m_PreviousJoystickInfo));
	for (int i = 0; i < NUM_SUPPORTED_JOYSTICKS; ++i)
	{
		m_PreviousJoystickInfo[i].dwPOV = JOY_POVCENTERED;
		m_PreviousJoystickInfo[i].dwRpos = 0x7fff;
		m_PreviousJoystickInfo[i].dwXpos = 0x7fff;
		m_PreviousJoystickInfo[i].dwYpos = 0x7fff;
		m_PreviousJoystickInfo[i].dwZpos = 0x7fff;
	}

	m_EventConnections.push_back(m_application.mInitialize += boost::bind(&RenderWindow::OnInitialize, this, _1));
	m_EventConnections.push_back(m_application.mUpdate += boost::bind(&RenderWindow::OnUpdate, this, _1));

	m_EventConnections.push_back(m_application.mTerminate += boost::bind(&RenderWindow::OnTerminate, this, _1));
	m_EventConnections.push_back(m_Resize += boost::bind(&RenderWindow::OnResize, this, _1));
}

RenderWindow::~RenderWindow()
{
	for (Event::ConnectionType& c : m_EventConnections)
	{
		c.disconnect();
	}
}

WindowApplicationBase& RenderWindow::GetApplication()
{
	return m_application;
}

void RenderWindow::OnInitialize(EventArgs& e)
{
	m_Initialize(e);
}

void RenderWindow::OnUpdate(UpdateEventArgs& e)
{
	ProcessJoySticks();
	m_Update(e);
}

void RenderWindow::OnResize(ResizeEventArgs& e)
{
	m_iWindowWidth = e.Width;
	m_iWindowHeight = e.Height;

	//m_Resize(e);
}

void RenderWindow::OnTerminate(EventArgs& e)
{
	m_Terminate(e);
}

bool RenderWindow::IsSync() const
{
	return m_vSync;
}

void RenderWindow::ProcessJoySticks()
{
}

const std::string& RenderWindow::GetWindowsName() const
{
	// TODO: 在此处插入 return 语句
	return m_sWindowName;
}

int RenderWindow::GetWindowWidth() const
{
	return m_iWindowWidth;
}

int RenderWindow::GetWindowHeight() const
{
	return m_iWindowHeight;
}

bool RenderWindow::IsVSync() const
{
	return m_vSync;
}

void RenderWindow::OnPreRender(RenderEventArgs& e)
{
	RenderEventArgs renderArgs(*this, e.ElapsedTime, e.TotalTime, e.FrameCounter, e.Camera, e.PipelineState);
	m_PreRender(renderArgs);
}

void RenderWindow::OnRender(RenderEventArgs& e)
{
	RenderEventArgs renderArgs(*this, e.ElapsedTime, e.TotalTime, e.FrameCounter, e.Camera, e.PipelineState);
	m_Render(renderArgs);
}

void RenderWindow::OnPostRender(RenderEventArgs& e)
{
	RenderEventArgs renderArgs(*this, e.ElapsedTime, e.TotalTime, e.FrameCounter, e.Camera, e.PipelineState);
	m_PostRender(renderArgs);
}

void RenderWindow::OnMouseMoved(MouseMotionEventArgs& e)
{
	if (!m_bInClientRect)
	{
		m_PreviousMousePosition[0] = e.X;
		m_PreviousMousePosition[1] = e.Y;
		m_bInClientRect = true;
	}
	e.RelX = e.X - m_PreviousMousePosition[0];
	e.RelY = e.Y - m_PreviousMousePosition[1];

	m_PreviousMousePosition[0] = e.X;
	m_PreviousMousePosition[1] = e.Y;
	m_MouseMoved(e);
}

void RenderWindow::OnMouseButtonPressed(MouseButtonEventArgs& e)
{
	m_MouseButtonPressed(e);
}

void RenderWindow::OnMouseButtonReleased(MouseButtonEventArgs& e)
{
	m_MouseButtonReleased(e);
}

void RenderWindow::OnMouseWheel(MouseWheelEventArgs& e)
{
	m_MouseWheel(e);
}

void RenderWindow::OnMouseLeave(EventArgs& e)
{
	m_bInClientRect = false;
	m_MouseLeave(e);
}


void RenderWindow::OnMouseFocus(EventArgs& e)
{
	m_MouseFocus(e);
}


void RenderWindow::OnClose(WindowCloseEventArgs& e)
{
	m_Close(e);
}
