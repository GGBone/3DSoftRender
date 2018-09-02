#pragma once
#include "GraphicsLib.h"
#include "AbstractPass.h"
#include "Base/Float4.h"
#include "SceneGraph/ClearFlag.h"

namespace Hikari
{
	class Float4;
	class RenderTarget;
	class Texture;

	class ClearRenderTargetPass : public AbstractPass
	{
	public:
		ClearRenderTargetPass(std::shared_ptr<RenderTarget> renderTarget,
		                      ClearFlags clearFlags = ClearFlags::All,
		                      const Float4& color = Float4(0, 0, 0, 0),
		                      float depth = 1.0f,
		                      uint8_t stencil = 0);
		ClearRenderTargetPass(std::shared_ptr<Texture> texture,
		                      ClearFlags clearFlags = ClearFlags::All,
		                      const Float4& color = Float4(0, 0, 0, 0),
		                      float depth = 1.0f,
		                      uint8_t stencil = 0);
		virtual ~ClearRenderTargetPass() = default;

		void Render(RenderEventArgs& e) override;

	private:
		std::shared_ptr<RenderTarget> m_RenderTarget{};

		std::shared_ptr<RenderEventArgs> m_RenderEventArgs{};

		std::shared_ptr<Texture> m_Texture{};

		ClearFlags m_ClearFlags{};
		Float4 m_ClearColor;
		float m_ClearDepth;

		uint8_t m_ClearStencil{};
	};
}
