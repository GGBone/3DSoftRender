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

		LightsPass(std::shared_ptr<Renderer> renderer,  std::shared_ptr<Scene> pointLight,
			shared_ptr<PipelineState> pipeline);

		virtual ~LightsPass();

		virtual void PreRender( RenderEventArgs& e );
		virtual void Render(RenderEventArgs& e);

		virtual void Visit(Mesh& mesh);
		void SetSampler(std::shared_ptr<SamplerState> samp, const std::string& name);

		void SetLight(std::shared_ptr<StructuredBuffer> buffer, const std::string& name);

	protected:
		const Light* GetCurrentLight();
		const uint32_t GetCurrentLightIndex();

	private:
		// The light we are currently rendering.
		Light* m_pCurrentLight;
		uint32_t m_uiLightIndex;

		std::shared_ptr<Renderer> m_RenderDevice;

		std::shared_ptr<Scene> m_PointLightScene;
		std::shared_ptr<Scene> m_pSpotLightScene;
		std::shared_ptr<Scene> m_pDirectionalLightScene;

		std::shared_ptr<SamplerState> m_SamplerState;
		std::string m_SamplerStateName;
		std::shared_ptr<StructuredBuffer> m_LightBuffer;
		std::vector<Light>& m_Lights;

		std::shared_ptr<StructuredBuffer> g_pLightStructuredBuffer;

		// Bind the constant to the shader.
		void BindSamplerState(const std::string& paramName);
		void BindMaterialBuffer(const std::string& paramName);
		void BindLightBuffer(const std::string& lightBuffer);
	};
}