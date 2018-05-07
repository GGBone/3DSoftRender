#include "Graphics\Dx11RenderLIB.h"
#include "FlagOctreePass.h"
#include "Graphics\Material.h"
#include "Graphics\Mesh.h"
#include "Graphics\Dx11Renderer.h"
#include "Graphics\PipelineState.h"
#include "Graphics\RenderTarget.h"
#include "Graphics\Buffer.h"
#include "Graphics\Dx11Buffer.h"
#include "Graphics\Dx11StructureBuffer.h"
#include "Graphics\Dx11Texture.h"
#include "Graphics\Dx11ConstantBuffer.h"
#include "Graphics\Dx11Scene.h"
#include "Graphics\Camera.h"
#include "Graphics\Query.h"
#include "ShaderEffect\VoxelDefine.h"
using namespace Hikari;



bool FlagOctreePass::init = false;
Hikari::FlagOctreePass::FlagOctreePass(std::shared_ptr<Renderer> render, std::shared_ptr<Scene>
	 scene, std::shared_ptr<PipelineState> pipeline)
	:m_Scene(scene),
	m_RenderDevice(render),
	m_Pipeline(pipeline),
	m_NodePool(nullptr),	//Initialize when m_TotalNode is set.
	m_cbInfo(nullptr),
	m_groupInfo(nullptr),
	m_BrickInfo(nullptr),
	m_cbAttri(nullptr),
	m_visualPool(nullptr),	//dynamic create
	m_visualIndex(nullptr),
	m_NumNode(nullptr),
	m_NodeIndex(nullptr),
	m_BrickInedx(nullptr)
{
	CBInfo cbInfo;
	m_cbInfo = m_RenderDevice->CreateConstantBuffer(cbInfo);

	CBGroupInfo cbGroupInfo;
	m_groupInfo = m_RenderDevice->CreateConstantBuffer(&cbGroupInfo, PAD16(sizeof(FlagOctreePass::CBGroupInfo)));

	CBBrickInfo cbBrickInfo;
	m_BrickInfo = m_RenderDevice->CreateConstantBuffer(&cbBrickInfo, PAD16(sizeof(FlagOctreePass::CBBrickInfo)));

	VoxelizationPass::Attri attr;
	m_cbAttri = m_RenderDevice->CreateConstantBuffer(attr);

	XMMATRIX matrix;
	m_cbTrans = m_RenderDevice->CreateConstantBuffer(matrix);

	UINT i[] = { 0 };
	m_visualIndex = m_RenderDevice->CreateBuffer(i, 1, sizeof(UINT));


	UINT mTotalLevel = (UINT)std::log2f(MaxLevelRes) + 1;
	std::vector<UINT> initNum;
	initNum.push_back(1);
	for (UINT i = 1; i < mTotalLevel; ++i)
	{
		initNum.push_back(0);
	}
	m_NumNode = m_RenderDevice->CreateBuffer(initNum.data(), (UINT)initNum.size(), sizeof(UINT));

	UINT u_nodeInit = 1;
	m_NodeIndex = m_RenderDevice->CreateBuffer(&u_nodeInit, 1, sizeof(UINT));

	UINT u_brickInit = 0;
	m_BrickInedx = m_RenderDevice->CreateBuffer(&u_brickInit, 1, sizeof(UINT));
}

Hikari::FlagOctreePass::~FlagOctreePass()
{
}


std::shared_ptr<Renderer> Hikari::FlagOctreePass::GetRenderDevice() const
{
	return m_RenderDevice;
}

void Hikari::FlagOctreePass::SetConstantInfo(CBInfo& data, const std::string & name)
{
	assert(m_cbInfo);
	m_cbInfo->Set(data);
	BindConstantInfo(name);
}

void Hikari::FlagOctreePass::SetConstantGroup(CBGroupInfo& data, const std::string & name)
{
	assert(m_groupInfo);
	m_groupInfo->Set(data);
	BindConstantGroup(name);

}

void Hikari::FlagOctreePass::SetConstantBrick(CBBrickInfo& data, const std::string & name)
{
	assert(m_BrickInfo);
	m_BrickInfo->Set(data);
	BindConstantBrick(name);
}

void Hikari::FlagOctreePass::SetAttriConstant(VoxelizationPass::Attri& data, const std::string & name)
{
	assert(m_cbAttri);
	m_cbAttri->Set(data);
	BindAttriConstant(name);

}

void Hikari::FlagOctreePass::SetVisualPool(const std::vector<VisualPackage>& data, const std::string & name)
{
	assert(m_visualPool);
	m_visualPool->Set(data);
	BindVisualPool(name);
}

