#pragma once
#include "GraphicsLib.h"
#include "SceneGraph/VisualEffect.h"
#include "Shader/ShaderParameter.h"

namespace Hikari
{
	class ShaderParameter;
	class ShaderFloat;

	class VisualEffectInstance : public Object
	{
	public:
		VisualEffectInstance(std::shared_ptr<VisualEffect> effect, int techniqueIndex);
		~VisualEffectInstance();
		const std::shared_ptr<VisualEffect> GetEffect() const;
		void Render(RenderEventArgs& e);
	private:
		std::shared_ptr<VisualEffect> mEffect;
		int mTechniqueIndex;
	};

	typedef std::shared_ptr<VisualEffectInstance> VisualEffectInstancePtr;
}
