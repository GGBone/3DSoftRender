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
	class ShadowPass : public BasePass
	{
	public:
		ShadowPass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);

		virtual ~ShadowPass() = default;

	protected:

	private:
	};
}