#include "Graphics\GraphicsPCH.h"
#include "DefaultEffect.h"
#include "Graphics\Dx11Shader.h"
using namespace Hikari;

Hikari::DefaultEffect::DefaultEffect(DirectRenderer* renderer)
{
	/*Shader* vshader = new Shader("DefaultShader.fx", 1, 1, 3, 0, false);
	vshader->SetInput(0, "VS", Shader::VT_FLOAT4, Shader::VS_POSITION);
	vshader->SetOutput(0, "", Shader::VT_FLOAT4, Shader::VS_POSITION);
	vshader->SetConstant(0, "mvp", 4);
	
	PixelShader* pshader = new PixelShader("DefaultShader.fx", 1, 1, 0, 0, false);
	pshader->SetInput(0, "PS", Shader::VT_FLOAT4, Shader::VS_POSITION);
	pshader->SetOutput(0, "", Shader::VT_FLOAT4, Shader::VS_COLOR0);*/

	//ShaderDx* vshader = new ShaderDx(renderer);
	//vshader->LoadShaderFromFile(Shader::VertexShader, "DefaultShader.fx", Shader::ShaderMacros(), "VS_main", "latest");

	//ShaderDx* pshader = new ShaderDx(renderer);
	//pshader->LoadShaderFromFile(Shader::VertexShader, "DefaultShader.fx", Shader::ShaderMacros(), "PS_main", "latest");


	//VisualPass* pass = new VisualPass();
	//pass->SetVertexShader(vshader);
	//pass->SetPixelShader(pshader);

	//VisualTechnique* technique = new VisualTechnique();
	//technique->InsertPass(pass);
	//InsertTechnique(technique);
}

Hikari::DefaultEffect::~DefaultEffect()
{
}

std::shared_ptr<VisualEffectInstance> Hikari::DefaultEffect::CreateInstance()
{
	/*VisualEffectInstance* instance = new VisualEffectInstance(this, 0);

	instance->SetVertexConstant(0, 0, new MMatrixParam());
	instance->SetVertexConstant(0, 1, new VMatrixParam());

	instance->SetVertexConstant(0, 2, new PMatrixParam());
	return instance;*/
	return nullptr;
}
