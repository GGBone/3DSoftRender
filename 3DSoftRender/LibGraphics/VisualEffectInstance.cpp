#include "GraphicsPCH.h"
#include "VisualEffectInstance.h"
using namespace Hikari;
Hikari::VisualEffectInstance::VisualEffectInstance(const VisualEffect * effect, int techniqueIndex)
	:mEffect(const_cast<VisualEffect*>(effect)),
	mTechniqueIndex(techniqueIndex)
{
	
}

Hikari::VisualEffectInstance::~VisualEffectInstance()
{

}

const VisualEffect* VisualEffectInstance::GetEffect() const
{
	return mEffect;
}
