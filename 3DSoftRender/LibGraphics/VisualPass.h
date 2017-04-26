#pragma once
#include "Object.h"
#include "Dx11RenderLIB.h"
#include "Visitor.h"
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
		virtual void Visit(Scene& scene) = 0;
		virtual void Visit(Node& node) = 0;
		virtual void Visit(Mesh& mesh) = 0;

	};
	typedef VisualPass* VisualPassPtr;
}
