#pragma once
#include "Core.h"
#include "BasePass.h"

namespace Hikari
{
	class TransparentPass : public BasePass
	{
	public:
		typedef BasePass base;
		TransparentPass(const shared_ptr<Renderer>& render, const shared_ptr<Scene>& transScene,
		                const shared_ptr<PipelineState>& pipeline);
		virtual ~TransparentPass();
		void Visit(Mesh& mesh) override;
	};
}
