#include "GraphicsPCH.h"
#include "OpaquePass.h"
#include "Mesh.h"
#include "Material.h"
#include "PipelineState.h"
using namespace Hikari;
Hikari::OpaquePass::OpaquePass(Renderer* renderer,Scene * scene, PipelineState* pipeline)
	:BasePass(renderer,scene,pipeline)
{

}

Hikari::OpaquePass::~OpaquePass()
{
}


void Hikari::OpaquePass::Visit(Mesh & mesh)
{
	Material* pMaterial = mesh.GetMaterial();
	if (pMaterial && !pMaterial->IsTransparent())
	{
		mesh.Render(GetRenderEventArgs());
	}
}

void Hikari::OpaquePass::BindSamplerState(const std::string& paramName)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(paramName).Set(m_SamplerState);
}

void Hikari::OpaquePass::SetSampler(SamplerState * samp,const std::string& name)
{
	m_SamplerState = samp;
	BindSamplerState(name);
}

void Hikari::OpaquePass::SetLight(StructuredBuffer * buffer, const std::string & name)
{
	m_LightBuffer = buffer;
	BindLightBuffer(name);
}

void Hikari::OpaquePass::BindLightBuffer(const std::string & paramName)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(paramName).Set(m_LightBuffer);

}




