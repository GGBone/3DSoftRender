#include "BasePass.h"
#include "Resource/RasterizerState.h"
#include "Resource/ConstantBuffer.h"
#include "Shader/Shader.h"
#include "Resource/PipelineState.h"
#include "SceneGraph/Scene.h"
#include "Algebra/HMatrix.h"
#include "SceneGraph/Camera.h"
#include "SceneGraph/Mesh.h"
#include "SceneGraph/Node.h"
#include "Shader/ShaderParameter.h"
#include "Renderer/Renderer.h"

using namespace Hikari;

BasePass::BasePass(const std::shared_ptr<Renderer>& render)
	: m_pRenderEventArgs(nullptr),
	  m_RenderDevice(render)
{
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());
}

BasePass::BasePass(const std::shared_ptr<Renderer>& render, const std::shared_ptr<Scene>& scene,
                   const std::shared_ptr<PipelineState>& pipeline)
	: m_pRenderEventArgs(nullptr)
	  , m_Pipeline(pipeline)
	  , m_Scene(scene)
	  , m_RenderDevice(render)
{
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());
}

BasePass::~BasePass()
{
	m_RenderDevice->destroy_constant_buffer(m_PerObjectConstantBuffer);
}

void BasePass::SetPerObjectConstantBufferData(PerObject& perObjectData)
{
	m_PerObjectConstantBuffer.get()->set(perObjectData);
}

void BasePass::BindPerObjectConstantBuffer(std::shared_ptr<Shader> shader)
{
	if (shader)
	{
		shader->GetShaderParameterByName("PerObject").set(m_PerObjectConstantBuffer);
	}
}


void BasePass::PreRender(RenderEventArgs& e)
{
	e.PipelineState = m_Pipeline.get();

	SetRenderEventArgs(e);
	if (m_Pipeline)
	{
		BindPerObjectConstantBuffer(m_Pipeline->GetShader(Shader::VertexShader));
		m_Pipeline->bind();
	}
	else
	{
		DebugBreak();
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
		m_Pipeline->unbind();
		e.PipelineState = {};
#endif
	}
	else
	{
		DebugBreak();
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
		perObjectData.ModelView = XMMatrixMultiply(worldTransform, viewMatrix);

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

std::shared_ptr<Renderer> BasePass::GetRenderDevice() const
{
	return m_RenderDevice;
}
