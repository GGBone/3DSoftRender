#include "GraphicsPCH.h"
#include "Dx11PipelineState.h"

using namespace Hikari;
PipelineStateDX11::PipelineStateDX11(ID3D11Device* pDevice)
	: m_pDevice(pDevice)
	, m_BlendState(pDevice)
	, m_RasterizerState(pDevice)
	, m_DepthStencilState(pDevice)
	, m_RenderTarget(nullptr)
{
	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}

PipelineStateDX11::~PipelineStateDX11()
{

}

void PipelineStateDX11::SetShader(Shader::ShaderType type,Shader* pShader)
{
	m_Shaders[type] = pShader;
}

Shader* PipelineStateDX11::GetShader(Shader::ShaderType type) const
{
	ShaderMap::const_iterator iter = m_Shaders.find(type);
	if (iter != m_Shaders.end())
	{
		return iter->second;
	}

	return nullptr;
}

const PipelineState::ShaderMap& PipelineStateDX11::GetShaders() const
{
	return m_Shaders;
}

void PipelineStateDX11::SetBlendState(const BlendState& blendState)
{
	m_BlendState = dynamic_cast<const BlendStateDX11&>(blendState);
}

BlendState& PipelineStateDX11::GetBlendState()
{
	return m_BlendState;
}

void PipelineStateDX11::SetRasterizerState(const RasterizerState& rasterizerState)
{
	m_RasterizerState = dynamic_cast<const RasterizerStateDX11&>(rasterizerState);
}

RasterizerState& PipelineStateDX11::GetRasterizerState()
{
	return m_RasterizerState;
}

void PipelineStateDX11::SetDepthStencilState(const DepthStencilState& depthStencilState)
{
	m_DepthStencilState = dynamic_cast<const DepthStencilStateDX11&>(depthStencilState);
}

DepthStencilState& PipelineStateDX11::GetDepthStencilState()
{
	return m_DepthStencilState;
}

void PipelineStateDX11::SetRenderTarget(RenderTarget* renderTarget)
{
	m_RenderTarget = renderTarget;
}

RenderTarget* PipelineStateDX11::GetRenderTarget() const
{
	return m_RenderTarget;
}

void PipelineStateDX11::Bind()
{
	if (m_RenderTarget)
	{
		m_RenderTarget->Bind();
	}

	m_BlendState.Bind();
	m_RasterizerState.Bind();
	m_DepthStencilState.Bind();

	for (auto shader : m_Shaders)
	{
		Shader* pShader = shader.second;
		if (pShader)
		{
			pShader->Bind();
		}
	}
}

void PipelineStateDX11::UnBind()
{
	if (m_RenderTarget)
	{
		m_RenderTarget->UnBind();
	}

	for (auto shader : m_Shaders)
	{
		Shader* pShader = shader.second;
		if (pShader)
		{
			pShader->UnBind();
		}
	}
}