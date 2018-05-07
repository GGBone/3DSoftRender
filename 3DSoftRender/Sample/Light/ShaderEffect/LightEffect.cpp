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
Hikari::LightEffect::LightEffect(std::shared_ptr<RenderWindow> rWindow, std::shared_ptr<Renderer> renderer, 
	vector<std::shared_ptr<Scene>> scene, vector<shared_ptr<Scene>> transScene)
{
	auto vertexShader = renderer->CreateShader();
	auto pixelShader = renderer->CreateShader();
	auto lightPixelShaser = renderer->CreateShader();
	auto oitPixelShader = renderer->CreateShader();

	auto forwardTechnique = std::make_shared<VisualTechnique>();

	//std::shared_ptr<OpaquePass> opaquePass;
	std::shared_ptr<LightsPass> lightPass;
	std::shared_ptr<TransparentPass> transparentPass;
	std::shared_ptr<LightsPass> lightPassFont;

	BlendState::BlendMode alphaBlending(true, false, BlendState::BlendFactor::SrcAlpha, BlendState::BlendFactor::OneMinusSrcAlpha);
	BlendState::BlendMode additiveBlending(true, false, BlendState::BlendFactor::One, BlendState::BlendFactor::One);

	DepthStencilState::DepthMode disableDepthWrites(true, DepthStencilState::DepthWrite::Disable);
	DepthStencilState::DepthMode disableDepthTesting(false);

	vertexShader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "VS_main", "latest");
	pixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_main", "latest");
	lightPixelShaser->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl", Shader::ShaderMacros(), "PS_light", "latest");
	oitPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/OIT/oit.hlsl", Shader::ShaderMacros(), "PS_main", "latest");
	//Opaque Pass
	{
		std::shared_ptr<PipelineState> g_OpaquePipeline = renderer->CreatePipelineState();
		g_OpaquePipeline->SetShader(Shader::VertexShader, vertexShader);
		g_OpaquePipeline->SetShader(Shader::PixelShader, lightPixelShaser);
		
		g_OpaquePipeline->SetRenderTarget(rWindow->GetRenderTarget());
		g_OpaquePipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::Front);

		std::shared_ptr<SamplerState> sampler = renderer->CreateSamplerState();
		sampler->SetFilter(SamplerState::MinFilter::MinLinear, SamplerState::MagFilter::MagLinear, SamplerState::MipFilter::MipLinear);
		sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat);

		auto iter = scene.begin();
		for (; iter != scene.end(); iter++)
		{
			lightPass = std::make_shared<LightsPass>(renderer, *iter, g_OpaquePipeline);
			lightPass->SetSampler(sampler, "LinearRepeatSampler");
			forwardTechnique->AddPass(lightPass);
			lightPass.reset();
		}
		sampler.reset();
		g_OpaquePipeline.reset();
	}

	//OIT Pass
	{
		auto oitPipeline = renderer->CreatePipelineState();

	}

	//Transparent Pass
	{

		std::shared_ptr<PipelineState> transparentPipeline = renderer->CreatePipelineState();
		transparentPipeline->SetShader(Shader::VertexShader, vertexShader);
		transparentPipeline->SetShader(Shader::PixelShader, lightPixelShaser);
		transparentPipeline->GetBlendState().SetBlendMode(alphaBlending);
		transparentPipeline->GetDepthStencilState().SetDepthMode(disableDepthWrites);
		transparentPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::None);
		transparentPipeline->SetRenderTarget(rWindow->GetRenderTarget());

		auto iter = transScene.begin();
		for (; iter != transScene.end(); iter++)
		{
			transparentPass = std::make_shared<TransparentPass>(renderer, *iter, transparentPipeline);
			forwardTechnique->AddPass(transparentPass);
			transparentPass.reset();
		}
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

		//lightPassFont = std::make_shared<LightsPass>(renderer,scene,lightFontPipeline);
	}


	InsertTechnique(forwardTechnique);

	vertexShader.reset();
	pixelShader.reset();
	lightPixelShaser.reset();
	lightPass.reset();
	transparentPass.reset();
	lightPassFont.reset();
}

Hikari::LightEffect::~LightEffect()
{
	
}

std::shared_ptr<VisualEffectInstance> Hikari::LightEffect::CreateInstance()
{

	std::shared_ptr<VisualEffectInstance> instance = std::make_shared<VisualEffectInstance>(shared_from_this(), 0);
	return instance;
}
