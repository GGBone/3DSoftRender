#pragma once
#include "BasePass.h"

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
		void PreRender(RenderEventArgs& e)override;
		void Render(RenderEventArgs& e)override;
	
		ShadowPass(std::shared_ptr<Renderer> render, shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline);

		virtual ~ShadowPass() = default;

	private:
		vector<shared_ptr<Camera>> shadow_camera_vec_;
		shared_ptr<RenderTarget> shadow_maps_;
	};
}
