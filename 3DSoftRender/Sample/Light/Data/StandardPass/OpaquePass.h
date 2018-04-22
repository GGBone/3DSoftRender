#pragma once
#include "BasePass.h"
#include <Graphics\Light.h>
//Opaque is the render something which is not lighten.
namespace Hikari
{
	using namespace std;
	class Renderer;
	class Material;
	class StructuredBuffer;
	class OpaquePass : public BasePass
	{
	public:
		OpaquePass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);

		virtual ~OpaquePass();

		virtual void Visit(Mesh& mesh) override;

	protected:
		/*const Light* GetCurrentLight();
		const uint32_t GetCurrentLightIndex();*/
	private:
	};
}