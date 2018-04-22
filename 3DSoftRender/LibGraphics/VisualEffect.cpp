#include "Graphics\VisualEffect.h"
#include "Graphics\GraphicsPCH.h"
using namespace Hikari;

Hikari::VisualEffect::VisualEffect()
:m_EffectName("Default")
{
}

Hikari::VisualEffect::~VisualEffect()
{
	ClearTechiniques();
}

void Hikari::VisualEffect::ClearTechiniques()
{
	auto iter = mTechniques.begin();
	for (; iter != mTechniques.end(); ++iter)
	{
		(*iter).reset();
	}
	mTechniques.clear();
}
void Hikari::VisualEffect::InsertTechnique(std::shared_ptr<VisualTechnique> technique)
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

std::shared_ptr<VisualTechnique> Hikari::VisualEffect::GetTechnique(int techIndex)
{
	return mTechniques[techIndex];
}

Hikari::VisualEffect::VisualEffect(const std::string & name, int mode)
	:m_EffectName(name)
{

}



