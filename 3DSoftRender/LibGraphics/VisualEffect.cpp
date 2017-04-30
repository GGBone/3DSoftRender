#include "VisualEffect.h"
#include "GraphicsPCH.h"
using namespace Hikari;

Hikari::VisualEffect::VisualEffect()
:m_EffectName("Default")
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

size_t Hikari::VisualEffect::GetTechniqueSize() const
{
	return mTechniques.size();
}

void Hikari::VisualEffect::PreRender()
{
	std::vector<VisualTechnique*>::const_iterator iter;
	for (iter = mTechniques.begin(); iter != mTechniques.end(); ++iter)
	{
		for (int i = 0; i < (*iter)->GetNumPass(); ++i)
		{
			(*iter)->GetPass(i);
		}
	}
}

VisualTechnique * Hikari::VisualEffect::GetTechnique(int techIndex)
{
	return mTechniques[techIndex];
}

Hikari::VisualEffect::VisualEffect(const std::string & name, int mode)
	:m_EffectName(name)
{

}
