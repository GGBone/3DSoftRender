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
	/*float world[] =
	{
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0,
	};
	float view[] =
	{
		1.0,0.0,0.0,0.0,
		0.0,0.94863262f,0.316227764f,-0.948683262f,
		0.0,-0.316227764f,0.948683262f,6.64079283f,
		0.0,0.0,0.0,1.0,
	};
	float project[] =
	{
		1.81066f,0.0,0.0,0.0,
		0.0,2.41421342f,0.0,0.0,
		0.0,0.0,1.000,-0.0100010000f,
		0.0,0.0,1.0,0.0,
	};*/
	VisualEffectInstance* instance = new VisualEffectInstance(this, 0);
	/*VMatrixParam* tempWorld = new VMatrixParam();
	tempWorld->SetMatrix(world);
	instance->SetVertexConstant(0, 0, tempWorld);

	VMatrixParam* tempView = new VMatrixParam();
	tempView->SetMatrix(world);
	tempView->SetMatrix(view);
	instance->SetVertexConstant(0, 1, tempView);

	VMatrixParam* tempProj = new VMatrixParam();
	tempProj->SetMatrix(world);
	tempProj->SetMatrix(project);*/
	instance->SetVertexConstant(0, 1, new VMatrixParam());
	instance->SetVertexConstant(0, 0, new MMatrixParam());
	instance->SetVertexConstant(0, 2, new PMatrixParam());
	return instance;
}
