#include "GraphicsPCH.h"
#include "Dx11RenderTarget.h"
using namespace Hikari;
Hikari::PdrRenderTarget::PdrRenderTarget(DirectRenderer * renderer, RenderTarget * renderTarget)
{
	mNumTargets = renderTarget->GetNumTargets();
	mWidth = renderTarget->GetWidth();
	mHeight = renderTarget->GetHeight();
	mFormat = renderTarget->GetFormat();
	mHasDepthStencil = renderTarget->HasDepthStencil();
	
	mColorTexture = new ID3D11Texture2D*[mNumTargets];
	for (int i = 0; i < mNumTargets; ++i)
	{
		Texture2D* texPtr = renderTarget->GetColorTexture(i);
		assert(renderer->InTexture2DMap(texPtr),"Dx11RenderTargetTarget");
		PdrTexture2D* dxColorTexture = new PdrTexture2D(renderer, texPtr);
		renderer->InsertInTexture2DMap(texPtr, dxColorTexture);
		mColorTexture[i] = dxColorTexture->mTexture;
		

		if (mHasDepthStencil)
		{
			Texture2D* depthStencil;
			PdrTexture2D* dxDepthStencil;
			depthStencil = renderTarget->GetDepthStencilTexture();
			dxDepthStencil = new PdrTexture2D(renderer, depthStencil);
			renderer->InsertInTexture2DMap(depthStencil, dxDepthStencil);
			mDepthStencilTexture = dxDepthStencil->mTexture;

		}
		else
		{
			mDepthStencilTexture = nullptr;
			mDepthStencil = nullptr;
		}
			
	}
}

void Hikari::PdrRenderTarget::Enable(DirectRenderer * renderer)
{
	renderer->mData->mImmediateContext->OMGetRenderTargets(1, &saveRenderView, &saveDepthView);
	renderer->mData->mImmediateContext->OMSetRenderTargets(1, &mRenderTarget, mDepthStencil);
}

void Hikari::PdrRenderTarget::ReadColor(int i, DirectRenderer * renderer, Texture2D *& texture)
{
	if (i < 0 || i >= mNumTargets)
	{
		assert(false, "Invalid target index.\n");
		return;
	}

	ID3D11DeviceContext* contex = renderer->mData->mImmediateContext;
	HRESULT hr;
	if (i == 0)
	{
		contex->OMGetRenderTargets(1, &saveRenderView, &saveDepthView);
	}
	contex->OMSetRenderTargets(1, &mRenderTarget, mDepthStencil);
	
}
