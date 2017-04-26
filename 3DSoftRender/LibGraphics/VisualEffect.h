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
		void PreRender();
	private:
		std::vector<VisualTechnique*> mTechniques;
		
	};
}