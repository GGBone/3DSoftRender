#include "Graphics\GraphicsPCH.h"
#include "Application\WindowApplicationEngine.h"
#include "OpaquePass.h"
#include "Graphics\Mesh.h"
#include "Graphics\Material.h"
#include "Graphics\PipelineState.h"
#include "Graphics\Scene.h"
#include "Graphics\Renderer.h"
#include "Graphics\Material.h"
#include "Graphics\Node.h"
#include "Graphics\PipelineState.h"
#include "Graphics\StructuredBuffer.h"
using namespace Hikari;
Hikari::OpaquePass::OpaquePass(std::shared_ptr<Renderer> renderer,std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline)
	:BasePass(renderer,scene,pipeline)
{

}

Hikari::OpaquePass::~OpaquePass()
{

}



void Hikari::OpaquePass::Visit(Mesh & mesh)
{

	std::shared_ptr<Material> pMaterial = mesh.GetMaterial();
	if (pMaterial && !pMaterial->IsTransparent())
	{
		mesh.Render(GetRenderEventArgs());
	}

}
