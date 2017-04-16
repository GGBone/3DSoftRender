#include "VisualEffect.h"
#include "GraphicsPCH.h"
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

Hikari::VisualEffect::VisualEffect(const std::string & name, int mode)
{

}

VisualTechnique * Hikari::VisualEffect::LoadVisualTechnique(Renderer* render,std::ifstream & in)
{
	VisualTechnique* technique = new VisualTechnique();
	char numPass;
	in.read(&numPass, sizeof(int));
	for (int i = 0; i < numPass; ++i)
	{
		technique->AddPass(LoadVisualPass(render,in));
	}
	return technique;
}

VisualPass * Hikari::VisualEffect::LoadVisualPass(Renderer* render,std::ifstream & in)
{
	
	
	return nullptr;
}

Shader* Hikari::VisualEffect::LoadShader(Renderer* render,std::ifstream & in)
{
	return nullptr;
}

std::string Hikari::VisualEffect::LoadStdString(Renderer* render,std::ifstream & inFile)
{
	return NULL;
}
