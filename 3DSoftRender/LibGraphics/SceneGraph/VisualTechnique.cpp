#include "GraphicsPCH.h"
#include "VisualTechnique.h"
using namespace Hikari;

VisualTechnique::VisualTechnique()
= default;

VisualTechnique::~VisualTechnique()
{
	auto iter = m_Passes.begin();
	for (; iter != m_Passes.end(); ++iter)
	{
		(*iter).reset();
	}
	m_Passes.clear();
	mSampler.reset();
}

unsigned int VisualTechnique::AddPass(std::shared_ptr<VisualPass> pass)
{
	// No check for duplicate passes (it may be intended to render the same pass multiple times?)
	m_Passes.push_back(pass);
	return static_cast<unsigned int>(m_Passes.size()) - 1;
}

std::shared_ptr<VisualPass> VisualTechnique::GetPass(unsigned int ID) const
{
	if (ID < m_Passes.size())
	{
		return m_Passes[ID];
	}

	return nullptr;
}

unsigned int VisualTechnique::GetNumPass() const
{
	return m_Passes.size();
}

// Render the scene using the passes that have been configured.
void VisualTechnique::Render(RenderEventArgs& renderEventArgs)
{
	for (auto pass : m_Passes)
	{
		if (pass->IsEnabled())
		{
			pass->PreRender(renderEventArgs);
			pass->Render(renderEventArgs);
			pass->PostRender(renderEventArgs);
		}
	}
}

void VisualTechnique::SetSampler(std::shared_ptr<SamplerState> sampler)
{
	mSampler = sampler;
}

std::shared_ptr<SamplerState> VisualTechnique::GetSampler() const
{
	return mSampler;
}
