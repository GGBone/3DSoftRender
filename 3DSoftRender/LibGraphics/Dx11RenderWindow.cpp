#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11RenderWindow.h"
#include "Graphics\Dx11RenderTarget.h"

using namespace Hikari;

static DXGI_RATIONAL  QueryRefreshRate(UINT screenWidth, UINT screenHeight, BOOL vSync)
{
	DXGI_RATIONAL refreshRate = {0,1};
	if (vSync)
	{
		IDXGIFactory* factory;
		IDXGIAdapter* adapter;
		IDXGIOutput* adapterOutput;
		DXGI_MODE_DESC* displayModeList;
		if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
		{

		}
		if (FAILED(factory->EnumAdapters(0, &adapter)))
		{

		}
		if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
		{

		}

		UINT numDisplayModes;
		if (adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numDisplayModes,NULL))
			
		{

		}
		displayModeList = new DXGI_MODE_DESC[numDisplayModes];
		assert(displayModeList);
		if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numDisplayModes, displayModeList)))
		{

		}

		for (UINT i = 0; i < numDisplayModes; ++i)
		{
			if (displayModeList[i].Width == screenWidth && displayModeList[i].Height == screenHeight)
			{
				refreshRate = displayModeList[i].RefreshRate;
			}
		}
		delete[] displayModeList;
	}
	return refreshRate;
}
Hikari::Dx11RenderWindow::Dx11RenderWindow(WindowApplicationBase & app, HWND hwnd, std::shared_ptr<DirectRenderer>& device, const std::string & windowName, int iWindowWidth, int iWindowHeight, bool vSync)
	: base(app, windowName, iWindowWidth, iWindowHeight)
	,m_IsMouseTracking(false)
	,m_hWnd(hwnd) 
	, m_Device(device)
	, m_pDeviceContext(m_Device->GetDeviceContext())
	, m_bResizePending(true)
{
	m_SampleDesc = { 1,0 };
	m_RenderTarget = std::dynamic_pointer_cast<RenderTargetDX11>(m_Device->CreateRenderTarget());
	CreateSwapChain();
}

Hikari::Dx11RenderWindow::~Dx11RenderWindow()
{
	m_Device.reset();
}

void Hikari::Dx11RenderWindow::ShowWindow()
{
	::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	::BringWindowToTop(m_hWnd);
}

void Hikari::Dx11RenderWindow::HideWindow()
{
	::ShowWindow(m_hWnd, SW_HIDE);
}

void Hikari::Dx11RenderWindow::CloseWindows()
{
	::DestroyWindow(m_hWnd);
}

void Hikari::Dx11RenderWindow::CreateSwapChain()
{
	UINT windowWidth = GetWindowWidth();
	UINT windowHeight = GetWindowHeight();
	bool vSync = IsVSync();
	std::string name = GetWindowsName();
	IDXGIFactory2* factory;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory2),(void**) &factory)))
	{

	}
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = windowWidth;
	swapChainDesc.Height = windowHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SampleDesc = m_SampleDesc;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullScreenDesc = {};
	swapChainFullScreenDesc.RefreshRate = QueryRefreshRate(windowWidth, windowHeight, vSync);

	swapChainFullScreenDesc.Windowed = true;
	IDXGISwapChain1* pSwapChain;

	if (FAILED(factory->CreateSwapChainForHwnd(m_Device->GetDevice(), m_hWnd, &swapChainDesc, &swapChainFullScreenDesc, nullptr, &pSwapChain)))
	{

	}
	pSwapChain->QueryInterface<IDXGISwapChain2>(&m_pSwapChain);
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pBackBuffer);

	Texture::TextureFormat depthStencilTextureFormat
	(Texture::Components::DepthStencil,
		Texture::Type::UnsignedNormalized,
		
		m_SampleDesc.Count,
		0,0,0,0,24,8);

	std::shared_ptr<Texture> depthStencilTexture = m_Device->CreateTexture2D(windowWidth,
		windowHeight, 1, depthStencilTextureFormat);

	Texture::TextureFormat colorTextureFormat(
		Texture::Components::RGBA,
		Texture::Type::UnsignedNormalized,
		m_SampleDesc.Count,
		8, 8, 8, 8, 0, 0);
	std::shared_ptr<Texture> colorTexture = m_Device->CreateTexture2D(windowWidth, windowHeight,
		1, colorTextureFormat);

	m_RenderTarget->AttachTexture(RenderTarget::AttachmentPoint::Color0, colorTexture);
	m_RenderTarget->AttachTexture(RenderTarget::AttachmentPoint::DepthStencil, depthStencilTexture);

}

void Hikari::Dx11RenderWindow::OnPreRender(RenderEventArgs & e)
{

	if (m_bResizePending)
	{
		ResizeSwapChanBuffers(GetWindowWidth(), GetWindowHeight());
		m_bResizePending = false;
	}
	m_RenderTarget->Bind();
	base::OnPreRender(e);
}

void Hikari::Dx11RenderWindow::OnRender(RenderEventArgs & e)
{
	base::OnRender(e);

}

void Hikari::Dx11RenderWindow::OnPostRender(RenderEventArgs & e)
{
	base::OnPostRender(e);
}

void Hikari::Dx11RenderWindow::OnResize(ResizeEventArgs & e)
{
	//Delay one frame
	base::OnResize(e);
	m_bResizePending = true;
}

void Hikari::Dx11RenderWindow::OnTerminate(EventArgs & e)
{
	base::OnTerminate(e);
}

void Hikari::Dx11RenderWindow::ResizeSwapChanBuffers(uint32_t width, uint32_t height)
{
	width = max(width, 1);
	height = max(height, 1);
	m_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	m_pBackBuffer->Release();
	m_pSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pBackBuffer);
	m_RenderTarget->Resize(width, height);

}

void Hikari::Dx11RenderWindow::Present()
{
	m_RenderTarget->Bind();

	std::shared_ptr<TextureDX11> colorBuffer = std::dynamic_pointer_cast<TextureDX11>(m_RenderTarget->GetTexture(RenderTarget::AttachmentPoint::Color0));
	if (colorBuffer)
	{
		m_pDeviceContext->CopyResource(m_pBackBuffer, colorBuffer->GetTextureResource());
	}
	if (IsSync())
	{
		m_pSwapChain->Present(1, 0);
	}
	else
	{
		m_pSwapChain->Present(0, 0);

	}
}

std::shared_ptr<RenderTarget> Hikari::Dx11RenderWindow::GetRenderTarget()
{
	return m_RenderTarget;
}
