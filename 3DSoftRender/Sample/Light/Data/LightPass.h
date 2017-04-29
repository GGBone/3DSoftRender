#pragma once
#include <Light.h>

#include "BasePass.h"

namespace Hikari
{
	class Renderer;
	class Material;
	class StructuredBuffer;
	class LightsPass : public BasePass
	{
	public:

		LightsPass(Renderer* renderer,std::vector<Light>& lights, Scene* pointLight, Scene* spotLight, Scene* directionalLight, PipelineState* pipeline);
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

		Renderer* m_RenderDevice;

		Material* m_LightMaterial;

		PipelineState* m_Pipeline;

		Scene* m_PointLightScene;
		Scene* m_pSpotLightScene;
		Scene* m_pDirectionalLightScene;


		StructuredBuffer* g_pLightStructuredBuffer;
	};
}