void Hikari::FlagOctreePass::SetVisualIndex(const std::vector<UINT>& data, const std::string & name)
{
	assert(m_visualIndex);
	m_visualIndex->Set(data);
	BindVisualIndex(name);
}

void Hikari::FlagOctreePass::SetNumOfNodes(std::vector<UINT>& numOfNodes, const std::string & name)
{
	assert(m_NumNode);
	m_NumNode->Set(numOfNodes);
	BindNumOfNodes(name);

}

void Hikari::FlagOctreePass::SetNodeIndex(std::vector<UINT>& nodeIndex, const std::string & name)
{
	assert(m_NodeIndex);
	m_NodeIndex->Set(nodeIndex);
	BindNodeIndex(name);

}

void Hikari::FlagOctreePass::SetBrickIndex(std::vector<UINT>&  data, const std::string & name)
{
	assert(m_BrickInedx);
	m_BrickInedx->Set(data);
	BindBrickIndex(name);

}

void Hikari::FlagOctreePass::SetTotalNode(UINT totalNode)
{
	m_TotalNode = totalNode;

	//Initialize NodesPool
	m_NodePool = m_RenderDevice->CreateStructuredBuffer(nullptr, m_TotalNode, sizeof(FlagOctreePass::Node), CPUAccess::None, true, true);

}

void Hikari::FlagOctreePass::SetTotalLevel(UINT totalLevel)
{
	m_TotalLevel = totalLevel;
}



void Hikari::FlagOctreePass::SetComputeShaders(std::shared_ptr<Shader> ss[],size_t size)
{
	m_shaders.reserve(size);
	for(int i = 0;i<size;++i)
		m_shaders.push_back(ss[i]);

}

void Hikari::FlagOctreePass::BindBrickIndex(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_BrickInedx);
}

void Hikari::FlagOctreePass::BindNodeIndex(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_NodeIndex);
}

void Hikari::FlagOctreePass::BindNumOfNodes(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_NumNode);
}

void Hikari::FlagOctreePass::BindConstantInfo(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_cbInfo);
}

void Hikari::FlagOctreePass::BindConstantGroup(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_groupInfo);
}

void Hikari::FlagOctreePass::BindConstantBrick(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_BrickInfo);
}

void Hikari::FlagOctreePass::BindAttriConstant(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_cbAttri);
}

void Hikari::FlagOctreePass::BindVisualIndex(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_visualIndex);
}

void Hikari::FlagOctreePass::BindVisualPool(const std::string & name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(m_visualPool);
}

void Hikari::FlagOctreePass::PreRender(RenderEventArgs & e)
{
	if (!init)
	{
		assert(m_NodePool);
		m_NodePool->Clear();

		PipelineState* prePipeline = e.PipelineState;
		m_fragmentList = prePipeline->GetRenderTarget()->GetStructuredBuffer(0);
		auto rBuffer = prePipeline->GetRenderTarget()->GetBuffer(0);
		m_TotalVoxel = *(UINT*)rBuffer->GetData();
		prePipeline->UnBind();
	}
	e.PipelineState = m_Pipeline.get();
	m_pRenderEventArgs = std::make_shared<RenderEventArgs>(e);

}

