#include "VoxelizationPass.h"
#include "Renderer.h"
#include "RenderEventArgs.h"
#include "PipelineState.h"
#include "RasterizerState.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "Node.h"
#include "StructuredBuffer.h"
#include "Scene.h"
#include "Dx11Renderer.h"
#include "RenderTarget.h"
#include "Buffer.h"
#include "RWBuffer.h"
using namespace Hikari;
Hikari::VoxelizationPass::VoxelizationPass(Renderer * render)
:m_RenderDevice(render),
m_pRenderEventArgs(nullptr),
m_PerObjectData(nullptr),
m_PerObjectConstantBuffer(nullptr),
m_Pipeline(nullptr),
m_Scene(nullptr)
{
	m_PerObjectData = (PerObject*)_aligned_malloc(sizeof(PerObject), 16);
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());
	
	//m_pGeometryData = (PerGeometry*)_aligned_malloc(sizeof(PerGeometry), 16);
	m_PerGeometryConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerGeometry());

	//m_Attri = (cbAttri*)_aligned_malloc(sizeof(cbAttri), 16);
	m_AttriConstantBuffer = m_RenderDevice->CreateConstantBuffer(cbAttri());

}

Hikari::VoxelizationPass::VoxelizationPass(Renderer * render, Scene * scene, PipelineState * pipeline)
	:m_RenderDevice(render),
	m_pRenderEventArgs(nullptr),
	//m_PerObjectData(nullptr),
	m_PerObjectConstantBuffer(nullptr),
	m_Pipeline(pipeline),
	m_Scene(scene)
{
	m_PerObjectData = (PerObject*)_aligned_malloc(sizeof(PerObject), 16);
	m_PerObjectConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerObject());

	//m_pGeometryData = (PerGeometry*)_aligned_malloc(sizeof(PerGeometry), 16);
	m_PerGeometryConstantBuffer = m_RenderDevice->CreateConstantBuffer(PerGeometry());

	//m_Attri = (cbAttri*)_aligned_malloc(sizeof(cbAttri), 16);
	m_AttriConstantBuffer = m_RenderDevice->CreateConstantBuffer(cbAttri());

}

Hikari::VoxelizationPass::~VoxelizationPass()
{
	_aligned_free(m_PerObjectData);
	m_RenderDevice->DestroyConstantBuffer(m_PerObjectConstantBuffer);

	//_aligned_free(m_pGeometryData);
	m_RenderDevice->DestroyConstantBuffer(m_PerGeometryConstantBuffer);

	//_aligned_free(m_Attri);
	m_RenderDevice->DestroyConstantBuffer(m_AttriConstantBuffer);

}

void Hikari::VoxelizationPass::PreRender(RenderEventArgs & e)
{
	e.PipelineState = m_Pipeline;
	SetRenderEventArgs(e);
	if (m_Pipeline)
	{
		m_Pipeline->GetRasterizerState().SetViewport(Viewport(0, 0, 2.0f, 2.0f));
		BindPerObjectConstantBuffer("cbTrans");
		m_Pipeline->Bind();
	}
}

void Hikari::VoxelizationPass::Render(RenderEventArgs & e)
{
	if (m_Scene)
	{
		m_Scene->Accept(*this);
	}
}

void Hikari::VoxelizationPass::PostRender(RenderEventArgs & e)
{
	if (m_Pipeline)
	{
		/*StructuredBuffer* uavFragment =  m_Pipeline->GetRenderTarget()->GetStructuredBuffer(0);
		RWBuffer* index = m_Pipeline->GetRenderTarget()->GetRWBuffer(0);
		
		index->Copy(nullptr)*/
		m_Pipeline->UnBind();
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

	m_PerObjectData->world = worldTransform;
	SetPerObjectConstantBufferData(*m_PerObjectData);
}

void Hikari::VoxelizationPass::Visit(Mesh & mesh)
{
	Material* pMaterial = mesh.GetMaterial();
	if (pMaterial && m_pRenderEventArgs)
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}

void Hikari::VoxelizationPass::SetRenderEventArgs(RenderEventArgs & e)
{
	m_pRenderEventArgs = &e;
}

RenderEventArgs & Hikari::VoxelizationPass::GetRenderEventArgs() const
{
	return *m_pRenderEventArgs;
}

Renderer * Hikari::VoxelizationPass::GetRenderDevice() const
{
	return m_RenderDevice;
}

void Hikari::VoxelizationPass::SetPerObjectConstantBufferData(PerObject & perObjectData)
{
	m_PerObjectConstantBuffer->Set(perObjectData);
}

void Hikari::VoxelizationPass::BindPerObjectConstantBuffer(const std::string& name)
{

	m_Pipeline->GetShader(Shader::VertexShader)->GetShaderParameterByName(name).Set(m_PerObjectConstantBuffer);

}

void Hikari::VoxelizationPass::SetPerGeometryConstantBufferData(PerGeometry & perObjectData)
{
	m_PerGeometryConstantBuffer->Set(perObjectData);
}

void Hikari::VoxelizationPass::BindPerGeometryConstantBuffer(const std::string& name)
{
	m_Pipeline->GetShader(Shader::GeometryShader)->GetShaderParameterByName(name).Set(m_PerGeometryConstantBuffer);

}

void Hikari::VoxelizationPass::SetCbAttriConstantBufferData(ConstantBuffer* perObjectData,const std::string& name)
{
	m_AttriConstantBuffer = perObjectData;
	BindCbAttriConstantBuffer(name);
}

void Hikari::VoxelizationPass::BindCbAttriConstantBuffer(const std::string& name)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).Set(m_AttriConstantBuffer);
}


void Hikari::VoxelizationPass::BindVoxelStructuredBuffer(const std::string & name)
{
	//m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).Set(m_VoxelBuffer);

}

void Hikari::VoxelizationPass::BindVoxelIndexStructuredBuffer(const std::string & name)
{
	//m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).Set(m_VoxelIndexBuffer);
}

void Hikari::VoxelizationPass::BindSampler(const std::string & name)
{
	m_Pipeline->GetShader(Shader::PixelShader)->GetShaderParameterByName(name).Set(m_Sampler);

}

void Hikari::VoxelizationPass::SetSampler(SamplerState * samp, const std::string & name)
{
	m_Sampler = samp;
	BindSampler(name);
}

void Hikari::VoxelizationPass::SetGeometryConstantBuffer(ConstantBuffer * buffer, const std::string & name)
{
	m_PerGeometryConstantBuffer = buffer;
	BindPerGeometryConstantBuffer(name);
}

void Hikari::VoxelizationPass::SetVoxelBuffer(StructuredBuffer * buffer, const std::string & name)
{
	m_VoxelBuffer = buffer;
	//BindVoxelStructuredBuffer(name);
}

void Hikari::VoxelizationPass::SetIndexBuffer(RWBuffer * buffer, const std::string & name)
{
	m_VoxelIndexBuffer = buffer;
	//BindVoxelIndexStructuredBuffer(name);
}
