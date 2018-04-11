#pragma once
#include <Graphics\Light.h>

#include "BasePass.h"

namespace Hikari
{
	class Renderer;
	class Material;
	class StructuredBuffer;
	class LightsPass : public BasePass
	{
	public:

		LightsPass(std::shared_ptr<Renderer> renderer,std::vector<Light>& lights, std::shared_ptr<Scene> pointLight, 
			std::shared_ptr<Scene> spotLight, std::shared_ptr<Scene> directionalLight, 
			std::shared_ptr<PipelineState> pipeline);
		virtual ~LightsPass();

		virtual void PreRender( RenderEventArgs& e );
		virtual void Render(RenderEventArgs& e);

		virtual void Visit(Scene& scene);
		virtual void Visit(Node& node);
		virtual void Visit(Mesh& mesh);

	protected:
		const Light* GetCurrentLight();
		const uint32_t GetCurrentLightIndex();

	private:
		std::vector<Light>& m_Lights;
		// The light we are currently rendering.
		Light* m_pCurrentLight;
		uint32_t m_uiLightIndex;

		std::shared_ptr<Renderer> m_RenderDevice;

		std::shared_ptr<Material> m_LightMaterial;

		std::shared_ptr<PipelineState> m_Pipeline;

		std::shared_ptr<Scene> m_PointLightScene;
		std::shared_ptr<Scene> m_pSpotLightScene;
		std::shared_ptr<Scene> m_pDirectionalLightScene;


		std::shared_ptr<StructuredBuffer> g_pLightStructuredBuffer;
	};
}