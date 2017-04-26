#include "LightPass.h"
#include "Scene.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Material.h"
#include "RenderEventArgs.h"
#include "Node.h"
#include "PipelineState.h"
using namespace Hikari;
Hikari::LightsPass::LightsPass(Renderer* renderer,std::vector<Light>& lights, Scene * pointLight, Scene * spotLight, Scene * directionalLight, PipelineState * pipeline)
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
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName("Lights").Set(g_pLightStructuredBuffer);
	BasePass::PreRender(e);
}

void Hikari::LightsPass::Render(RenderEventArgs & e)
{
	m_uiLightIndex = 0;
	for (Light& light : m_Lights)
	{
		m_pCurrentLight = &light;
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
	Material* temp = mesh.GetMaterial();
	mesh.SetMaterial(m_LightMaterial);
	mesh.Render(GetRenderEventArgs());
	mesh.SetMaterial(temp);
}

const Light * Hikari::LightsPass::GetCurrentLight()
{
	return m_pCurrentLight;
}

const uint32_t Hikari::LightsPass::GetCurrentLightIndex()
{
	return m_uiLightIndex;
}
