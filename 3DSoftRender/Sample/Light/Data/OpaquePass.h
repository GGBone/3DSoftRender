#pragma once
#include "BasePass.h"

namespace Hikari
{
	class OpaquePass : public BasePass
	{
	public:
		OpaquePass(Renderer* render, Scene* scene, PipelineState* pipeline);

		virtual ~OpaquePass();
		

		void SetSampler(SamplerState* samp,const std::string& name);
		void SetLight(StructuredBuffer* buffer, const std::string& name);

		virtual void Visit(Mesh& mesh) override;

	private:
		SamplerState* m_SamplerState;
		std::string m_SamplerStateName;
		StructuredBuffer* m_LightBuffer;

		// Bind the constant to the shader.
		void BindSamplerState(const std::string& paramName);
		//void BindMaterialBuffer(const std::string& paramName);
		void BindLightBuffer(const std::string& lightBuffer);
	};
}