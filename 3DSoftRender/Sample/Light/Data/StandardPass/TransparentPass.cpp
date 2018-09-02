#include "TransparentPass.h"
#include "SceneGraph/Material.h"
#include "SceneGraph/Mesh.h"
using namespace Hikari;

TransparentPass::TransparentPass(const shared_ptr<Renderer>& render, const shared_ptr<Scene>& transScene,
                                 const shared_ptr<PipelineState>& pipeline)
	: base(render, transScene, pipeline)
{
}

TransparentPass::~TransparentPass()
= default;

void TransparentPass::Visit(Mesh& mesh)
{
	std::shared_ptr<Material> pMaterial = mesh.GetMaterial();
	/*if (pMaterial && pMaterial->IsTransparent())
	{*/
	mesh.Render(GetRenderEventArgs());
	//}
}
