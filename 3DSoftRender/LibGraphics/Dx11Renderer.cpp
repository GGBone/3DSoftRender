#include "GraphicsPCH.h"
#include "RenderData.h"
#include "Dx11Renderer.h"
#include "Dx11RenderData.h"
#include "Dx11VertexBuffer.h"
#include "Dx11VertexShader.h"
#include "Dx11PixelShader.h"



using namespace Hikari;
DirectRenderer::DirectRenderer(DirectRenderData* input, int width, int height, Texture::Format colorFormat, Texture::Format depthStencilFormat, int numMultisamples)
:
	Renderer((RendererData*)input)
{
	Initialize(width, height, Texture::Format(), Texture::Format(), numMultisamples);
	mData = input;
	//Set all the State 
	//To-Do
}
DirectRenderer::~DirectRenderer()
{
	delete mData;
	Terminate();
}

void DirectRenderer::SetViewport(int xPosition, int yPosition, int width,
	int height)
{
	
}
void DirectRenderer::GetViewport(int& xPosition, int& yPosition, int& width,
	int& height) const
{
	D3D11_VIEWPORT* viewports = 0;
	UINT* numofViewports = 0;
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->RSGetViewports(numofViewports, viewports);
	if (viewports == nullptr)
		MessageBoxA(0, "ERROR", "GetViewportError", MB_OK);
	xPosition = viewports[0].TopLeftX;
	yPosition = mHeight - viewports[0].Height - viewports[0].TopLeftY;
	width = viewports[0].Width;
	height = viewports[0].Height;
}

void DirectRenderer::SetDepthRange(float zMin, float zMax)
{
	D3D11_VIEWPORT* viewports = 0;
	UINT* numofViewports = 0;
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->RSGetViewports(numofViewports, viewports);
	if (viewports == nullptr)
		MessageBoxA(0, "ERROR", "GetViewportError", MB_OK);
	zMin = viewports[0].MinDepth;
	zMax = viewports[0].MaxDepth;
}

void DirectRenderer::GetDepthRange(float& zMin, float& zMax) const
{
	D3D11_VIEWPORT* viewports = 0;
	UINT* numofViewports;
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->RSGetViewports(numofViewports, viewports);
	if (viewports == nullptr)
		MessageBoxA(0, "ERROR", "GetViewportError", MB_OK);
	zMin = viewports[0].MinDepth;
	zMax = viewports[0].MaxDepth;
}
void Hikari::DirectRenderer::Resize(int width, int height)
{
}
//// Support for clearing the color, depth, and stencil buffers.
void DirectRenderer::ClearColorBuffer()
{
	FLOAT color[] = { 0,0,0,1 };
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->ClearRenderTargetView((static_cast<DirectRenderData*>(mData))->g_pRenderTargetView, color);
}

void DirectRenderer::ClearDepthBuffer()
{
	/*D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_DEPTH;
	mData->mImmediateContext->ClearDepthStencilView(mData->g_pDepthStencilView, clearFlag, 1, 0);*/
}
void DirectRenderer::ClearStencilBuffer()
{
	/*D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_STENCIL;
	mData->mImmediateContext->ClearDepthStencilView(mData->g_pDepthStencilView, clearFlag, 0, 0);*/
}
void DirectRenderer::ClearBuffers()
{
	ClearColorBuffer();
	ClearDepthBuffer();
	ClearStencilBuffer();
}
void DirectRenderer::ClearColorBuffer(int x, int y, int w, int h)
{
	D3D11_RECT rect;
	rect.left = (long)x;
	rect.top = (long)y;

	rect.right = (long)(x + w - 1);
	rect.bottom = (long)(y + h - 1);

	FLOAT clearColor[] = { mClearColor[0],mClearColor[1],mClearColor[2],mClearColor[3] };
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->ClearRenderTargetView((static_cast<DirectRenderData*>(mData))->g_pRenderTargetView, clearColor);

}
void Hikari::DirectRenderer::ClearDepthBuffer(int x, int y, int w, int h)
{
}
void Hikari::DirectRenderer::ClearStencilBuffer(int x, int y, int w, int h)
{
}
void Hikari::DirectRenderer::ClearBuffers(int x, int y, int w, int h)
{
}
void Hikari::DirectRenderer::DisplayColorBuffer()
{
}
void Hikari::DirectRenderer::SetColorMask(bool allowRed, bool allowGreen, bool allowBlue, bool allowAlpha)
{
}
bool Hikari::DirectRenderer::PreDraw()
{
	return false;
}
void Hikari::DirectRenderer::PostDraw()
{
}
void Hikari::DirectRenderer::Draw(const unsigned char * screenBuffer, bool reflectY)
{
}
void Hikari::DirectRenderer::Draw(int x, int y, const Float4 & color, const std::string & message)
{
}

void DirectRenderer::DrawPrimitive(const Visual * visual)
{
	static bool InitTemp = false;
	static PdrVertexShader* pdrVShader;
	static PdrPixelShader* pdrPShader;
	if (!InitTemp)
	{
		const VertexBuffer* vertexBuffer = visual->GetVertexBuffer();
		//Bind Vertex and Pixel Shader in pileline
		const VisualPass* pass = visual->GetVisualPass();

		VertexShader* vShader = pass->GetVertexShader();
		PixelShader* pShader = pass->GetPixelShader();
		PdrVertexBuffer* pdrVertex;
		ID3D11InputLayout* inputLayout = pass->GetInputLayout();
		VertexShaderMap::iterator iterV = mVertexShaders.find(vShader);
		PixelShaderMap::iterator iterP = mPixelShaders.find(pShader);

		if (iterV != mVertexShaders.end())
		{
			pdrVShader = iterV->second;
		}
		else

		{
			pdrVShader = new PdrVertexShader(this, vShader);

			mVertexShaders[vShader] = pdrVShader;
			D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};
			UINT totalLayoutElements = ARRAYSIZE(solidColorLayout);
			HRESULT hr = (static_cast<DirectRenderData*>(mData))->mDevice->CreateInputLayout(solidColorLayout, totalLayoutElements, pdrVShader->vsBuffer->GetBufferPointer(),
				pdrVShader->vsBuffer->GetBufferSize(), &inputLayout);
		}
		if (iterP != mPixelShaders.end())
		{
			pdrPShader = iterP->second;
		}
		else
		{
			pdrPShader = new PdrPixelShader(this, pShader);
			mPixelShaders[pShader] = pdrPShader;
		}

		//temp will be package in class


		//Bind VertexBuffer
		if (mVertexBuffers.find(vertexBuffer) == mVertexBuffers.end())
		{
			pdrVertex = new PdrVertexBuffer(this, vertexBuffer);
			mVertexBuffers[vertexBuffer] = pdrVertex;
		}
		(static_cast<DirectRenderData*>(mData))->mImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		(static_cast<DirectRenderData*>(mData))->mImmediateContext->IASetInputLayout(inputLayout);
		InitTemp = true;
	}

	ClearBuffers();

	(static_cast<DirectRenderData*>(mData))->mImmediateContext->VSSetShader(pdrVShader->mVShader, NULL, 0);
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->PSSetShader(pdrPShader->mPShader, NULL, 0);
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->Draw(6, 0);
	(static_cast<DirectRenderData*>(mData))->g_pSwapChain->Present(0, 0);
}
