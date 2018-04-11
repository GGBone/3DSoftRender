#pragma once
#include "Graphics\Dx11Renderer.h"
#include "Graphics\RenderWindow.h"
namespace Hikari
{
	class RenderTargetDX11;
	class Dx11RenderWindow :public RenderWindow 
	{
	public:
		typedef RenderWindow base;
		Dx11RenderWindow(WindowApplicationBase& app, HWND hwnd, std::shared_ptr<DirectRenderer> device, const std::string& windowName, int iWindowWidth,
			int iWindowHeight,bool vSync=false);
		virtual ~Dx11RenderWindow();
		virtual void ShowWindow() override;
		virtual void HideWindow() override;
		virtual void CloseWindows() override;

	
		virtual void Present() override;

		virtual std::shared_ptr<RenderTarget> GetRenderTarget() override;

	protected:
		virtual void CreateSwapChain();

		virtual void OnPreRender(RenderEventArgs& e) override;
		virtual void OnRender(RenderEventArgs& e) override;
		virtual void OnPostRender(RenderEventArgs& e) override;

		/*virtual void OnMouseMoved(MouseMotionEventArgs& e) override;
		virtual void OnMouseLevel(EventArgs& e) override;*/

		virtual void OnResize(ResizeEventArgs& e)override;
		virtual void OnTerminate(EventArgs& e)override;
		virtual void ResizeSwapChanBuffers(uint32_t width, uint32_t height);

	private:
		bool m_IsMouseTracking;
		HWND m_hWnd;
		DirectRenderer& m_Device;
		
		IDXGISwapChain2* m_pSwapChain;
		ID3D11Texture2D* m_pBackBuffer;
		ID3D11DeviceContext* m_pDeviceContext;
		std::shared_ptr<RenderTargetDX11> m_RenderTarget;
		//Used to enable the AA
		DXGI_SAMPLE_DESC m_SampleDesc;


		bool m_bResizePending;

	};
}