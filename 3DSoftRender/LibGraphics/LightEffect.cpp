#include "GraphicsPCH.h"
#include "LightEffect.h"
using namespace Hikari;
Hikari::LightEffect::LightEffect()
{
	VertexShader* vshader = new VertexShader("LightShader.fx", 1, 1, 3, 0, false);
	vshader->SetInput(0, "VS", Shader::VT_NONE, Shader::VS_NONE);

	vshader->SetOutput(0, "VS_Output", Shader::VT_NONE, Shader::VS_NONE);

	vshader->SetConstant(0, "mvp", 4);

	PixelShader* pshader = new PixelShader("LightShader.fx", 1, 1, 0, 0, false);
	pshader->SetInput(0, "PS", Shader::VT_NONE, Shader::VS_NONE);

	//pshader->SetOutput(0, "", Shader::VT_FLOAT4, Shader::VS_COLOR0);

	VisualPass* pass = new VisualPass();
	pass->SetVertexShader(vshader);
	pass->SetPixelShader(pshader);

	VisualTechnique* technique = new VisualTechnique();
	technique->InsertPass(pass);
	InsertTechnique(technique);
}

Hikari::LightEffect::~LightEffect()
{
}

VisualEffectInstance * Hikari::LightEffect::CreateInstance() const
{

	return nullptr;
}
