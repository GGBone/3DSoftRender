#pragma once
#include "BasePass.h"
namespace Hikari
{
	class TransparentPass : public BasePass
	{
	public:
		typedef BasePass base;
		TransparentPass(std::shared_ptr<Renderer> render,std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);
		virtual ~TransparentPass();
		virtual void Visit(Mesh& mesh) override;

	};
}