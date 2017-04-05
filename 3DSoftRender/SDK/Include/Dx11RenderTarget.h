#pragma once
#include "RenderTarget.h"
#include "Dx11RenderLIB.h"
namespace Hikari
{
	class DirectRenderer;
	class PdrRenderTarget
	{
	public:
		PdrRenderTarget(DirectRenderer* renderer, RenderTarget* renderTarget);
		~PdrRenderTarget();
		void Enable(DirectRenderer* renderer);
		void Disable(DirectRenderer* renderer);
		void ReadColor(int i, DirectRenderer* renderer, Texture2D*& texture);
	private:
		int mNumTargets;
		UINT mWidth, mHeight;
		Texture::Format mFormat;
		bool mHasDepthStencil;

		ID3D11RenderTargetView* mRenderTarget;
		ID3D11Texture2D** mColorTexture;

		ID3D11DepthStencilView* mDepthStencil;
		ID3D11Texture2D* mDepthStencilTexture;

		ID3D11RenderTargetView* saveRenderView;
		ID3D11DepthStencilView* saveDepthView;
	};

}