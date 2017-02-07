#pragma once
#include "Dx11RenderLIB.h"
namespace Hikari

{
	class DirectRenderData : public RendererData
	{
	public:
		DirectRenderData(int width,int height,int numMultisamples,HWND handle);
		~DirectRenderData();
		
		ID3D11Device* mDevice = NULL;
		ID3D11DeviceContext* mImmediateContext = NULL;
		IDXGISwapChain* g_pSwapChain = NULL;
		ID3D11RenderTargetView* g_pRenderTargetView = NULL;
		ID3D11Texture2D* g_pDepthStencil = NULL;
		ID3D11DepthStencilView* g_pDepthStencilView = NULL;

		ID3D11InputLayout* g_pVertexLayout = NULL;
		ID3D11InputLayout*	g_pCurveLayout = NULL;

		ID3D11Buffer*	g_pCBNeverChanges = NULL;
		
		ID3D11Buffer*	g_pCBChangeOnResize = NULL;
		ID3D11Buffer*	g_pCBChangesEveryFrame = NULL;

		ID3D11Buffer*	g_pVertexBuffer;
		ID3D11Buffer*	g_pIndexBuffer;

		ID3D11Buffer*	g_pCurveVertexBuffer;

		ID3D11SamplerState*	g_pSamplerLinear = NULL;

		D3D11_VIEWPORT vp;

	private:
		bool InitDevice();
	};
}