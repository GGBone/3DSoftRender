#include "GraphicsPCH.h"
#include "ProgressWindow.h"
#include "WindowApplicationBase.h"

using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(RenderWindow, ProgressWindow);
IMPLEMENT_RTTI(Hikari, RenderWindow, ProgressWindow);

void ProgressWindow::ShowWindow()
{
	::ShowWindow(m_hParentWindow, SW_SHOW);
}

void ProgressWindow::HideWindow()
{
	::ShowWindow(m_hParentWindow, SW_HIDE);
}

void ProgressWindow::CloseWindows()
{
	if (m_hProgressWindow)
	{
		DestroyWindow(m_hProgressWindow);
		m_hProgressWindow = nullptr;
	}
	if (m_hParentWindow)
	{
		DestroyWindow(m_hParentWindow);
		m_hParentWindow = nullptr;
	}
}

void ProgressWindow::Present()
{
}

std::shared_ptr<RenderTarget> ProgressWindow::GetRenderTarget()
{
	return std::shared_ptr<RenderTarget>();
}

void ProgressWindow::SetTotalProgress(float totalProgress)
{
	m_fTotalProgress = totalProgress;
	SendMessageA(m_hProgressWindow, PBM_SETRANGE, 0, MAKELPARAM(0, (totalProgress * 100.0f)));
}

void ProgressWindow::UpdateProgress(ProgressEventArgs& e)
{
	if (e.Progress < m_fPreviousProgress)
	{
		m_fCurrentProgress += (1.0f - m_fPreviousProgress);
		m_fPreviousProgress = e.Progress;
	}
	else
	{
		m_fCurrentProgress += (e.Progress - m_fPreviousProgress);
	}
	m_fPreviousProgress = e.Progress;
	SendMessageA(m_hProgressWindow, PBM_SETPOS, (WPARAM)(m_fCurrentProgress * 100.0f), 0);
}

ProgressWindow::ProgressWindow(WindowApplicationBase& app, const std::string& name, HWND hwnd, int width, int height,
                               float totalProgress)
	:
	base(app, "", width, height),
	m_hParentWindow(hwnd),
	m_fTotalProgress(totalProgress),
	m_fCurrentProgress(0.0f),
	m_fPreviousProgress(0.0f)
{
	RECT clientArea;
	GetClientRect(hwnd, &clientArea);
	m_hProgressWindow = CreateWindowExA(
		0, PROGRESS_CLASSA, nullptr,
		WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		clientArea.left, clientArea.top, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top,
		m_hParentWindow, nullptr, app.GetModuleHandle(), nullptr);
	if (!m_hProgressWindow)
	{
		return;
	}
	SetTotalProgress(totalProgress);
}

ProgressWindow::~ProgressWindow()
{
	CloseWindows();
}
