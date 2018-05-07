#include "ShaderEffect\VoxelDefine.h"
#include "VoxelizationPass.h"
#include "Graphics\Renderer.h"
#include "Graphics\PipelineState.h"
#include "Graphics\RasterizerState.h"
#include "Graphics\Mesh.h"
#include "Graphics\ConstantBuffer.h"
#include "Graphics\Node.h"
#include "Graphics\StructuredBuffer.h"
#include "Graphics\Scene.h"
#include "Graphics\Dx11Renderer.h"
#include "Graphics\RenderTarget.h"
#include "Graphics\Buffer.h"
#include "Graphics\Buffer.h"
using namespace Hikari;
bool VoxelizationPass::init = false;
Hikari::VoxelizationPass::VoxelizationPass(std::shared_ptr<Renderer> render)
:m_RenderDevice(render),
m_pRenderEventArgs(nullptr),
m_PerObjectConstantBuffer(nullptr),
m_Pipeline(nullptr),
m_Scene(nullptr),
m_PerGeometryConstantBuffer(nullptr),
m_AttriConstantBuffer(nullptr)
{

	m_PerObjData = PerObject();
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerObjData);

	m_PerGeomData = PerGeometry();
	m_PerGeometryConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerGeomData);

	m_AttrData = Attri();
	m_AttriConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_AttrData);
}

Hikari::VoxelizationPass::VoxelizationPass(std::shared_ptr<Renderer> render, std::shared_ptr<Scene> scene, std::shared_ptr<PipelineState> pipeline)
	:m_RenderDevice(render),
	m_pRenderEventArgs(nullptr),
	//m_PerObjectData(nullptr),
	m_PerObjectConstantBuffer(nullptr),
	m_Pipeline(pipeline),
	m_Scene(scene),
	m_PerGeometryConstantBuffer(nullptr),
	m_AttriConstantBuffer(nullptr)
{
	m_PerObjData = PerObject();
	m_sPerObjCBName = "cbTrans";
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerObjData);

	m_PerGeomData = PerGeometry();
	m_PerGeometryConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_PerGeomData);

	m_AttrData = Attri();
	m_AttriConstantBuffer = m_RenderDevice->CreateConstantBuffer(m_AttrData);
}

Hikari::VoxelizationPass::~VoxelizationPass()
{
	//_aligned_free(m_PerObjectData);

	m_RenderDevice->DestroyConstantBuffer(m_PerObjectConstantBuffer);

	m_RenderDevice->DestroyConstantBuffer(m_PerGeometryConstantBuffer);

	m_RenderDevice->DestroyConstantBuffer(m_AttriConstantBuffer);

}

void Hikari::VoxelizationPass::PreRender(RenderEventArgs & e)
{
	e.PipelineState = m_Pipeline.get();
	if (init)
		return;
	SetRenderEventArgs(e);
	if (m_Pipeline)
	{
		m_Pipeline->GetRasterizerState().SetViewport(Viewport(0, 0, MaxLevelRes, MaxLevelRes));
		BindPerObjectConstantBuffer(m_sPerObjCBName);
		m_Pipeline->Bind();
	}
}

void Hikari::VoxelizationPass::Render(RenderEventArgs & e)
{
	if (init)
		return;
	if (m_Scene)
	{
		m_Scene->Accept(*this);
	}
}

void Hikari::VoxelizationPass::PostRender(RenderEventArgs & e)
{
	if (init)
		return;
	if (m_Pipeline)
	{
		auto index = m_Pipeline->GetRenderTarget()->GetBuffer(0);
		
		index->CopyBufferData();
		//m_Pipeline->UnBind();
		init = true;
	}
}

void Hikari::VoxelizationPass::Visit(Scene & scene)
{
}

void Hikari::VoxelizationPass::Visit(Node & node)
{

	HMatrix temp = node.GetWorldTransform();
	XMMATRIX worldTransform = XMMatrixSet(temp[0][0], temp[0][1], temp[0][2], temp[0][3],
		temp[1][0], temp[1][1], temp[1][2], temp[1][3],
		temp[2][0], temp[2][1], temp[2][2], temp[2][3],
		temp[3][0], temp[3][1], temp[3][2], temp[3][3]);

	m_PerObjData.world = worldTransform;
	SetPerObjectConstantData(m_PerObjData, m_sPerObjCBName);
}

void Hikari::VoxelizationPass::Visit(Mesh & mesh)
{
	std::shared_ptr<Material> pMaterial = mesh.GetMaterial();
	if (pMaterial.get())
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}

void Hikari::VoxelizationPass::SetRenderEventArgs( RenderEventArgs & e)
{
	m_pRenderEventArgs = std::make_shared<RenderEventArgs>(e);
}


std::shared_ptr<Renderer> Hikari::VoxelizationPass::GetRenderDevice() const
{
	return m_RenderDevice;
}

void Hikari::VoxelizationPass::SetPerObjectConstantData(PerObject& perObjectData, const std::string& name)
{
	assert(m_PerObjectConstantBuffer);
#if _DEBUG
	m_PerObjData = perObjectData;
#endif
	m_PerObjectConstantBuffer->Set(perObjectData);
	BindPerObjectConstantBuffer(name);
}

void Hikari::VoxelizationPass::BindPerObjectConstantBuffer(const std::string& name)
{

	m_Pipeline->GetShader(Shader::VertexShader)->GetShaderParameterByName(name).Set(m_PerObjectConstantBuffer);

}

void Hikari::VoxelizationPass::SetPerGeometryConstantData(PerGeometry& perGeomData, const std::string& name)
{
	assert(m_PerGeometryConstantBuffer);
#if _DEBUG
	m_PerGeomData = perGeomData;
#endif
	m_PerGeometryConstantBuffer->Set(perGeomData);
	BindPerGeometryConstantBuffer(name);
}

void Hikari::VoxelizationPass::BindPerGeometryConstantBuffer(const std::string& name)
{
	m_Pipeline->GetShader(Shader::GeometryShader)->GetShaderParameterByName(name).Set(m_PerGeometryConstantBuffer);
}

void Hikari::VoxelizationPass::SetAttriConstantData(Attri& attrData, const std::string& name)
{
	assert(m_AttriConstantBuffer);
#if _DEBUG
	m_AttrData = attrData;
#endif
	m_AttriConstantBuffer->Set(attrData);
	BindAttriConstantBuffer(name);
}


void Hikari::VoxelizationPass::BindAttriConstantBuffer(const std::string& name)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).Set(m_AttriConstantBuffer);
}


void Hikari::VoxelizationPass::BindSampler(const std::string& name)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).Set(m_Sampler);
}

void Hikari::VoxelizationPass::SetSampler(std::shared_ptr<SamplerState>& samp, const std::string & name)
{
	m_Sampler = samp;
	BindSampler(name);
}
