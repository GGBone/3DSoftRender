#include "GraphicsPCH.h"
#include "DefaultEffect.h"
using namespace Hikari;

Hikari::DefaultEffect::DefaultEffect()
{
	VertexShader* vshader = new VertexShader("DefaultShader.fx", 1, 1, 3, 0, false);
	vshader->SetInput(0, "VS", Shader::VT_FLOAT4, Shader::VS_POSITION);
	vshader->SetOutput(0, "", Shader::VT_FLOAT4, Shader::VS_POSITION);
	vshader->SetConstant(0, "mvp", 4);
	
	PixelShader* pshader = new PixelShader("DefaultShader.fx", 1, 1, 0, 0, false);
	pshader->SetInput(0, "PS", Shader::VT_FLOAT4, Shader::VS_POSITION);
	pshader->SetOutput(0, "", Shader::VT_FLOAT4, Shader::VS_COLOR0);

	VisualPass* pass = new VisualPass();
	pass->SetVertexShader(vshader);
	pass->SetPixelShader(pshader);

	VisualTechnique* technique = new VisualTechnique();
	technique->InsertPass(pass);
	InsertTechnique(technique);
}

Hikari::DefaultEffect::~DefaultEffect()
{
}

VisualEffectInstance * Hikari::DefaultEffect::CreateInstance() const
{
	VisualEffectInstance* instance = new VisualEffectInstance(this, 0);

	instance->SetVertexConstant(0, 0, new MMatrixParam());
	instance->SetVertexConstant(0, 1, new VMatrixParam());

	instance->SetVertexConstant(0, 2, new PMatrixParam());
	return instance;
}
