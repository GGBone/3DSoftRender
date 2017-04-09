#include "GraphicsPCH.h"
#include "RenderData.h"
#include "Dx11Renderer.h"
#include "Dx11RenderData.h"
#include "Dx11VertexBuffer.h"
#include "Dx11VertexShader.h"
#include "Dx11PixelShader.h"



using namespace Hikari;
DirectRenderer::DirectRenderer(int width, int height, int numMultisamples, HWND handle)
	:Renderer(new RendererData(width,height,handle))
{
	mData = new DirectRenderData(width, height, numMultisamples, handle);
	Initialize(width, height, Texture::Format(), Texture::Format(), numMultisamples);

}
DirectRenderer::~DirectRenderer()
{
	delete mData;
	Terminate();
}

void Hikari::DirectRenderer::Bind(const VertexFormat * vFormat)
{
}

void Hikari::DirectRenderer::Unbind(const VertexFormat * vFormat)
{
}

void Hikari::DirectRenderer::Enable(const VertexFormat * vFormat)
{
}

void DirectRenderer::SetViewport(int xPosition, int yPosition, int width,
	int height)
{
	
}
void DirectRenderer::Disable(const VertexFormat* vFormat)
{

}
void Hikari::DirectRenderer::Bind(const VertexBuffer * vBuffer)
{
}
void Hikari::DirectRenderer::Unbind(const VertexBuffer * vBuffer)
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
void DirectRenderer::ClearBackBuffer()
{
	FLOAT color[] = { 0,0,0,1 };
	mData->mImmediateContext->ClearRenderTargetView(mData->g_pRenderTargetView, color);
}

void DirectRenderer::ClearDepthBuffer()
{
	D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_DEPTH;
	mData->mImmediateContext->ClearDepthStencilView(mData->g_pDepthStencilView, clearFlag, 1, 0);
}
void DirectRenderer::ClearStencilBuffer()
{
	D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_STENCIL;
	mData->mImmediateContext->ClearDepthStencilView(mData->g_pDepthStencilView, clearFlag, 0, 0);
}
void DirectRenderer::ClearBuffers()
{
	ClearBackBuffer();
	//ClearDepthBuffer();
	//ClearStencilBuffer();
}
void DirectRenderer::ClearBackBuffer(int x, int y, int w, int h)
{
	D3D11_RECT rect;
	rect.left = (long)x;
	rect.top = (long)y;

	rect.right = (long)(x + w - 1);
	rect.bottom = (long)(y + h - 1);

	FLOAT clearColor[] = { mClearColor[0],mClearColor[1],mClearColor[2],mClearColor[3] };
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->ClearRenderTargetView((static_cast<DirectRenderData*>(mData))->g_pRenderTargetView, clearColor);

}
void Hikari::DirectRenderer::SetClearColor(const Float4 & color)
{
	mClearColor = color;
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

void Hikari::DirectRenderer::DisplayBackBuffer()
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
	//ClearBuffers();
	mData->mImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	mData->mImmediateContext->DrawIndexed(36,0,0);

	mData->g_pSwapChain->Present(0, 0);
}

void Hikari::DirectRenderer::Enable(const VertexBuffer * vBuffer)
{
	VertexBufferMap::iterator iter = mVertexBuffers.find(vBuffer);
	PdrVertexBuffer* pdrVBuffer;
	if (iter != mVertexBuffers.end())
	{
		pdrVBuffer = iter->second;
	}
	else
	{
		// Lazy creation.
		pdrVBuffer = new PdrVertexBuffer(this, vBuffer);
		mVertexBuffers[vBuffer] = pdrVBuffer;
	}

	pdrVBuffer->Enable(this, vBuffer->GetElementSize(), 0, 0);
}
void Hikari::DirectRenderer::Enable(const IndexBuffer * iBuffer)
{
	IndexBufferMap::iterator iter = mIndexBuffers.find(iBuffer);
	PdrIndexBuffer* pdrIBuffer;
	if (iter != mIndexBuffers.end())
	{
		pdrIBuffer = iter->second;
	}
	else
	{
		// Lazy creation.
		pdrIBuffer = new PdrIndexBuffer(this, iBuffer);
		mIndexBuffers[iBuffer] = pdrIBuffer;
	}

	pdrIBuffer->Enable(this, iBuffer->GetElementSize(), 0, 0);
}
void Hikari::DirectRenderer::Disable(const VertexBuffer * vBuffer)
{
}

void Hikari::DirectRenderer::Enable(const VertexShader * vShader, const ShaderParameters * vParam)
{
	PdrVertexShader* pvShader;
	VertexShaderMap::iterator iter = mVertexShaders.find(vShader);
	if (iter != mVertexShaders.end())
	{
		pvShader = iter->second;
	}
	else
	{
		pvShader = new PdrVertexShader(this, vShader);
		mVertexShaders[vShader] = pvShader;
		InputLayout* input = new InputLayout(this, pvShader, nullptr);
		mData->mImmediateContext->IASetInputLayout(input->GetInputLayout());
	}
	pvShader->Enable(this, vShader, vParam);
}

void Hikari::DirectRenderer::Enable(const PixelShader * pShader, const ShaderParameters * pParam)
{
	PdrPixelShader* ppShader;
	PixelShaderMap::iterator iter = mPixelShaders.find(pShader);
	if (iter != mPixelShaders.end())
	{
		ppShader = iter->second;
	}
	else
	{
		ppShader = new PdrPixelShader(this, pShader);
		mPixelShaders[pShader] = ppShader;
	}
	ppShader->Enable(this, pShader, pParam);
}
