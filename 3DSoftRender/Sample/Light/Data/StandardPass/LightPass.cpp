//Opaque Pass
#include "WindowApplicationEngine.h"
#include "LightPass.h"
#include "Loader.h"
#include "Renderer/Renderer.h"
#include "Resource/PipelineState.h"
#include "SceneGraph/Scene.h"
using namespace Hikari;


LightsPass::LightsPass(std::shared_ptr<Renderer> renderer, std::shared_ptr<Scene> pointLight,
                       shared_ptr<PipelineState> pipeline)
	: BasePass(renderer, pointLight, pipeline)
	  , m_Lights(WindowApplicationEngine::g_Setting.Lights)
{
	const ShaderParameter::ShaderInputParameter light_struct_buffer =
	{
		ShaderParameter::ShaderInputType::StructuredBuffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::UNKNOWN,
		CPUAccess::Write,
		GPUAccess::Read
	};
	g_pLightStructuredBuffer = renderer->CreateStructuredBuffer(m_Lights, light_struct_buffer);
}

LightsPass::~LightsPass()
= default;

void LightsPass::PreRender(RenderEventArgs& e)
{
	//XMMATRIX viewMatrix = e.Camera->View();

	//// Update the viewspace vectors of the light.
	//for (unsigned int i = 0; i < WindowApplicationEngine::g_Setting.Lights.size(); i++)
	//{
	//	// Update the lights so that their position and direction are in view space.
	//	Light& light = WindowApplicationEngine::g_Setting.Lights[i];
	//	XMVECTOR lightPosWS = XMVectorSet(light.m_PositionWS[0], light.m_PositionWS[1], light.m_PositionWS[2], light.m_PositionWS[3]);
	//	XMVECTOR lightPosVS = XMVector3TransformCoord(lightPosWS, viewMatrix);

	//}
	g_pLightStructuredBuffer->set(WindowApplicationEngine::g_Setting.Lights);
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName("Lights").set(g_pLightStructuredBuffer);
	BindPerObjectConstantBuffer(m_Pipeline->GetShader(Shader::PixelShader));
	BasePass::PreRender(e);
}

void LightsPass::Render(RenderEventArgs& e)
{
	m_uiLightIndex = 0;
	for each (Light light in m_Lights)
	{
		m_pCurrentLight = &light;
		m_pCurrentLight->m_Selected = true;

		m_PointLightScene = m_Scene;
		m_pSpotLightScene = m_Scene;
		m_pDirectionalLightScene = m_Scene;
		switch (light.m_Type)
		{
		case Light::LightType::Point:
			m_PointLightScene->Accept(*this);
			break;
		case Light::LightType::Spot:
			m_pSpotLightScene->Accept(*this);
			break;
		case Light::LightType::Directional:
			m_pDirectionalLightScene->Accept(*this);
			break;
		}

		++m_uiLightIndex;
	}
}


void LightsPass::Visit(Mesh& mesh)
{
	mesh.Render(GetRenderEventArgs());
}

const Light* LightsPass::GetCurrentLight()
{
	return m_pCurrentLight;
}

const uint32_t LightsPass::GetCurrentLightIndex()
{
	return m_uiLightIndex;
}

void LightsPass::BindSamplerState(const std::string& paramName)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(paramName).set(m_SamplerState);
}

void LightsPass::BindMaterialBuffer(const std::string& paramName)
{
}

void LightsPass::SetSampler(std::shared_ptr<SamplerState> samp, const std::string& name)
{
	m_SamplerState = samp;
	BindSamplerState(name);
}

void LightsPass::SetLight(std::shared_ptr<StructuredBuffer> buffer, const std::string& name)
{
	m_LightBuffer = buffer;
	BindLightBuffer(name);
}

void LightsPass::BindLightBuffer(const std::string& paramName)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(paramName).set(m_LightBuffer);
}
