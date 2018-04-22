#include <Graphics\GraphicsPCH.h>
#include <Graphics\Scene.h>
#include <Graphics\Node.h>
#include <Graphics\Mesh.h>
#include <Graphics\Material.h>
#include <Graphics\PipelineState.h>
#include <Graphics\Shader.h>
#include <Graphics\ShaderParameter.h>
#include <Graphics\Camera.h>
#include <Graphics\ConstantBuffer.h>
#include "BasePass.h"

using namespace Hikari;
BasePass::BasePass(std::shared_ptr<Renderer> render)
	: m_pRenderEventArgs(nullptr),
	m_RenderDevice(render)
{
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());
}

BasePass::BasePass(std::shared_ptr<Renderer> render, std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline)
	: m_pRenderEventArgs(nullptr)
	, m_Scene(scene)
	, m_Pipeline(pipeline)
	, m_RenderDevice(render)
{
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());
}

BasePass::~BasePass()
{
	m_RenderDevice->DestroyConstantBuffer(m_PerObjectConstantBuffer);
}

void BasePass::SetPerObjectConstantBufferData(PerObject& perObjectData)
{
	m_PerObjectConstantBuffer.get()->Set(perObjectData);
}

void BasePass::BindPerObjectConstantBuffer(std::shared_ptr<Shader> shader)
{
	if (shader)
	{
		shader->GetShaderParameterByName("PerObject").Set(m_PerObjectConstantBuffer);
	}
}



void BasePass::PreRender(RenderEventArgs& e)
{
	e.PipelineState = m_Pipeline.get();

	SetRenderEventArgs(e);
	std::vector<Viewport> vport = e.PipelineState->GetRasterizerState().GetViewports();
	if (m_Pipeline)
	{	
		m_Pipeline->GetRasterizerState().SetViewport(Viewport(0,0,1280,760,0.0f,1.0f));
		BindPerObjectConstantBuffer(m_Pipeline->GetShader(Shader::VertexShader));
		m_Pipeline->Bind();
	}
}

void BasePass::Render(RenderEventArgs& e)
{
	if (m_Scene)
	{
		m_Scene->Accept(*this);
	}
}

void BasePass::PostRender(RenderEventArgs& e)
{
	if (m_Pipeline)
	{
#if defined(VOXEL)
#else
		//m_Pipeline->UnBind();
#endif
	}
}

// Inherited from Visitor
void BasePass::Visit(Scene& scene)
{
	//Check the scene file if it has beed modify or delete to avoid crash.
}

void BasePass::Visit(Node& node)
{
	Camera* camera = GetRenderEventArgs().Camera;
	if (camera)
	{
		PerObject perObjectData;
		// Update the constant buffer data for the node.
		XMMATRIX viewMatrix = camera->View();
		HMatrix temp = node.GetWorldTransform();
		XMMATRIX worldTransform = XMMatrixSet(temp[0][0], temp[0][1], temp[0][2], temp[0][3],
			temp[1][0], temp[1][1], temp[1][2], temp[1][3],
			temp[2][0], temp[2][1], temp[2][2], temp[2][3],
			temp[3][0], temp[3][1], temp[3][2], temp[3][3]);
		perObjectData.ModelView = XMMatrixMultiply(viewMatrix, worldTransform);

		perObjectData.ModelViewProjection = XMMatrixMultiply(perObjectData.ModelView, camera->Proj());

		// Update the constant buffer data
		SetPerObjectConstantBufferData(perObjectData);
	}
}

void BasePass::Visit(Mesh& mesh)
{
	std::shared_ptr<Material> pMaterial = mesh.GetMaterial();
	if (pMaterial && m_pRenderEventArgs)
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}

void BasePass::SetRenderEventArgs(RenderEventArgs& e)
{
	m_pRenderEventArgs = std::make_shared<RenderEventArgs>(e);
}

RenderEventArgs& BasePass::GetRenderEventArgs() const
{
	assert(m_pRenderEventArgs);
	return *m_pRenderEventArgs;
}

std::shared_ptr<Renderer> Hikari::BasePass::GetRenderDevice() const
{
	return m_RenderDevice;
}

