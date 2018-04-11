#pragma once
#include "Graphics\Renderer.h"
#include "Graphics\GraphicsLib.h"
#include "Graphics\VisualTechnique.h"
#include "Graphics\Dx11Shader.h"


namespace Hikari
{
	class VisualEffectInstance;
	class VisualEffect
	{
	public:
		VisualEffect::VisualEffect();
		VisualEffect::~VisualEffect();
		VisualEffect::VisualEffect(const std::string & name, int mode);
		void VisualEffect::InsertTechnique(std::shared_ptr<VisualTechnique> technique);
		std::shared_ptr<VisualTechnique> VisualEffect::GetTechnique(int techIndex);
		size_t GetTechniqueSize() const;
		void PreRender();
	protected:
		virtual std::shared_ptr<VisualEffectInstance> CreateInstance() = 0;

	private:
		std::vector<std::shared_ptr<VisualTechnique>> mTechniques;
		std::string m_EffectName;
	};
}