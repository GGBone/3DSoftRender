#include "Graphics\Mesh.h"
#include "TransparentPass.h"
#include "Graphics\Material.h"
using namespace Hikari;

TransparentPass::TransparentPass(shared_ptr<Renderer> render, shared_ptr<Scene> transScene, shared_ptr<PipelineState> pipeline)
:base(render, transScene,pipeline)
{
}

Hikari::TransparentPass::~TransparentPass()
{
}

void Hikari::TransparentPass::Visit(Mesh & mesh)
{
	std::shared_ptr<Material> pMaterial = mesh.GetMaterial();
	/*if (pMaterial && pMaterial->IsTransparent())
	{*/
		mesh.Render(GetRenderEventArgs());
	//}
}
