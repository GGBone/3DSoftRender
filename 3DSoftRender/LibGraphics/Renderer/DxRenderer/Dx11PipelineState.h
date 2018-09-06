#pragma once


#include "Dx11BlendState.h"
#include "Dx11RasterizerState.h"
#include "Dx11DepthStencilState.h"

namespace Hikari
{
	class PipelineStateDX11 : public PipelineState
	{
	public:
		PipelineStateDX11(ID3D11Device* pDevice);
		virtual ~PipelineStateDX11();

		void SetShader(Shader::ShaderType type, std::shared_ptr<Shader> pShader) override;
		std::shared_ptr<Shader> GetShader(Shader::ShaderType type) const override;
		const ShaderMap& GetShaders() const override;

		void SetBlendState(const BlendState& blendState) override;
		BlendState& GetBlendState() override;

		void SetRasterizerState(const RasterizerState& rasterizerState) override;
		RasterizerState& GetRasterizerState() override;

		void SetDepthStencilState(const DepthStencilState& depthStencilState) override;
		DepthStencilState& GetDepthStencilState() override;

		void SetRenderTarget(std::shared_ptr<RenderTarget> renderTarget) override;
		std::shared_ptr<RenderTarget> GetRenderTarget() const override;

		void bind() override;
		void unbind() override;
	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};

		ShaderMap m_Shaders;

		BlendStateDX11 m_BlendState;
		RasterizerStateDX11 m_RasterizerState;
		DepthStencilStateDX11 m_DepthStencilState;
		std::shared_ptr<RenderTarget> m_RenderTarget;
	};
}
