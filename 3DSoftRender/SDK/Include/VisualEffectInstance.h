#pragma once
#include "GraphicsLib.h"
#include "VisualEffect.h"
#include "ShaderParameter.h"
namespace Hikari
{
	class ShaderParameter;
	class ShaderFloat;
	class VisualEffectInstance
	{
	public:
		VisualEffectInstance(const VisualEffect* effect, int techniqueIndex);
		~VisualEffectInstance();
		const VisualEffect* GetEffect() const;

	private:
		VisualEffect* mEffect;
		int mTechniqueIndex;
	
	};
	typedef VisualEffectInstance* VisualEffectInstancePtr;
}