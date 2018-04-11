#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11RenderWindow.h"
#include "LightEffect.h"
#include "Graphics\VisualEffectInstance.h"
#include "OpaquePass.h"
#include "TransparentPass.h"

#include "Graphics\Scene.h"
#include "Graphics\RenderTarget.h"
#include "Graphics\PipelineState.h"
#include "Graphics\SamplerState.h"
#include "ClearRenderTargetPass.h"
#include "LightPass.h"
#include "Graphics\BlendState.h"
#include "Graphics\DepthStencilState.h"


using namespace Hikari;
Hikari::LightEffect::LightEffect(std::shared_ptr<RenderWindow> rWindow, std::shared_ptr<Renderer> renderer,std::shared_ptr<Scene> scene,std::vector<Light>& lights)
{
	std::shared_ptr<Shader> vertexShader = renderer->CreateShader();
	std::shared_ptr<Shader> pixelShader = renderer->CreateShader();
	std::shared_ptr<Shader> lightPixelShaser = renderer->CreateShader();

	std::shared_ptr<OpaquePass> opaquePass;
	//std::shared_ptr<ClearRenderTargetPass> clearPass;
	std::shared_ptr<TransparentPass> transparentPass;
	std::shared_ptr<LightsPass> lightPassFont;

	BlendState::BlendMode alphaBlending(true, false, BlendState::BlendFactor::SrcAlpha, BlendState::BlendFactor::OneMinusSrcAlpha);
	BlendState::BlendMode additiveBlending(true, false, BlendState::BlendFactor::One, BlendState::BlendFactor::One);

	DepthStencilState::DepthMode disableDepthWrites(true, DepthStencilState::DepthWrite::Disable);
	DepthStencilState::DepthMode disableDepthTesting(false);

	vertexShader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "VS_main", "latest");
	pixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_NoLight", "latest");
	lightPixelShaser->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_light", "latest");

	std::shared_ptr<StructuredBuffer> lightBuffer = renderer->CreateStructuredBuffer(lights, CPUAccess::Write);

	pixelShader->GetShaderParameterByName("Lights").Set(lightBuffer);

	//Opaque Pass
	{
		std::shared_ptr<PipelineState> g_OpaquePipeline = renderer->CreatePipelineState();
		g_OpaquePipeline->SetShader(Shader::VertexShader, vertexShader);
		g_OpaquePipeline->SetShader(Shader::PixelShader, pixelShader);

		g_OpaquePipeline->SetRenderTarget(rWindow->GetRenderTarget());
		g_OpaquePipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::Front);

		std::shared_ptr<SamplerState> sampler = renderer->CreateSamplerState();
		sampler->SetFilter(SamplerState::MinFilter::MinLinear, SamplerState::MagFilter::MagLinear, SamplerState::MipFilter::MipLinear);
		sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat);

		opaquePass = std::make_shared<OpaquePass>(renderer, scene, g_OpaquePipeline);
		opaquePass->SetSampler(sampler, "LinearRepeatSampler");

	}

	//Transparent Pass
	{

		std::shared_ptr<PipelineState> transparentPipeline = renderer->CreatePipelineState();
		transparentPipeline->SetShader(Shader::VertexShader, vertexShader);
		transparentPipeline->SetShader(Shader::PixelShader, pixelShader);
		transparentPipeline->GetBlendState().SetBlendMode(alphaBlending);
		transparentPipeline->GetDepthStencilState().SetDepthMode(disableDepthWrites);
		transparentPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::None);
		transparentPipeline->SetRenderTarget(rWindow->GetRenderTarget());
		transparentPass = std::make_shared<TransparentPass>(renderer, scene, transparentPipeline);

	}

	//LightFontPass
	{
		std::shared_ptr<Scene> sphere = renderer->CreateSphere(1.0f);
		std::shared_ptr<Scene> arrow = renderer->CreateArrow();
		std::shared_ptr<Scene> cone = renderer->CreateCylinder(0.0f, 1.0f, 1.0f, AVector(0, 0, 1));
		std::shared_ptr<PipelineState> lightFontPipeline = renderer->CreatePipelineState();
		lightFontPipeline->SetShader(Shader::VertexShader, vertexShader);
		lightFontPipeline->SetShader(Shader::PixelShader, lightPixelShaser);
		lightFontPipeline->SetRenderTarget(rWindow->GetRenderTarget());
		lightFontPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::Front);
		lightFontPipeline->GetDepthStencilState().SetDepthMode(disableDepthWrites);
		lightFontPipeline->GetBlendState().SetBlendMode(alphaBlending);

		lightPassFont = std::make_shared<LightsPass>(renderer,lights,scene,cone,arrow,lightFontPipeline);
	}



	std::shared_ptr<VisualTechnique> forwardTechnique = std::make_shared<VisualTechnique>();

	forwardTechnique->AddPass(opaquePass);
	/*forwardTechnique->AddPass(transparentPass);
	forwardTechnique->AddPass(lightPassFont);*/
	InsertTechnique(forwardTechnique);

}

Hikari::LightEffect::~LightEffect()
{
}

std::shared_ptr<VisualEffectInstance> Hikari::LightEffect::CreateInstance()
{

	std::shared_ptr<VisualEffectInstance> instance = std::make_shared<VisualEffectInstance>(shared_from_this(), 0);
	return instance;
}
