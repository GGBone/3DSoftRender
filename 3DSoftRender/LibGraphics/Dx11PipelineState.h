#pragma once

#include "Graphics\PipelineState.h"

#include "Graphics\Dx11BlendState.h"
#include "Graphics\Dx11RasterizerState.h"
#include "Graphics\Dx11DepthStencilState.h"
#include "Graphics\RenderTarget.h"
namespace Hikari
{
	class PipelineStateDX11 : public PipelineState
	{
	public:
		PipelineStateDX11(ID3D11Device* pDevice);
		virtual ~PipelineStateDX11();

		virtual void SetShader(Shader::ShaderType type, std::shared_ptr<Shader> pShader) override;
		virtual std::shared_ptr<Shader> GetShader(Shader::ShaderType type) const override;
		virtual const ShaderMap& GetShaders() const override;

		virtual void SetBlendState(const BlendState& blendState) override;
		virtual BlendState& GetBlendState() override;

		virtual void SetRasterizerState(const RasterizerState& rasterizerState) override;
		virtual RasterizerState& GetRasterizerState() override;

		virtual void SetDepthStencilState(const DepthStencilState& depthStencilState) override;
		virtual DepthStencilState& GetDepthStencilState() override;

		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> renderTarget) override;
		virtual std::shared_ptr<RenderTarget> GetRenderTarget() const override;

		virtual void Bind() override;
		virtual void UnBind() override;
	protected:

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;

		ShaderMap m_Shaders;

		BlendStateDX11 m_BlendState;
		RasterizerStateDX11 m_RasterizerState;
		DepthStencilStateDX11 m_DepthStencilState;
		std::shared_ptr<RenderTarget> m_RenderTarget;
	};
}