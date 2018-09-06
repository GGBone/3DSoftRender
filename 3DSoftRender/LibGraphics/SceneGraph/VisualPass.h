#pragma once
#include "Object.h"
#include "Renderer/DxRenderer/Dx11RenderLIB.h"
#include "SceneGraph/Visitor.h"

namespace Hikari
{
	class RenderEventArgs;

	class VisualPass : public Visitor
	{
	public:
		virtual void SetEnabled(bool enabled) = 0;
		virtual bool IsEnabled() const = 0;

		// Render the pass. This should only be called by the RenderTechnique.
		virtual void PreRender(RenderEventArgs& e) = 0;
		virtual void Render(RenderEventArgs& e) = 0;
		virtual void PostRender(RenderEventArgs& e) = 0;

		// Inherited from Visitor
		void Visit(Scene& scene) override = 0;
		void Visit(Node& node) override = 0;
		void Visit(Mesh& mesh) override = 0;
	};

	typedef VisualPass* VisualPassPtr;
}
