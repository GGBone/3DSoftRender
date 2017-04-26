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
	Shader* lightPixelShader = renderer->CreateShader();
	Shader* lightPickingPixelShader = renderer->CreateShader();
	Shader* unlitPixelShader = renderer->CreateShader();
	Shader* germetryPixelShader = renderer->CreateShader();
	Shader* debugTexturePixelShader = renderer->CreateShader();
	Shader* debugDepthTexturePixelShader = renderer->CreateShader();
	Shader* debugStencilTexturePixelShader = renderer->CreateShader();
	Shader* deferedLightingPixelShader = renderer->CreateShader();
	Shader* lightCullingComputeShader = renderer->CreateShader();
	Shader* computeFrustrumsComputeShader = renderer->CreateShader();
	Shader* forwardPlusPixelShader = renderer->CreateShader();

	
	vertexShader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "VS_main", "latest");
	pixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_main", "latest");
	lightPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_light", "latest");
	lightPickingPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/DeferredRendering.hlsl", Shader::ShaderMacros(), "PS_LightPicking", "latest");
	unlitPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_unlit", "latest");
	germetryPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/DeferredRendering.hlsl", Shader::ShaderMacros(), "PS_Geometry", "latest");
	debugTexturePixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/DeferredRendering.hlsl", Shader::ShaderMacros(), "PS_DebugTexture", "latest");
	debugDepthTexturePixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/DeferredRendering.hlsl", Shader::ShaderMacros(), "PS_DebugDepthTexture", "latest");
	debugStencilTexturePixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/DeferredRendering.hlsl", Shader::ShaderMacros(), "PS_DebugStencilTexture", "latest");
	deferedLightingPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/DeferredRendering.hlsl", Shader::ShaderMacros(), "PS_DeferredLighting", "latest");
	lightCullingComputeShader->LoadShaderFromFile(Shader::ComputeShader, "../Assets/shaders/ForwardPlusRendering.hlsl", Shader::ShaderMacros(), "CS_main", "cs_5_0");
	computeFrustrumsComputeShader->LoadShaderFromFile(Shader::ComputeShader, "../Assets/shaders/ForwardPlusRendering.hlsl", Shader::ShaderMacros(), "CS_ComputeFrustums", "cs_5_0");
	forwardPlusPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardPlusRendering.hlsl", Shader::ShaderMacros(), "PS_main", "latest");
	
	Texture::TextureFormat lightPickingTextureFormat(
		Texture::Components::R,
		Texture::Type::UnsignedInteger,
		1,
		16, 0, 0, 0, 0, 0
	);

	Texture* g_LightPickingTexture = renderer->CreateTexture2D(renderer->mData->mWidth, renderer->mData->mHeight, 1,
		lightPickingTextureFormat, CPUAccess::Read);

	Texture* lightPickingTexure = renderer->CreateTexture2D(renderer->mData->mWidth, renderer->mData->mHeight,
		1, lightPickingTextureFormat);

	Texture::TextureFormat lightPickingDepthStencilTextureFormat(
		Texture::Components::DepthStencil,
		Texture::Type::UnsignedNormalized,
		1,
		0, 0, 0, 0, 24, 8);
	Texture* lightPickingDepthStencilTexture = renderer->CreateTexture2D(
		renderer->mData->mWidth, renderer->mData->mHeight, 1, lightPickingDepthStencilTextureFormat);


	RenderTarget* g_LightPickingRenderTarget = renderer->CreateRenderTarget();
	g_LightPickingRenderTarget->AttachTexture(RenderTarget::AttachmentPoint::Color0,
		lightPickingTexure);

	g_LightPickingRenderTarget->AttachTexture(RenderTarget::AttachmentPoint::DepthStencil,
		lightPickingDepthStencilTexture);

	StructuredBuffer* lightBuffer =  ((Renderer*)renderer)->CreateStructuredBuffer(lights, CPUAccess::Write);

	pixelShader->GetShaderParameterByName("Lights").Set(lightBuffer);

	PipelineState* g_OpaquePipeline = renderer->CreatePipelineState();
	g_OpaquePipeline->SetShader(Shader::VertexShader, vertexShader);
	g_OpaquePipeline->SetShader(Shader::PixelShader, pixelShader);
	g_OpaquePipeline->SetRenderTarget(renderer->mData->renderTarget);


	DepthStencilState::DepthMode disableDepthWrite(true, DepthStencilState::DepthWrite::Disable);
	BlendState::BlendMode alphaBleding(true, false, BlendState::BlendFactor::SrcAlpha, BlendState::BlendFactor::OneMinusBlendFactor);
	PipelineState* g_LightPipelineFront = renderer->CreatePipelineState();
	g_LightPipelineFront->SetShader(Shader::VertexShader, vertexShader);
	g_LightPipelineFront->SetShader(Shader::PixelShader, lightPixelShader);
	g_LightPipelineFront->SetRenderTarget(renderer->mData->renderTarget);
	g_LightPipelineFront->GetRasterizerState().SetCullMode(RasterizerState::CullMode::Back);
	g_LightPipelineFront->GetDepthStencilState().SetDepthMode(disableDepthWrite);
	g_LightPipelineFront->GetBlendState().SetBlendMode(alphaBleding);

	SamplerState* sampler = renderer->CreateSamplerState();
	sampler->SetFilter(SamplerState::MinFilter::MinLinear, SamplerState::MagFilter::MagLinear, SamplerState::MipFilter::MipLinear);
	sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat);

	OpaquePass* opaquePass = new OpaquePass(renderer,scene,g_OpaquePipeline);
	opaquePass->SetSampler(sampler,"LinearRepeatSampler");
	ClearRenderTargetPass* clearPass = new ClearRenderTargetPass(renderer->mData->renderTarget);

	LightsPass* lightPass = new LightsPass(renderer, lights,scene, scene, scene,g_LightPipelineFront);

	VisualTechnique* forwardTechnique = new VisualTechnique();
	

	forwardTechnique->AddPass(clearPass);
	forwardTechnique->AddPass(opaquePass);
	forwardTechnique->AddPass(lightPass);
	InsertTechnique(forwardTechnique);

	//InsertTechnique(techique2);
}

Hikari::LightEffect::~LightEffect()
{
}

VisualEffectInstance * Hikari::LightEffect::CreateInstance() const
{

	VisualEffectInstance* instance = new VisualEffectInstance(this,0);
	return instance;
}
