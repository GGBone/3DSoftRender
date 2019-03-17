#pragma once
#include "BasePass.h"

//Opaque is the render something which is not lighten.
namespace Hikari
{
	using namespace std;
	class Renderer;
	class Material;
	class StructuredBuffer;

	class GeometryPass : public BasePass
	{
	public:
		void PreRender(RenderEventArgs& e)override;
		void Render(RenderEventArgs& e)override;

		GeometryPass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);

		virtual ~GeometryPass() = default;

	private:
		shared_ptr<StructuredBuffer> G_Buffer_;
		struct GBufferStruct
		{
			shared_ptr<RenderTarget> position;
			shared_ptr<RenderTarget> normals;
			shared_ptr<RenderTarget> albedo;
			shared_ptr<RenderTarget> specular;
		};
	};
}
