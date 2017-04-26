#include <GraphicsPCH.h>


#include <Scene.h>
#include <Node.h>
#include <Mesh.h>
#include <Material.h>
#include <PipelineState.h>
#include <Shader.h>
#include <ShaderParameter.h>
#include <Camera.h>
#include <ConstantBuffer.h>

#include <RenderEventArgs.h>
#include <BasePass.h>
using namespace Hikari;
BasePass::BasePass(Renderer* render)
	: m_pRenderEventArgs(nullptr),
	m_RenderDevice(render)
{
	m_PerObjectData = (PerObject*)_aligned_malloc(sizeof(PerObject), 16);
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());
}

BasePass::BasePass(Renderer* render,Scene* scene, PipelineState* pipeline)
	: m_pRenderEventArgs(nullptr)
	, m_Scene(scene)
	, m_Pipeline(pipeline)
	, m_RenderDevice(render)
{
	m_PerObjectData = (PerObject*)_aligned_malloc(sizeof(PerObject), 16);
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());
}

BasePass::~BasePass()
{
	_aligned_free(m_PerObjectData);
	m_RenderDevice->DestroyConstantBuffer(m_PerObjectConstantBuffer);
}

void BasePass::SetPerObjectConstantBufferData(PerObject& perObjectData)
{
	m_PerObjectConstantBuffer->Set(perObjectData);
}

void BasePass::BindPerObjectConstantBuffer(Shader* shader)
{
	if (shader)
	{
		shader->GetShaderParameterByName("PerObject").Set(m_PerObjectConstantBuffer);
	}
}



void BasePass::PreRender(RenderEventArgs& e)
{
	e.PipelineState = m_Pipeline;
	SetRenderEventArgs(e);

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
		m_Pipeline->UnBind();
	}
}

// Inherited from Visitor
void BasePass::Visit(Scene& scene)
{

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

		perObjectData.ModelViewProjection = camera->ViewProj();

		// Update the constant buffer data
		SetPerObjectConstantBufferData(perObjectData);
	}
}

void BasePass::Visit(Mesh& mesh)
{
	Material* pMaterial = mesh.GetMaterial();
	if (pMaterial && m_pRenderEventArgs)
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}

void BasePass::SetRenderEventArgs(RenderEventArgs& e)
{
	m_pRenderEventArgs = &e;
}

RenderEventArgs& BasePass::GetRenderEventArgs() const
{
	assert(m_pRenderEventArgs);
	return *m_pRenderEventArgs;
}

Renderer * Hikari::BasePass::GetRenderDevice() const
{
	return m_RenderDevice;
}

