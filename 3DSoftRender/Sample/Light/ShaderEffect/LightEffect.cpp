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
#include "ShadowPass.h"
#include "GeometryPass.h"
#include "GBufferLightingPass.h"
#include "ClearRenderTargetPass.h"
using namespace Hikari;

LightEffect::LightEffect(std::shared_ptr<RenderWindow> rWindow, std::shared_ptr<Renderer> renderer,
	vector<std::shared_ptr<Scene>> scene, vector<shared_ptr<Scene>> transScene)
{
	auto vertex_shader = renderer->CreateShader();
	auto pixel_shader = renderer->CreateShader();
	auto light_pixel_shaser = renderer->CreateShader();
	auto oit_pixel_shader = renderer->CreateShader();
	auto geometry_pass_shader = renderer->CreateShader();


	auto forwardTechnique = std::make_shared<VisualTechnique>();
	auto deferredTechinique = std::make_shared<VisualTechnique>();


	//std::shared_ptr<OpaquePass> opaquePass;
	std::shared_ptr<LightsPass> forward_light_pass;
	std::shared_ptr<GeometryPass> deferred_geometry_pass;
	std::shared_ptr<GBufferLightingPass> g_buffer_lighting_pass;


	std::shared_ptr<TransparentPass> transparent_pass;
	std::shared_ptr<LightsPass> light_pass_font;
	std::shared_ptr<ClearRenderTargetPass> clear_pass;
	std::shared_ptr<ShadowPass> shadow_pass;

	const BlendState::BlendMode alpha_blending(true, false, BlendState::BlendFactor::SrcAlpha,
		BlendState::BlendFactor::OneMinusSrcAlpha);
	const BlendState::BlendMode additive_blending(true, false, BlendState::BlendFactor::One,
		BlendState::BlendFactor::One);

	const DepthStencilState::DepthMode disable_depth_writes(true, DepthStencilState::DepthWrite::Disable);
	// ReSharper disable once CppDeclaratorNeverUsed
	const DepthStencilState::DepthMode disable_depth_testing(false);

	vertex_shader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/ForwardRendering.hlsl",
		Shader::ShaderMacros(), "VS_main", "latest");
	pixel_shader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl",
		Shader::ShaderMacros(), "PS_main", "latest");
	light_pixel_shaser->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/ForwardRendering.hlsl",
		Shader::ShaderMacros(), "PS_light", "latest");
	oit_pixel_shader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/OIT/oit.hlsl", Shader::ShaderMacros(),
		"PS_main", "latest");
	geometry_pass_shader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/MyDeferredShader.hlsl", Shader::ShaderMacros(),
		"PS_main", "latest");
	//prepare
	auto shadow_map_texture = renderer->CreateTexture2D(2048, 2048, 1, { Texture::Components::DepthStencil,
		Texture::Type::UnsignedNormalized,1,0,0,0,0,24,8
	});
	auto shadow_render_target = renderer->CreateRenderTarget();
	shadow_render_target->AttachTexture(RenderTarget::AttachmentPoint::Depth, shadow_map_texture);
	{
		//Clear
		auto clear_pass = make_shared<ClearRenderTargetPass>(shadow_render_target,ClearFlags::Depth,Float4(0.45,0.45,0.45,1.0));
		forwardTechnique->AddPass(clear_pass);
		clear_pass.reset();
	}

	{
		//shadow
		auto shadow_pipeline = renderer->CreatePipelineState();
		shadow_pipeline->SetShader(Shader::VertexShader, vertex_shader);
		shadow_pipeline->SetShader(Shader::PixelShader, nullptr);
		shadow_pipeline->SetRenderTarget(shadow_render_target);
		shadow_pipeline->GetRasterizerState().SetViewport({ 0.f, 0.f, 2048.f, 2048.f, 0.0f, 1.0f });
		auto iter = scene.begin();
		for (; iter != scene.end(); ++iter)
		{
			shadow_pass = make_shared<ShadowPass>(renderer, *iter, shadow_pipeline);
			forwardTechnique->AddPass(shadow_pass);
			shadow_pass.reset();
		}
	}


	//ClearColor
	{
		auto clear_pass = make_shared<ClearRenderTargetPass>(rWindow->GetRenderTarget(), ClearFlags::All, Float4(0.45, 0.45, 0.45, 1.0));
		forwardTechnique->AddPass(clear_pass);
		clear_pass.reset();
	}

	//Forward Opaque Pass
	{
		std::shared_ptr<PipelineState> g_OpaquePipeline = renderer->CreatePipelineState();
		g_OpaquePipeline->SetShader(Shader::VertexShader, vertex_shader);
		g_OpaquePipeline->SetShader(Shader::PixelShader, light_pixel_shaser);

		const auto render_target = rWindow->GetRenderTarget();
		g_OpaquePipeline->SetRenderTarget(render_target);
		g_OpaquePipeline->GetRasterizerState().SetViewport({ 0.f, 0.f,1280.f, 760.f, 0.0f,1.0f });

		std::shared_ptr<SamplerState> sampler = renderer->CreateSamplerState();
		sampler->SetFilter(SamplerState::MinFilter::MinLinear, SamplerState::MagFilter::MagLinear,
			SamplerState::MipFilter::MipLinear);
		sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat,
			SamplerState::WrapMode::Repeat);

		auto iter = scene.begin();
		for (; iter != scene.end(); ++iter)
		{
			forward_light_pass = std::make_shared<LightsPass>(renderer, *iter, g_OpaquePipeline);
			forward_light_pass->SetSampler(sampler, "LinearRepeatSampler");
			forwardTechnique->AddPass(forward_light_pass);
			forward_light_pass.reset();
		}
		sampler.reset();
		g_OpaquePipeline.reset();
	}

	//Deferred Opaque Pass
	{
		std::shared_ptr<PipelineState> geometry_pipeline = renderer->CreatePipelineState();

	}

	//OIT Pass
	{
		auto oitPipeline = renderer->CreatePipelineState();
		oitPipeline->SetShader(Shader::VertexShader, vertex_shader);
		oitPipeline->SetShader(Shader::PixelShader, oit_pixel_shader);
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
		transparentPipeline->SetShader(Shader::VertexShader, vertex_shader);
		transparentPipeline->SetShader(Shader::PixelShader, light_pixel_shaser);
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
		lightFontPipeline->SetShader(Shader::VertexShader, vertex_shader);
		lightFontPipeline->SetShader(Shader::PixelShader, light_pixel_shaser);
		lightFontPipeline->SetRenderTarget(rWindow->GetRenderTarget());
		lightFontPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::Front);
		lightFontPipeline->GetDepthStencilState().SetDepthMode(disable_depth_writes);
		lightFontPipeline->GetBlendState().set_blend_mode(alpha_blending);

		//lightPassFont = std::make_shared<LightsPass>(renderer,scene,lightFontPipeline);
	}


	InsertTechnique(forwardTechnique);

	vertex_shader.reset();
	pixel_shader.reset();
	light_pixel_shaser.reset();
	forward_light_pass.reset();
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
