#include "Graphics.h"
#include "OpaquePass.h"
#include "DefaultEffect.h"
#include "SceneGraph/VisualEffectInstance.h"
#include "Renderer/RenderWindow.h"
using namespace Hikari;

DefaultEffect::DefaultEffect(shared_ptr<RenderWindow> r_window,shared_ptr<Renderer> renderer, shared_ptr<Scene> scene)
{
#ifdef SOFT_RENDER
	auto vshader = new shader("defaultshader.fx", 1, 1, 3, 0, false);
	vshader->setinput(0, "vs", shader::vt_float4, shader::vs_position);
	vshader->setoutput(0, "", shader::vt_float4, shader::vs_position);
	vshader->setconstant(0, "mvp", 4);
	
	pixelshader* pshader = new pixelshader("defaultshader.fx", 1, 1, 0, 0, false);
	pshader->setinput(0, "ps", shader::vt_float4, shader::vs_position);
	pshader->setoutput(0, "", shader::vt_float4, shader::vs_color0);
#else
	auto vshader = renderer->CreateShader();
	vshader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/DefaultShader.hlsl", Shader::ShaderMacros(),
	                            "VS_main", "latest");

	auto pshader = renderer->CreateShader();
	pshader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/DefaultShader.hlsl", Shader::ShaderMacros(),
	                            "PS_main", "latest");

	auto mPipeline = renderer->CreatePipelineState();
	mPipeline->SetShader(Shader::VertexShader, vshader);
	mPipeline->SetShader(Shader::PixelShader, pshader);
	mPipeline->SetRenderTarget(r_window->GetRenderTarget());
	const auto pass = make_shared<OpaquePass>(renderer, scene, mPipeline);

	auto technique = make_shared<VisualTechnique>();
	technique->AddPass(pass);
	InsertTechnique(technique);
#endif
}

DefaultEffect::~DefaultEffect()
= default;

std::shared_ptr<VisualEffectInstance> DefaultEffect::CreateInstance()
{
#ifdef SOFT_RENDER
	VisualEffectInstance* instance = new VisualEffectInstance(this, 0);

	instance->SetVertexConstant(0, 0, new MMatrixParam());
	instance->SetVertexConstant(0, 1, new VMatrixParam());

	instance->SetVertexConstant(0, 2, new PMatrixParam());
	return instance;
#else
	auto instance = make_shared<VisualEffectInstance>(shared_from_this(), 0);
	return instance;
#endif
	return nullptr;
}
