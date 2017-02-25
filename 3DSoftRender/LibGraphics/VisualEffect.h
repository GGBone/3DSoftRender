#pragma once
#include "GraphicsLib.h"
#include "VisualTechnique.h"
#include "Shader.h"
namespace Hikari
{
	class VisualEffect
	{
	public:
		Hikari::VisualEffect::VisualEffect();
		Hikari::VisualEffect::~VisualEffect();
		Hikari::VisualEffect::VisualEffect(const std::string & name, int mode);
		void Hikari::VisualEffect::InsertTechnique(VisualTechnique * technique);
		VisualTechnique * Hikari::VisualEffect::GetTechnique(int techIndex);
		VisualEffect * Hikari::VisualEffect::LoadFX(const std::string & name, int mode);
		Shader* LoadShader(std::ifstream & in);
		VisualTechnique * Hikari::VisualEffect::LoadVisualTechnique(std::ifstream & in);

		VisualPass * Hikari::VisualEffect::LoadVisualPass(std::ifstream & in);
		std::string Hikari::VisualEffect::LoadStdString(std::ifstream & inFile);
		
	private:
		std::vector<VisualTechnique*> mTechniques;
	};
}