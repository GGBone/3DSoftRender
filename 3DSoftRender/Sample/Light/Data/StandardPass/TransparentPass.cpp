#include "Graphics\Mesh.h"
#include "TransparentPass.h"
#include "Graphics\Material.h"
using namespace Hikari;

TransparentPass::TransparentPass(std::shared_ptr<Renderer> render,std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline)
:base(render,scene,pipeline)
{
}

Hikari::TransparentPass::~TransparentPass()
{
}

void Hikari::TransparentPass::Visit(Mesh & mesh)
{
	std::shared_ptr<Material> pMaterial = mesh.GetMaterial();
	if (pMaterial && pMaterial->IsTransparent())
	{
		mesh.Render(GetRenderEventArgs());
	}
}
