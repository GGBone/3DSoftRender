#include "OITPass.h"

Hikari::OITPass::OITPass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline)
:BasePass(render,scene,pipeline)
{
}

Hikari::OITPass::~OITPass()
{
}

void Hikari::OITPass::Visit(Mesh & mesh)
{
}
