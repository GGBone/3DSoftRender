#include "Dx11RenderLIB.h"
#include "FlagOctreePass.h"
#include "Material.h"
#include "Mesh.h"
#include "Dx11Renderer.h"
#include "PipelineState.h"
#include "RenderEventArgs.h"
#include "RenderTarget.h"
#include "RWBuffer.h"
#include "Dx11RWBuffer.h"
#include "Dx11StructureBuffer.h"
using namespace Hikari;
#define PAD16(x) ((x+15) & (~15))

bool FlagOctreePass::init = false;
Hikari::FlagOctreePass::FlagOctreePass(Renderer * render, Scene * scene, PipelineState * pipeline)
	:m_Scene(scene),
	m_RenderDevice(render),
	m_Pipeline(pipeline)
{

}

Hikari::FlagOctreePass::~FlagOctreePass()
{
}


Renderer * Hikari::FlagOctreePass::GetRenderDevice() const
{
	return m_RenderDevice;
}

void Hikari::FlagOctreePass::SetConstantInfo(ConstantBuffer * buffer, const std::string & name)
{
	m_cbInfo = buffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(buffer);

}

void Hikari::FlagOctreePass::SetConstantGroup(ConstantBuffer * buffer, const std::string & name)
{
	m_groupInfo = buffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(buffer);

}

void Hikari::FlagOctreePass::SetConstantBrick(ConstantBuffer * buffer, const std::string & name)
{
	m_BrickInfo = buffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(buffer);

}

void Hikari::FlagOctreePass::SetNodeBuffer(StructuredBuffer * buffer, const std::string & name)
{
	m_NodeBuffer = buffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(buffer);
}

void Hikari::FlagOctreePass::SetNumNode(RWBuffer * rwBuffer, const std::string & name)
{
	m_NumNode = rwBuffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(rwBuffer);

}

void Hikari::FlagOctreePass::SetNodeIndex(RWBuffer * rwBuffer, const std::string & name)
{
	m_NodeIndex = rwBuffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(rwBuffer);

}

void Hikari::FlagOctreePass::SetBrickIndex(RWBuffer * rwBuffer, const std::string & name)
{
	m_BrickInedx = rwBuffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(rwBuffer);

}

void Hikari::FlagOctreePass::SetTotalNode(UINT totalNode)
{
	m_TotalNode = totalNode;
}

void Hikari::FlagOctreePass::SetTotalLevel(UINT totalLevel)
{
	m_TotalLevel = totalLevel;
}


Buffer * Hikari::FlagOctreePass::GetStage() const
{
	return stage;
}

void Hikari::FlagOctreePass::PreRender(RenderEventArgs & e)
{
	if (!init)
	{
		PipelineState* prePipeline = e.PipelineState;
		StructuredBuffer* sBuffer = prePipeline->GetRenderTarget()->GetStructuredBuffer(0);
		RWBuffer* rBuffer = prePipeline->GetRenderTarget()->GetRWBuffer(0);
		m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName("FragmentList").Set(sBuffer);
		m_TotalVoxel = *(UINT*)rBuffer->GetData();
		init = true;
	}
	e.PipelineState = m_Pipeline;
	m_Pipeline->Bind();
	
}

void Hikari::FlagOctreePass::Render(RenderEventArgs & e)
{
	if (init)
	{
		if (m_TotalVoxel == 0)
			return;
		for (UINT level = 0; level < m_TotalLevel; ++level)
		{
			CBInfo cbInfo;
			cbInfo.curLevel = level;
			cbInfo.totalLevel = m_TotalLevel;
			cbInfo.sumVoxels = m_TotalVoxel;
			cbInfo.curNode = 0;
			m_cbInfo->Set(&cbInfo, sizeof(cbInfo));
			UINT sqrtVoxel = (UINT)std::sqrtf((UINT)m_TotalVoxel);

			UINT dd[] = { PAD16(sqrtVoxel) / 16, PAD16(sqrtVoxel) / 16, 1 };
			CBGroupInfo cbGroup;
			cbGroup.groupInfo[0] = dd[0];
			cbGroup.groupInfo[1] = dd[1];
			cbGroup.groupInfo[2] = dd[2];
			m_groupInfo->Set(&cbGroup, sizeof(cbGroup));
			Vector3f group(dd[0], dd[1], 1);
			m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(group);
		}

		
	}
}

void Hikari::FlagOctreePass::PostRender(RenderEventArgs & e)
{
	m_Pipeline->UnBind();
}

void Hikari::FlagOctreePass::Visit(Scene & scene)
{
}

void Hikari::FlagOctreePass::Visit(Hikari::Node & node)
{
}


void Hikari::FlagOctreePass::Visit(Mesh & mesh)
{
	Material* pMaterial = mesh.GetMaterial();
	if (pMaterial && m_pRenderEventArgs)
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}
