#pragma once
#include "GraphicsLib.h"
#include "VisualPass.h"
namespace Hikari
{
	class RenderEventArgs;
	class SamplerState;
	class VisualTechnique
	{

	public:
		VisualTechnique();
		virtual ~VisualTechnique();

		// Add a pass to the technique. The ID of the added pass is returned
		// and can be used to retrieve the pass later.
		virtual unsigned int AddPass(VisualPass* pass);
		virtual VisualPass* GetPass(unsigned int ID) const;
		virtual unsigned int GetNumPass()const;
		// Render the scene using the passes that have been configured.
		virtual void Render(RenderEventArgs& renderEventArgs);
		virtual void SetSampler(SamplerState* sampler);
		virtual SamplerState* GetSampler() const;
	protected:

	private:
		typedef std::vector<VisualPass*> RenderPassList;
		RenderPassList m_Passes;
		SamplerState* mSampler;
	};
}