#pragma once
#include "Renderer/Renderer.h"
#include "SceneGraph/VisualTechnique.h"

namespace Hikari
{
	class VisualEffectInstance;

	class VisualEffect
	{
	public:
		VisualEffect();
		virtual ~VisualEffect();
		VisualEffect(const std::string& name, int mode);
		void InsertTechnique(std::shared_ptr<VisualTechnique> technique);
		std::shared_ptr<VisualTechnique> VisualEffect::GetTechnique(int techIndex);
		size_t GetTechniqueSize() const;
		void ClearTechiniques();
	protected:
		virtual std::shared_ptr<VisualEffectInstance> CreateInstance() = 0;

	private:
		std::vector<std::shared_ptr<VisualTechnique>> mTechniques;
		std::string m_EffectName;
	};
}
