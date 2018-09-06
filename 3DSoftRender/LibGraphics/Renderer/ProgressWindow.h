#pragma once
#include "RenderWindow.h"

namespace Hikari
{
#define NUM_SUPPORTED_JOYSTICKS 16

	class ProgressWindow : public RenderWindow
	{
	DECLARE_NAMES;
	DECLARE_RTTI;
	public:
		typedef RenderWindow base;
		void ShowWindow() override;
		void HideWindow() override;
		void CloseWindows() override;

		void Present() override;

		std::shared_ptr<RenderTarget> GetRenderTarget() override;

		void SetTotalProgress(float totalProgress);
		void UpdateProgress(ProgressEventArgs& e);
		virtual ~ProgressWindow();
		friend WindowApplicationBase;
		ProgressWindow(WindowApplicationBase& app, const std::string& name, HWND hwnd, int width, int height,
		               float totalProgress = 100.0f);

	protected:

		HWND m_hParentWindow;
		HWND m_hProgressWindow{};
		float m_fTotalProgress;
		float m_fCurrentProgress;

		float m_fPreviousProgress;
	};
}
