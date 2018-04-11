#pragma once
#include "BasePass.h"
#include <Graphics\Light.h>

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
		

		void SetSampler(std::shared_ptr<SamplerState> samp,const std::string& name);
		void SetLight(std::shared_ptr<StructuredBuffer> buffer, const std::string& name);

		virtual void PreRender(RenderEventArgs& e) override;
		virtual void Render(RenderEventArgs& e) override;

		virtual void Visit(Mesh& mesh) override;

	protected:
		const Light* GetCurrentLight();
		const uint32_t GetCurrentLightIndex();
	private:
		std::shared_ptr<SamplerState> m_SamplerState;
		std::string m_SamplerStateName;
		std::shared_ptr<StructuredBuffer> m_LightBuffer;
		std::vector<Light>& m_Lights;

		// The light we are currently rendering.
		Light* m_pCurrentLight;
		uint32_t m_uiLightIndex;

		std::shared_ptr<Material> m_LightMaterial;

		std::shared_ptr<Scene> m_PointLightScene;
		std::shared_ptr<Scene> m_pSpotLightScene;
		std::shared_ptr<Scene> m_pDirectionalLightScene;


		std::shared_ptr<StructuredBuffer> g_pLightStructuredBuffer;

		// Bind the constant to the shader.
		void BindSamplerState(const std::string& paramName);
		//void BindMaterialBuffer(const std::string& paramName);
		void BindLightBuffer(const std::string& lightBuffer);
	};
}