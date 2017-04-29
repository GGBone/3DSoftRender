#pragma once
#include "GraphicsLib.h"
#include "AbstractPass.h"
#include "Float4.h"
#include "ClearFlag.h"
namespace Hikari
{
	class Float4;
	class RenderTarget;
	class Texture;

	class ClearRenderTargetPass : public AbstractPass
	{
	public:
		ClearRenderTargetPass(RenderTarget* renderTarget,
			ClearFlags clearFlags = ClearFlags::All,
			const Float4& color = Float4(0,0,0,0),
			float depth = 1.0f,
			uint8_t stencil = 0);
		ClearRenderTargetPass(Texture* texture,
			ClearFlags clearFlags = ClearFlags::All,
			const Float4& color = Float4(0, 0, 0, 0),
			float depth = 1.0f,
			uint8_t stencil = 0);
		virtual ~ClearRenderTargetPass();

		virtual void Render(RenderEventArgs& e);

	private:
		RenderTarget* m_RenderTarget;
		Texture* m_Texture;
		ClearFlags m_ClearFlags;
		Float4  m_ClearColor;
		float m_ClearDepth;
		uint8_t m_ClearStencil;
	};

}