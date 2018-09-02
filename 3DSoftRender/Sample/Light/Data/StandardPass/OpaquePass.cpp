#include "GraphicsPCH.h"
#include "WindowApplicationEngine.h"
#include "OpaquePass.h"
#include "SceneGraph/Mesh.h"
#include "SceneGraph/Material.h"

using namespace Hikari;

OpaquePass::OpaquePass(std::shared_ptr<Renderer> renderer, std::shared_ptr<Scene> scene,
                       std::shared_ptr<PipelineState> pipeline)
	: BasePass(renderer, scene, pipeline)
{
}

OpaquePass::~OpaquePass()
= default;


void OpaquePass::Visit(Mesh& mesh)
{
	const auto pMaterial = mesh.GetMaterial();
	if (pMaterial && !pMaterial->IsTransparent())
	{
		mesh.Render(GetRenderEventArgs());
	}
}
