#pragma once
#include "SceneGraph/VisualPass.h"

namespace Hikari
{
	class RenderEventArgs;

	class AbstractPass : public VisualPass
	{
	public:
		AbstractPass();
		virtual ~AbstractPass();

		// Enable or disable the pass. If a pass is disabled, the technique will skip it.
		void SetEnabled(bool enabled) override;
		bool IsEnabled() const override;

		// Render the pass. This should only be called by the RenderTechnique.
		void PreRender(RenderEventArgs& e) override;
		void Render(RenderEventArgs& e) override = 0;
		void PostRender(RenderEventArgs& e) override;

		// Inherited from Visitor
		void Visit(Scene& scene) override;
		void Visit(Node& node) override;
		void Visit(Mesh& mesh) override;

	private:
		bool m_Enabled;
	};
}
