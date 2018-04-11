#include "Graphics\VisualEffect.h"
#include "Graphics\GraphicsPCH.h"
using namespace Hikari;

Hikari::VisualEffect::VisualEffect()
:m_EffectName("Default")
{
}

Hikari::VisualEffect::~VisualEffect()
{
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

void Hikari::VisualEffect::PreRender()
{
	/*std::vector<std::shared_ptr<VisualTechnique>>::const_iterator iter;
	for (iter = mTechniques.begin(); iter != mTechniques.end(); ++iter)
	{
		for (int i = 0; i < (*iter)->GetNumPass(); ++i)
		{
			(*iter)->GetPass(i);
		}
	}*/
}

std::shared_ptr<VisualTechnique> Hikari::VisualEffect::GetTechnique(int techIndex)
{
	return mTechniques[techIndex];
}

Hikari::VisualEffect::VisualEffect(const std::string & name, int mode)
	:m_EffectName(name)
{

}



