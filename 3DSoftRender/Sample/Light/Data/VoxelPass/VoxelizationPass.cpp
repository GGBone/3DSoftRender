#include "ShaderEffect/VoxelDefine.h"
#include "VoxelizationPass.h"
#include "Renderer/Renderer.h"
#include "Resource/RasterizerState.h"
#include "Resource/PipelineState.h"
#include "SceneGraph/Scene.h"
#include "Algebra/HMatrix.h"
#include "SceneGraph/Node.h"

using namespace Hikari;
bool VoxelizationPass::init = false;

VoxelizationPass::VoxelizationPass(std::shared_ptr<Renderer> render)
	: m_PerObjectConstantBuffer(nullptr),
	  m_PerGeometryConstantBuffer(nullptr),
	  m_AttriConstantBuffer(nullptr),
	  m_pRenderEventArgs(nullptr),
	  m_Pipeline(nullptr),
	  m_Scene(nullptr),
	  m_RenderDevice(render)
{
	m_PerObjData = PerObject();
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerObjData);

	m_PerGeomData = PerGeometry();
	m_PerGeometryConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerGeomData);

	m_AttrData = Attri();
	m_AttriConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_AttrData);
}

VoxelizationPass::VoxelizationPass(std::shared_ptr<Renderer> render, std::shared_ptr<Scene> scene,
                                   std::shared_ptr<PipelineState> pipeline)
	: m_PerObjectConstantBuffer(nullptr),
	  m_PerGeometryConstantBuffer(nullptr),
	  //m_PerObjectData(nullptr),
	  m_AttriConstantBuffer(nullptr),
	  m_pRenderEventArgs(nullptr),
	  m_Pipeline(pipeline),
	  m_Scene(scene),
	  m_RenderDevice(render)
{
	m_PerObjData = PerObject();
	m_sPerObjCBName = "cbTrans";
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerObjData);

	m_PerGeomData = PerGeometry();
	m_PerGeometryConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerGeomData);

	m_AttrData = Attri();
	m_AttriConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_AttrData);
}

VoxelizationPass::~VoxelizationPass()
{
	//_aligned_free(m_PerObjectData);

	m_RenderDevice->destroy_constant_buffer(m_PerObjectConstantBuffer);

	m_RenderDevice->destroy_constant_buffer(m_PerGeometryConstantBuffer);

	m_RenderDevice->destroy_constant_buffer(m_AttriConstantBuffer);
}

void VoxelizationPass::PreRender(RenderEventArgs& e)
{
	e.PipelineState = m_Pipeline.get();
	if (init)
		return;
	SetRenderEventArgs(e);
	if (m_Pipeline)
	{
		m_Pipeline->GetRasterizerState().SetViewport(Viewport(0, 0, MaxLevelRes, MaxLevelRes));
		BindPerObjectConstantBuffer(m_sPerObjCBName);
		m_Pipeline->bind();
	}
}

void VoxelizationPass::Render(RenderEventArgs& e)
{
	if (init)
		return;
	if (m_Scene)
	{
		m_Scene->Accept(*this);
	}
}

void VoxelizationPass::PostRender(RenderEventArgs& e)
{
	if (init)
		return;
	if (m_Pipeline)
	{
		auto index = m_Pipeline->GetRenderTarget()->GetBuffer(0);

		//for debug copy in a staging buffer
		index->copy_buffer_data();
		//m_Pipeline->unbind();
		init = true;
	}
}

void VoxelizationPass::Visit(Scene& scene)
{
}

void VoxelizationPass::Visit(Node& node)
{
	HMatrix temp = node.GetWorldTransform();
	XMMATRIX worldTransform = XMMatrixSet(temp[0][0], temp[0][1], temp[0][2], temp[0][3],
	                                      temp[1][0], temp[1][1], temp[1][2], temp[1][3],
	                                      temp[2][0], temp[2][1], temp[2][2], temp[2][3],
	                                      temp[3][0], temp[3][1], temp[3][2], temp[3][3]);

	m_PerObjData.world = worldTransform;
	SetPerObjectConstantData(m_PerObjData, m_sPerObjCBName);
}

void VoxelizationPass::Visit(Mesh& mesh)
{
	std::shared_ptr<Material> pMaterial = mesh.GetMaterial();
	if (pMaterial.get())
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}

void VoxelizationPass::SetRenderEventArgs(RenderEventArgs& e)
{
	m_pRenderEventArgs = std::make_shared<RenderEventArgs>(e);
}


std::shared_ptr<Renderer> VoxelizationPass::GetRenderDevice() const
{
	return m_RenderDevice;
}

void VoxelizationPass::SetPerObjectConstantData(PerObject& perObjectData, const std::string& name)
{
	assert(m_PerObjectConstantBuffer);
#if _DEBUG
	m_PerObjData = perObjectData;
#endif
	m_PerObjectConstantBuffer->set(perObjectData);
	BindPerObjectConstantBuffer(name);
}

void VoxelizationPass::BindPerObjectConstantBuffer(const std::string& name)
{
	m_Pipeline->GetShader(Shader::VertexShader)->GetShaderParameterByName(name).set(m_PerObjectConstantBuffer);
}

void VoxelizationPass::SetPerGeometryConstantData(PerGeometry& perGeomData, const std::string& name)
{
	assert(m_PerGeometryConstantBuffer);
#if _DEBUG
	m_PerGeomData = perGeomData;
#endif
	m_PerGeometryConstantBuffer->set(perGeomData);
	BindPerGeometryConstantBuffer(name);
}

void VoxelizationPass::BindPerGeometryConstantBuffer(const std::string& name)
{
	m_Pipeline->GetShader(Shader::GeometryShader)->GetShaderParameterByName(name).set(m_PerGeometryConstantBuffer);
}

void VoxelizationPass::SetAttriConstantData(Attri& attrData, const std::string& name)
{
	assert(m_AttriConstantBuffer);
#if _DEBUG
	m_AttrData = attrData;
#endif
	m_AttriConstantBuffer->set(attrData);
	BindAttriConstantBuffer(name);
}


void VoxelizationPass::BindAttriConstantBuffer(const std::string& name)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).set(m_AttriConstantBuffer);
}


void VoxelizationPass::BindSampler(const std::string& name)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).set(m_Sampler);
}

void VoxelizationPass::SetSampler(std::shared_ptr<SamplerState>& samp, const std::string& name)
{
	m_Sampler = samp;
	BindSampler(name);
}
