#pragma once
#include "BasePass.h"
namespace Hikari
{
	class TransparentPass : public BasePass
	{
	public:
		typedef BasePass base;
		TransparentPass(shared_ptr<Renderer> render,shared_ptr<Scene> transScene, shared_ptr<PipelineState> pipeline);
		virtual ~TransparentPass();
		virtual void Visit(Mesh& mesh) override;

	};
}