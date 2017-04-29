#include "GraphicsPCH.h"
#include "LightEffect.h"
#include "OpaquePass.h"
#include "Scene.h"
#include "RenderTarget.h"
#include "PipelineState.h"
#include "SamplerState.h"
#include "ClearRenderTargetPass.h"
#include "LightPass.h"
#include "BlendState.h"
#include "DepthStencilState.h"
using namespace Hikari;
Hikari::LightEffect::LightEffect(DirectRenderer* renderer,Scene* scene,std::vector<Light>& lights)
{
	
	Shader* vertexShader = renderer->CreateShader();
	Shader* pixelShader = renderer->CreateShader();

	vertexShader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "VS_main", "latest");
	pixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_main", "latest");

	StructuredBuffer* lightBuffer =  ((Renderer*)renderer)->CreateStructuredBuffer(lights, CPUAccess::Write);

	pixelShader->GetShaderParameterByName("Lights").Set(lightBuffer);

	PipelineState* g_OpaquePipeline = renderer->CreatePipelineState();
	g_OpaquePipeline->SetShader(Shader::VertexShader, vertexShader);
	g_OpaquePipeline->SetShader(Shader::PixelShader, pixelShader);
	g_OpaquePipeline->SetRenderTarget(renderer->mData->renderTarget);

	SamplerState* sampler = renderer->CreateSamplerState();
	sampler->SetFilter(SamplerState::MinFilter::MinLinear, SamplerState::MagFilter::MagLinear, SamplerState::MipFilter::MipLinear);
	sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat);

	OpaquePass* opaquePass = new OpaquePass(renderer,scene,g_OpaquePipeline);
	opaquePass->SetSampler(sampler,"LinearRepeatSampler");
	ClearRenderTargetPass* clearPass = new ClearRenderTargetPass(renderer->mData->renderTarget);


	VisualTechnique* forwardTechnique = new VisualTechnique();
	

	forwardTechnique->AddPass(clearPass);
	forwardTechnique->AddPass(opaquePass);

	InsertTechnique(forwardTechnique);

}

Hikari::LightEffect::~LightEffect()
{
}

VisualEffectInstance * Hikari::LightEffect::CreateInstance() const
{

	VisualEffectInstance* instance = new VisualEffectInstance(this,0);
	return instance;
}
