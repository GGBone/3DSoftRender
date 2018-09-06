#include <GraphicsPCH.h>
#include <Graphics.h>
#include "VisualEffect.h"

using namespace Hikari;

VisualEffect::VisualEffect()
	: m_EffectName("Default")
{
}

VisualEffect::~VisualEffect()
{
	ClearTechiniques();
}

void VisualEffect::ClearTechiniques()
{
	auto iter = mTechniques.begin();
	for (; iter != mTechniques.end(); ++iter)
	{
		(*iter).reset();
	}
	mTechniques.clear();
}

void VisualEffect::InsertTechnique(std::shared_ptr<VisualTechnique> technique)
{
	if (technique != nullptr)
	{
		mTechniques.push_back(technique);
	}
}

size_t VisualEffect::GetTechniqueSize() const
{
	return mTechniques.size();
}

std::shared_ptr<VisualTechnique> VisualEffect::GetTechnique(int techIndex)
{
	return mTechniques[techIndex];
}

VisualEffect::VisualEffect(const std::string& name, int mode)
	: m_EffectName(name)
{
}
