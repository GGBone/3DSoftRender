#include "GraphicsPCH.h"
#include "VisualEffect.h"
using namespace Hikari;

Hikari::VisualEffect::VisualEffect()
{
}

Hikari::VisualEffect::~VisualEffect()
{
}

void Hikari::VisualEffect::InsertTechnique(VisualTechnique * technique)
{
	if (technique != nullptr)
	{
		mTechniques.push_back(technique);
	}
}

VisualTechnique * Hikari::VisualEffect::GetTechnique(int techIndex)
{
	return mTechniques[techIndex];
}

VisualEffect * Hikari::VisualEffect::LoadFX(const std::string & name, int mode)
{
	return new VisualEffect(name, mode);
}

Hikari::VisualEffect::VisualEffect(const std::string & name, int mode)
{

}

VisualTechnique * Hikari::VisualEffect::LoadVisualTechnique(std::ifstream & in)
{
	VisualTechnique* technique = new VisualTechnique();
	char numPass;
	in.read(&numPass, sizeof(int));
	for (int i = 0; i < numPass; ++i)
	{
		technique->InsertPass(LoadVisualPass(in));
	}
	return technique;
}

VisualPass * Hikari::VisualEffect::LoadVisualPass(std::ifstream & in)
{
	VisualPass* pass = new VisualPass();
	pass->SetVertexShader((VertexShader*)LoadShader(in));
	pass->SetPixelShader((PixelShader*)LoadShader(in));
	return nullptr;
}

Shader* Hikari::VisualEffect::LoadShader(std::ifstream & in)
{
	std::string programName = LoadStdString(in);
	char numInput, numOutput, numConstants, numSamplers, numProfilers;

	in.read(&numInput, sizeof(char));
	in.read(&numOutput, sizeof(char));
	in.read(&numConstants, sizeof(char));
	in.read(&numSamplers, sizeof(char));
	in.read(&numProfilers, sizeof(char));

	Shader* shader = nullptr;
	//VertexShader
	shader = new VertexShader(programName, numInput, numOutput, numConstants, numSamplers, true);
	//Pixel
	shader = new PixelShader(programName, numInput, numOutput, numConstants, numSamplers, true);
	return shader;
}

std::string Hikari::VisualEffect::LoadStdString(std::ifstream & inFile)
{
	return NULL;
}
