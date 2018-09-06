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
		virtual unsigned int AddPass(std::shared_ptr<VisualPass> pass);
		virtual std::shared_ptr<VisualPass> GetPass(unsigned int ID) const;
		virtual unsigned int GetNumPass() const;
		// Render the scene using the passes that have been configured.
		virtual void Render(RenderEventArgs& renderEventArgs);
		virtual void SetSampler(std::shared_ptr<SamplerState> sampler);
		virtual std::shared_ptr<SamplerState> GetSampler() const;
	protected:

	private:
		typedef std::vector<std::shared_ptr<VisualPass>> RenderPassList;
		RenderPassList m_Passes;
		std::shared_ptr<SamplerState> mSampler;
	};
}
