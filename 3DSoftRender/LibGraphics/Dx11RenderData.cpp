#if 0
#include "Dx11RenderLIB.h"
#include "Dx11RenderData.h"

Hikari::RendererData::RendererData(int width, int height, int numMultisamples, HWND handle)
	:mWindowHandle(handle),
	mWidth(width),
	mHeight(height)
{
	InitDevice();
}

Hikari::RendererData::~RendererData()
{
}

bool Hikari::RendererData::InitDevice()
{
	HRESULT hr = S_OK;
	D3D_DRIVER_TYPE	g_driverType;
	D3D_FEATURE_LEVEL  g_featureLevel;

	RECT rc;
	GetClientRect(mWindowHandle, &rc);
	mWidth = rc.right - rc.left;
	mHeight = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = mWidth;
	sd.BufferDesc.Height = mHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mWindowHandle;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &mDevice, &g_featureLevel, &mImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = mDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Create depth stencil texture
	/*D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = mWidth;
	descDepth.Height = mHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = mDevice->CreateTexture2D(&descDepth, NULL, &g_pDepthStencil);
	if (FAILED(hr))
		return hr;*/

	// Create the depth stencil view
	//D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	//ZeroMemory(&descDSV, sizeof(descDSV));
	//descDSV.Format = descDepth.Format;
	//descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//descDSV.Texture2D.MipSlice = 0;
	//hr = mDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, NULL);
	//if (FAILED(hr))
	//	return hr;

	mImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

	// Setup the viewport
	
	vp.Width = (FLOAT)mWidth;
	vp.Height = (FLOAT)mHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mImmediateContext->RSSetViewports(1, &vp);

	//Set Shader State
	return S_OK;
}

#endif