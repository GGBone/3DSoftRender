#include "LightEffect.h"
#include "SceneGraph/VisualEffectInstance.h"
#include "SceneGraph/VisualTechnique.h"
#include "Renderer/DxRenderer/Dx11Renderer.h"
#include "TransparentPass.h"
#include "SceneGraph/Scene.h"
#include "Shader/Shader.h"
#include "Resource/PipelineState.h"
#include "Resource/SamplerState.h"
#include "Renderer/RenderWindow.h"
#include "Resource/RasterizerState.h"
#include "Resource/BlendState.h"
#include "Resource/DepthStencilState.h"
#include "LightPass.h"
#include "OITPass.h"

using namespace Hikari;

LightEffect::LightEffect(std::shared_ptr<RenderWindow> rWindow, std::shared_ptr<Renderer> renderer,
	vector<std::shared_ptr<Scene>> scene, vector<shared_ptr<Scene>> transScene)
{
	auto vertexShader = renderer->CreateShader();
	auto pixelShader = renderer->CreateShader();
	auto lightPixelShaser = renderer->CreateShader();
	auto oitPixelShader = renderer->CreateShader();

	auto forwardTechnique = std::make_shared<VisualTechnique>();

	//std::shared_ptr<OpaquePass> opaquePass;
	std::shared_ptr<LightsPass> light_pass;
	std::shared_ptr<TransparentPass> transparent_pass;
	std::shared_ptr<LightsPass> light_pass_font;

	const BlendState::BlendMode alpha_blending(true, false, BlendState::BlendFactor::SrcAlpha,
		BlendState::BlendFactor::OneMinusSrcAlpha);
	const BlendState::BlendMode additive_blending(true, false, BlendState::BlendFactor::One,
		BlendState::BlendFactor::One);

	const DepthStencilState::DepthMode disable_depth_writes(true, DepthStencilState::DepthWrite::Disable);
	// ReSharper disable once CppDeclaratorNeverUsed
	const DepthStencilState::DepthMode disable_depth_testing(false);

	vertexShader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/ForwardRendering.hlsl",
		Shader::ShaderMacros(), "VS_main", "latest");
	pixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl",
		Shader::ShaderMacros(), "PS_main", "latest");
	lightPixelShaser->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl",
		Shader::ShaderMacros(), "PS_light", "latest");
	oitPixelShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/OIT/oit.hlsl", Shader::ShaderMacros(),
		"PS_main", "latest");
	//Opaque Pass
	{
		std::shared_ptr<PipelineState> g_OpaquePipeline = renderer->CreatePipelineState();
		g_OpaquePipeline->SetShader(Shader::VertexShader, vertexShader);
		g_OpaquePipeline->SetShader(Shader::PixelShader, lightPixelShaser);

		g_OpaquePipeline->SetRenderTarget(rWindow->GetRenderTarget());

		std::shared_ptr<SamplerState> sampler = renderer->CreateSamplerState();
		sampler->SetFilter(SamplerState::MinFilter::MinLinear, SamplerState::MagFilter::MagLinear,
			SamplerState::MipFilter::MipLinear);
		sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat,
			SamplerState::WrapMode::Repeat);

		auto iter = scene.begin();
		for (; iter != scene.end(); ++iter)
		{
			light_pass = std::make_shared<LightsPass>(renderer, *iter, g_OpaquePipeline);
			light_pass->SetSampler(sampler, "LinearRepeatSampler");
			forwardTechnique->AddPass(light_pass);
			light_pass.reset();
		}
		sampler.reset();
		g_OpaquePipeline.reset();
	}

	//OIT Pass
	{
		auto oitPipeline = renderer->CreatePipelineState();
		oitPipeline->SetShader(Shader::VertexShader, vertexShader);
		oitPipeline->SetShader(Shader::PixelShader, oitPixelShader);
		oitPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::None);
		oitPipeline->SetRenderTarget(rWindow->GetRenderTarget());
		auto iter = transScene.begin();

		auto oitPass = make_shared<OITPass>(renderer, scene, oitPipeline);
		//forwardTechnique->AddPass(oitPass);
		oitPass.reset();
	}

	//Transparent Pass
	{
		std::shared_ptr<PipelineState> transparentPipeline = renderer->CreatePipelineState();
		transparentPipeline->SetShader(Shader::VertexShader, vertexShader);
		transparentPipeline->SetShader(Shader::PixelShader, lightPixelShaser);
		transparentPipeline->GetBlendState().set_blend_mode(alpha_blending);
		transparentPipeline->GetDepthStencilState().SetDepthMode(disable_depth_writes);
		transparentPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::None);
		transparentPipeline->SetRenderTarget(rWindow->GetRenderTarget());

		auto iter = transScene.begin();
		for (; iter != transScene.end(); ++iter)
		{
			transparent_pass = std::make_shared<TransparentPass>(renderer, *iter, transparentPipeline);
			//forwardTechnique->AddPass(transparentPass);
			transparent_pass.reset();
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
		lightFontPipeline->GetDepthStencilState().SetDepthMode(disable_depth_writes);
		lightFontPipeline->GetBlendState().set_blend_mode(alpha_blending);

		//lightPassFont = std::make_shared<LightsPass>(renderer,scene,lightFontPipeline);
	}


	InsertTechnique(forwardTechnique);

	vertexShader.reset();
	pixelShader.reset();
	lightPixelShaser.reset();
	light_pass.reset();
	transparent_pass.reset();
	light_pass_font.reset();
}

LightEffect::~LightEffect()
= default;

std::shared_ptr<VisualEffectInstance> LightEffect::CreateInstance()
{
	std::shared_ptr<VisualEffectInstance> instance = std::make_shared<VisualEffectInstance>(shared_from_this(), 0);
	return instance;
}
