#pragma once
#include "Graphics\VisualPass.h"

namespace Hikari
{
	class RenderEventArgs;
	class AbstractPass : public VisualPass
	{
	public:
		AbstractPass();
		virtual ~AbstractPass();

		// Enable or disable the pass. If a pass is disabled, the technique will skip it.
		virtual void SetEnabled(bool enabled);
		virtual bool IsEnabled() const;

		// Render the pass. This should only be called by the RenderTechnique.
		virtual void PreRender(RenderEventArgs& e);
		virtual void Render(RenderEventArgs& e) = 0;
		virtual void PostRender(RenderEventArgs& e);

		// Inherited from Visitor
		virtual void Visit(Scene& scene);
		virtual void Visit(Node& node);
		virtual void Visit(Mesh& mesh);

	private:
		bool m_Enabled;
	};
}