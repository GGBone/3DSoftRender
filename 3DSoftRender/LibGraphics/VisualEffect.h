#pragma once
#include "GraphicsLib.h"
#include "VisualTechnique.h"
#include "Dx11Shader.h"
#include "Renderer.h"
namespace Hikari
{
	class VisualEffect
	{
	public:
		VisualEffect::VisualEffect();
		VisualEffect::~VisualEffect();
		VisualEffect::VisualEffect(const std::string & name, int mode);
		void VisualEffect::InsertTechnique(VisualTechnique * technique);
		VisualTechnique * Hikari::VisualEffect::GetTechnique(int techIndex);

		Shader* LoadShader(Renderer* render,std::ifstream & in);
		VisualTechnique * Hikari::VisualEffect::LoadVisualTechnique(Renderer* render,std::ifstream & in);

		VisualPass * Hikari::VisualEffect::LoadVisualPass(Renderer* render,std::ifstream & in);
		std::string Hikari::VisualEffect::LoadStdString(Renderer* render,std::ifstream & inFile);
		
	private:
		std::vector<VisualTechnique*> mTechniques;
		
	};
}