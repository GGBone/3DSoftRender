#include "GraphicsPCH.h"
#include "ShadowPass.h"

Hikari::ShadowPass::ShadowPass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene,
                               std::shared_ptr<PipelineState> pipeline)
	: BasePass(render, scene, pipeline)
{
}