void Hikari::FlagOctreePass::Render(RenderEventArgs & e)
{
	if (!init)
	{	
		if (m_TotalVoxel == 0)
			return;
		CBInfo cbInfo;
		CBGroupInfo cbGroup;
		for (UINT level = 0; level < m_TotalLevel; ++level)
		{
			m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[0]);

			
			cbInfo.curLevel = level;
			cbInfo.totalLevel = m_TotalLevel;
			cbInfo.sumVoxels = m_TotalVoxel;
			cbInfo.curNode = 0;
			m_cbInfo->Set(&cbInfo, sizeof(cbInfo));
			UINT sqrtVoxel = (UINT)std::sqrtf((float)m_TotalVoxel);

			UINT dd[] = { PAD16(sqrtVoxel) / VoxelDispatchUnit, PAD16(sqrtVoxel) / VoxelDispatchUnit, 1 };
			
			cbGroup.groupInfo[0] = dd[0];
			cbGroup.groupInfo[1] = dd[1];
			cbGroup.groupInfo[2] = dd[2];
			m_groupInfo->Set(&cbGroup, sizeof(cbGroup));

			m_shaders[0]->GetShaderParameterByName("FragmentList").Set(m_fragmentList);
			m_shaders[0]->GetShaderParameterByName("cbInfo").Set(m_cbInfo);
			m_shaders[0]->GetShaderParameterByName("cbGroupInfo").Set(m_groupInfo);
			m_shaders[0]->GetShaderParameterByName("nodesPool").Set(m_NodePool);
			
			m_Pipeline->Bind();

			Vector3UI group(dd[0], dd[1], 1);
			m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(group);

#if _DEBUG
			//m_NodePool->Copy(nullptr);

#endif
			m_Pipeline->UnBind();


			//pass Alloc
			m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[1]);

			m_shaders[1]->GetShaderParameterByName("nodesPool").Set(m_NodePool);
			m_shaders[1]->GetShaderParameterByName("brickIndex").Set(m_BrickInedx);
			m_shaders[1]->GetShaderParameterByName("numNode").Set(m_NumNode);
			m_shaders[1]->GetShaderParameterByName("nodeIndex").Set(m_NodeIndex);

			m_NumNode->CopyBufferData();
			void* data = m_NumNode->GetData();
			mNumNodePerLevel.push_back(((UINT*)data)[level]);

			UINT sqrNode = (UINT)std::sqrtf((float)mNumNodePerLevel[level]);
			UINT ddd[] = { sqrNode + 1,sqrNode + 1,1 };
			cbInfo.curLevel = level;
			cbInfo.curNode = mNumNodePerLevel[level];
			cbInfo.sumVoxels = m_TotalVoxel;
			cbInfo.totalLevel = m_TotalLevel;
			m_cbInfo->Set(&cbInfo, sizeof(cbInfo));

			cbGroup.groupInfo[0] = ddd[0];
			cbGroup.groupInfo[1] = ddd[1];
			cbGroup.groupInfo[2] = ddd[2];
			m_groupInfo->Set(&cbGroup, sizeof(cbGroup));

			m_shaders[1]->GetShaderParameterByName("cbInfo").Set(m_cbInfo);
			m_shaders[1]->GetShaderParameterByName("cbGroupInfo").Set(m_groupInfo);

			m_Pipeline->Bind();

			group = Vector3UI(ddd[0], ddd[1], ddd[2]);
			m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(group);

			m_BrickInedx->CopyBufferData();

			m_Pipeline->UnBind();
		}


		//Create brickPool
		m_TotalBrick = *(UINT*)m_BrickInedx->GetData();
		
		UINT r = (UINT)std::pow(m_TotalBrick, 0.33333334f);
		while (r*r*r < m_TotalBrick)
			++r;
		UINT pp[3] = { r,r,r };
		//update brick info
		CBBrickInfo cbrickInfo;
		cbrickInfo.extent[0] = pp[0];
		cbrickInfo.extent[1] = pp[1];
		cbrickInfo.extent[2] = pp[2];
		m_BrickInfo->Set(&cbrickInfo,sizeof(cbrickInfo));

		//Texture3D
		for (UINT i = 0; i < 3; ++i)
		{
			if(!m_BricksPool[i])
				m_BricksPool[i] = m_RenderDevice->CreateTexture3D(
					r*BrickRes, r*BrickRes, r*BrickRes, 
					Texture::TextureFormat(
						Texture::Components::R,
						Texture::Type::UnsignedInteger,
						1,
						32
					),
					CPUAccess::None,
					true);
			else
			{
				m_BricksPool[i]->Clear();
			}
		}
		m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[2]);
		UINT sqrVoxel = (UINT)std::sqrtf((float)m_TotalVoxel);
		UINT dd[] = { PAD16(sqrVoxel) / VoxelDispatchUnit,PAD16(sqrVoxel) / VoxelDispatchUnit,1 };
		//update CBGroup

		cbGroup.groupInfo[0] = dd[0];
		cbGroup.groupInfo[1] = dd[1];
		cbGroup.groupInfo[2] = dd[2];
		m_groupInfo->Set(&cbGroup, sizeof(cbGroup));

		//Mipmap pass
		m_shaders[2]->GetShaderParameterByName("cbInfo").Set(m_cbInfo);
		m_shaders[2]->GetShaderParameterByName("BrickInfo").Set(m_BrickInfo);
		m_shaders[2]->GetShaderParameterByName("cbGroupInfo").Set(m_groupInfo);

		m_shaders[2]->GetShaderParameterByName("FragmentList").Set(m_fragmentList);

		m_shaders[2]->GetShaderParameterByName("nodesPools").Set(m_NodePool);

		m_shaders[2]->GetShaderParameterByName("bricksPool_color").Set(m_BricksPool[0]);
		m_shaders[2]->GetShaderParameterByName("bricksPool_normal").Set(m_BricksPool[1]);
		m_shaders[2]->GetShaderParameterByName("bricksPool_irrandiance").Set(m_BricksPool[2]);

		m_Pipeline->Bind();
		Vector3UI g(dd[0], dd[1], dd[2]);
		m_shaders[2]->Dispatch(g);

		m_Pipeline->UnBind();

		for (int level = m_TotalLevel - 2; level >= 0; --level)
		{
			m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[3]);
			UINT sqrNode = (UINT)std::sqrtf((float)mNumNodePerLevel[level]);
			UINT ddd[] = { sqrNode + 1,sqrNode + 1,1 };
			CBInfo cbinfo;
			cbinfo.curLevel = level;
			cbinfo.totalLevel = m_TotalLevel;
			cbinfo.sumVoxels = m_TotalVoxel;
			cbinfo.curNode = mNumNodePerLevel[level];
			m_cbInfo->Set(&cbinfo, sizeof(cbinfo));

			cbGroup.groupInfo[0] = ddd[0];
			cbGroup.groupInfo[1] = ddd[1];
			cbGroup.groupInfo[2] = ddd[2];
			m_groupInfo->Set(&cbGroup, sizeof(cbGroup));

			m_shaders[3]->GetShaderParameterByName("cbInfo").Set(m_cbInfo);
			m_shaders[3]->GetShaderParameterByName("cbBrickInfo").Set(m_BrickInfo);
			m_shaders[3]->GetShaderParameterByName("cbGroupInfo").Set(m_groupInfo);

			m_shaders[3]->GetShaderParameterByName("nodesPool").Set(m_NodePool);
			m_shaders[3]->GetShaderParameterByName("numNode").Set(m_NumNode);

			m_shaders[3]->GetShaderParameterByName("bricksPool_color").Set(m_BricksPool[0]);
			m_shaders[3]->GetShaderParameterByName("bricksPool_normal").Set(m_BricksPool[1]);
			m_shaders[3]->GetShaderParameterByName("bricksPool_irradiance").Set(m_BricksPool[2]);


			m_Pipeline->Bind();
			Vector3UI ppp(ddd[0], ddd[1], 1);
			m_shaders[3]->Dispatch(ppp);
		}
		m_Pipeline->UnBind();

		m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[4]);

		float res = std::powf(2.f, CURLEVEL);
		float size = (1.0f / res) * 0.5f;

		mCubeMesh = m_RenderDevice->CreateMesh();
		XMFLOAT3  v[8];
		v[0] = XMFLOAT3(-size, -size, -size);
		v[1] = XMFLOAT3(-size, size, -size);
		v[2] = XMFLOAT3(size, size, -size);
		v[3] = XMFLOAT3(size, -size, -size);

		v[4] = XMFLOAT3(-size, -size, size);
		v[5] = XMFLOAT3(-size, size, size);
		v[6] = XMFLOAT3(size, size, size);
		v[7] = XMFLOAT3(size, -size, size);

		float* tempV = new float[24];
		for (int i = 0; i < 24; i+=3)
		{
			tempV[i] = v[i / 3].x;
			tempV[i+1] = v[i / 3].y;
			tempV[i+2] = v[i / 3].z;

		}
		auto vertexbuffer = m_RenderDevice->CreateFloatVertexBuffer(tempV, 8, sizeof(XMFLOAT3));

		UINT indices[36];

		//前面
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 2; indices[4] = 3; indices[5] = 0;

		//左面
		indices[6] = 4; indices[7] = 5; indices[8] = 1;
		indices[9] = 1; indices[10] = 0; indices[11] = 4;

		//上面	
		indices[12] = 1; indices[13] = 5; indices[14] = 6;
		indices[15] = 6; indices[16] = 2; indices[17] = 1;

		//右面
		indices[18] = 2; indices[19] = 6; indices[20] = 7;
		indices[21] = 7; indices[22] = 3; indices[23] = 2;

		//下面
		indices[24] = 4; indices[25] = 0; indices[26] = 3;
		indices[27] = 3; indices[28] = 7; indices[29] = 4;

		//后面
		indices[30] = 7; indices[31] = 6; indices[32] = 5;
		indices[33] = 5; indices[34] = 4; indices[35] = 7;

		auto indexbuffer = m_RenderDevice->CreateUIntIndexBuffer(indices, 36);
		
		mCubeMesh->SetIndexBuffer(indexbuffer);
		positionBind = std::make_shared<BufferBinding>("POSITION", 0);

		mCubeMesh->AddVertexBuffer(*positionBind,vertexbuffer);
	
		if (!m_visualPool)
			m_visualPool = m_RenderDevice->CreateStructuredBuffer(nullptr, mNumNodePerLevel[CURLEVEL], sizeof(VisualPackage), CPUAccess::None, true, true);
		else
			m_visualPool->Clear();
		//update cbuffer
		cbInfo.curLevel = CURLEVEL;
		cbInfo.curNode = mNumNodePerLevel[CURLEVEL];
		m_cbInfo->Set(&cbInfo,sizeof(cbInfo));

		VoxelizationPass::Attri cbAttri;
		cbAttri.origin = Float4(-.5f, .5f, -.5f, 1.0f);
		cbAttri.extent = Float4(1.0f, 1.0f, 1.0f, 0.0f);
		m_cbAttri = m_RenderDevice->CreateConstantBuffer(&cbAttri, sizeof(cbAttri));

		//constant
		m_shaders[4]->GetShaderParameterByName("cbInfo").Set(m_cbInfo);
		m_shaders[4]->GetShaderParameterByName("cbAttri").Set(m_cbAttri);
		m_shaders[4]->GetShaderParameterByName("cbBrickInfo").Set(m_BrickInfo);
		//shader source
		m_shaders[4]->GetShaderParameterByName("nodesPool").Set(m_NodePool);
		//unordered
		m_shaders[4]->GetShaderParameterByName("visualIndex").Set(m_visualIndex);
		m_shaders[4]->GetShaderParameterByName("visualPool").Set(m_visualPool);
		m_shaders[4]->GetShaderParameterByName("bricksPool_color").Set(m_BricksPool[0]);
		m_shaders[4]->GetShaderParameterByName("bricksPool_normal").Set(m_BricksPool[1]);


		//bind buffer
		m_Pipeline->Bind();
		Vector3UI ddd((UINT)res,(UINT)res,(UINT)res);
		m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(ddd);

		m_Pipeline->UnBind();

		m_visualIndex->CopyBufferData();
		UINT sum = *((UINT*)m_visualIndex->GetData());
		std::vector<UINT> instances;
		for (UINT i = 0; i < sum; ++i)
		{
			instances.push_back(i);
		}
		m_InstanceBuffer = m_RenderDevice->CreateVertexBuffer(instances);
		instantBind = std::make_shared<BufferBinding>("INDEX", 0);

		mCubeMesh->AddVertexBuffer(*instantBind, m_InstanceBuffer);

	

		e.PipelineState = m_Pipeline.get();
		init = true;
	}

	m_Pipeline->GetRasterizerState().SetViewport(Viewport(0, 0, 1280, 760, 0.0f, 1.0f));
	//m_Pipeline->GetRasterizerState().SetFillMode(RasterizerState::FillMode::WireFrame, RasterizerState::FillMode::WireFrame);
	m_Pipeline->GetRasterizerState().SetPirmitiveMode(RasterizerState::PrimitiveMode::LINE_LIST);
	//m_Pipeline->SetRenderTarget();
	m_Pipeline->GetRenderTarget()->Clear(ClearFlags::All, Float4(1, 1, 1, 1));
	m_Pipeline->SetShader(Shader::ShaderType::VertexShader, m_shaders[5]);
	m_Pipeline->SetShader(Shader::ShaderType::PixelShader, m_shaders[6]);
	Camera* mCamera = e.Camera;
	
	m_shaders[5]->GetShaderParameterByName("visualPool").Set(m_visualPool);
	m_shaders[5]->GetShaderParameterByName("cbTrans").Set(m_cbTrans);
	m_Pipeline->Bind();
	Visit(*mCubeMesh);
	
}

void Hikari::FlagOctreePass::PostRender(RenderEventArgs & e)
{
	if (m_Pipeline)
	{
		//m_Pipeline->UnBind();
	}
}

void Hikari::FlagOctreePass::Visit(Scene & scene)
{
}

void Hikari::FlagOctreePass::Visit(Hikari::Node & node)
{
}


void Hikari::FlagOctreePass::Visit(Mesh & mesh)
{
	Camera* camera = m_pRenderEventArgs->Camera;
	if (camera)
	{
		XMMATRIX viewProj = XMMatrixTranspose(camera->ViewProj());
		m_cbTrans->Set(&viewProj, sizeof(XMMATRIX));
	}
	if ( m_pRenderEventArgs)
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}
