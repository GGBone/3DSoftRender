#include "GraphicsPCH.h"
#include "VisualEffectInstance.h"
using namespace Hikari;

VisualEffectInstance::VisualEffectInstance(std::shared_ptr<VisualEffect> effect, int techniqueIndex)
	: mEffect(effect),
	  mTechniqueIndex(techniqueIndex)
{
}

VisualEffectInstance::~VisualEffectInstance()
= default;

const std::shared_ptr<VisualEffect> VisualEffectInstance::GetEffect() const
{
	return mEffect;
}

void VisualEffectInstance::Render(RenderEventArgs& e)
{
	std::shared_ptr<VisualTechnique> technique;
	size_t size = mEffect->GetTechniqueSize();
	for (size_t i = 0; i < size; i++)
	{
		technique = mEffect->GetTechnique(i);
		size_t passNum = technique->GetNumPass();
		for (size_t j = 0; j < passNum; j++)
		{
			technique->GetPass(j)->PreRender(e);
			technique->GetPass(j)->Render(e);
			technique->GetPass(j)->PostRender(e);
		}
	}
}
