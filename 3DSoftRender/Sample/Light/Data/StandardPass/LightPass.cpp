//Opaque Pass
#include "Application\WindowApplicationEngine.h"
#include "LightPass.h"
#include "Graphics\Scene.h"
#include "Graphics\Mesh.h"
#include "Graphics\Renderer.h"
#include "Graphics\Material.h"
#include "Graphics\Node.h"
#include "Graphics\PipelineState.h"
#include "Graphics\StructuredBuffer.h"
#include "Loader\Loader.h"
using namespace Hikari;

Hikari::LightsPass::LightsPass(std::shared_ptr<Renderer> renderer,std::vector<Light>& lights, 
	std::shared_ptr<Scene> pointLight, std::shared_ptr<Scene> spotLight, std::shared_ptr<Scene> directionalLight,
	std::shared_ptr<PipelineState> pipeline)
	:BasePass(renderer,nullptr,pipeline),
	m_Lights(lights),
	m_pCurrentLight(nullptr),
	m_uiLightIndex(-1),
	m_RenderDevice(renderer),
	m_Pipeline(pipeline),
	m_pSpotLightScene(spotLight),
	m_PointLightScene(pointLight),
	m_pDirectionalLightScene(directionalLight)
{
	m_LightMaterial = renderer->CreateMaterial();
	g_pLightStructuredBuffer = renderer->CreateStructuredBuffer(lights, CPUAccess::Write);

}

Hikari::LightsPass::~LightsPass()
{
}

void Hikari::LightsPass::PreRender(RenderEventArgs & e)
{
	XMMATRIX viewMatrix = e.Camera->View();

	// Update the viewspace vectors of the light.
	for (unsigned int i = 0; i < WindowApplicationEngine::g_Setting.Lights.size(); i++)
	{
		// Update the lights so that their position and direction are in view space.
		Light& light = WindowApplicationEngine::g_Setting.Lights[i];
		XMVECTOR lightWS = XMVectorSet(light.m_PositionWS[0], light.m_PositionWS[1], light.m_PositionWS[2], light.m_PositionWS[3]);
		XMVECTOR lightVS = XMVector3TransformCoord(lightWS, viewMatrix);
		XMFLOAT4 temp;
		XMStoreFloat4(&temp, lightVS);

		light.m_DirectionVS = Float4(temp.x, temp.y, temp.z, temp.w);

	}
	g_pLightStructuredBuffer->Set(WindowApplicationEngine::g_Setting.Lights);
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName("Lights").Set(g_pLightStructuredBuffer);
	BasePass::PreRender(e);
}

void Hikari::LightsPass::Render(RenderEventArgs & e)
{
	m_uiLightIndex = 0;
	for each (Light light in m_Lights)
	{
		m_pCurrentLight = &light;
		m_pCurrentLight->m_Selected = true;
		float a = light.m_Enabled ? 0.5f: 0.1f;
		a = light.m_Selected ? 0.9f : a;
		m_LightMaterial->SetDiffuseColor(light.m_Color);
		m_LightMaterial->SetOpacity(a);

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

void Hikari::LightsPass::Visit(Scene & scene)
{
}

void Hikari::LightsPass::Visit(Node & node)
{
	Camera* camera = GetRenderEventArgs().Camera;
	PerObject perObject;
	HMatrix nodeTransform = node.GetWorldTransform();
 	XMMATRIX translate =XMMatrixTranslation( m_pCurrentLight->m_PositionWS[0], m_pCurrentLight->m_PositionWS[1], m_pCurrentLight->m_PositionWS[2]);
	//XMMATRIX rotation = 
	perObject.ModelView = camera->View();
	perObject.ModelViewProjection = camera->Proj() * perObject.ModelView;
	SetPerObjectConstantBufferData(perObject);
}

void Hikari::LightsPass::Visit(Mesh & mesh)
{
	std::shared_ptr<Material> temp = mesh.GetMaterial();
	mesh.SetMaterial(m_LightMaterial);
	mesh.Render(GetRenderEventArgs());
	mesh.SetMaterial(temp);
}

const Light* Hikari::LightsPass::GetCurrentLight()
{
	return m_pCurrentLight;
}

const uint32_t Hikari::LightsPass::GetCurrentLightIndex()
{
	return m_uiLightIndex;
}
