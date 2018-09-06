#include "FlagOctreePass.h"

#include "ShaderEffect/VoxelDefine.h"
#include "Renderer/Renderer.h"
#include "Resource/PipelineState.h"
#include "Resource/RasterizerState.h"
#include "SceneGraph/Camera.h"
using namespace Hikari;


bool FlagOctreePass::init = false;

FlagOctreePass::FlagOctreePass(std::shared_ptr<Renderer> render, std::shared_ptr<Scene>
                               scene, std::shared_ptr<PipelineState> pipeline)
	: m_cbInfo(nullptr),
	  m_groupInfo(nullptr),
	  m_BrickInfo(nullptr),
	  m_cbAttri(nullptr), //Initialize when m_TotalNode is set.
	  m_NumNode(nullptr),
	  m_BrickInedx(nullptr),
	  m_NodeIndex(nullptr),
	  m_visualIndex(nullptr),
	  m_NodePool(nullptr), //dynamic create
	  m_visualPool(nullptr),
	  m_Pipeline(pipeline),
	  m_Scene(scene),
	  m_RenderDevice(render)
{
	CBInfo cbInfo{};
	m_cbInfo = m_RenderDevice->CreateConstantBuffer(cbInfo);

	CBGroupInfo cbGroupInfo{};
	m_groupInfo = m_RenderDevice->CreateConstantBuffer(&cbGroupInfo, PAD16(sizeof(FlagOctreePass::CBGroupInfo)));

	CBBrickInfo cbBrickInfo{};
	m_BrickInfo = m_RenderDevice->CreateConstantBuffer(&cbBrickInfo, PAD16(sizeof(FlagOctreePass::CBBrickInfo)));

	VoxelizationPass::Attri attr{};
	m_cbAttri = m_RenderDevice->CreateConstantBuffer(attr);

	XMMATRIX matrix;
	m_cbTrans = m_RenderDevice->CreateConstantBuffer(matrix);

	UINT i[] = {0};
	//bind uav Views
	const ShaderParameter::ShaderInputParameter visual_index_buffer = {
		ShaderParameter::ShaderInputType::Buffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::R32_SINT,
		CPUAccess::None,
		GPUAccess::Write
	};
	m_visualIndex = m_RenderDevice->CreateBuffer(i, visual_index_buffer);


	UINT mTotalLevel = (UINT)std::log2f(MaxLevelRes) + 1;
	std::vector<UINT> initNum;
	initNum.push_back(1);
	for (UINT i = 1; i < mTotalLevel; ++i)
	{
		initNum.push_back(0);
	}
	const ShaderParameter::ShaderInputParameter num_node_buffer = {
		ShaderParameter::ShaderInputType::Buffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::R32_SINT,
		CPUAccess::None,
		GPUAccess::ReadWrite
	};
	m_NumNode = m_RenderDevice->CreateBuffer(initNum.data(), (UINT)initNum.size(), sizeof(UINT), num_node_buffer);

	UINT u_nodeInit = 1;
	const ShaderParameter::ShaderInputParameter node_init_buffer = {
		ShaderParameter::ShaderInputType::Buffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::R32_SINT,
		CPUAccess::None,
		GPUAccess::ReadWrite
	};
	m_NodeIndex = m_RenderDevice->CreateBuffer(&u_nodeInit, 1, sizeof(UINT), node_init_buffer);

	UINT u_brickInit = 0;
	const ShaderParameter::ShaderInputParameter brick_init_buffer = {
		ShaderParameter::ShaderInputType::Buffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::R32_SINT,
		CPUAccess::None,
		GPUAccess::ReadWrite
	};
	m_BrickInedx = m_RenderDevice->CreateBuffer(&u_brickInit, 1, sizeof(UINT), brick_init_buffer);
}

FlagOctreePass::~FlagOctreePass()
= default;


std::shared_ptr<Renderer> FlagOctreePass::GetRenderDevice() const
{
	return m_RenderDevice;
}

void FlagOctreePass::SetConstantInfo(CBInfo& data, const std::string& name)
{
	assert(m_cbInfo);
	m_cbInfo->set(data);
	BindConstantInfo(name);
}

void FlagOctreePass::SetConstantGroup(CBGroupInfo& data, const std::string& name)
{
	assert(m_groupInfo);
	m_groupInfo->set(data);
	BindConstantGroup(name);
}

void FlagOctreePass::SetConstantBrick(CBBrickInfo& data, const std::string& name)
{
	assert(m_BrickInfo);
	m_BrickInfo->set(data);
	BindConstantBrick(name);
}

void FlagOctreePass::SetAttriConstant(VoxelizationPass::Attri& data, const std::string& name)
{
	assert(m_cbAttri);
	m_cbAttri->set(data);
	BindAttriConstant(name);
}

void FlagOctreePass::SetVisualPool(const std::vector<VisualPackage>& data, const std::string& name)
{
	assert(m_visualPool);
	m_visualPool->set(data);
	BindVisualPool(name);
}

void FlagOctreePass::SetVisualIndex(const std::vector<UINT>& data, const std::string& name)
{
	assert(m_visualIndex);
	m_visualIndex->set(data);
	BindVisualIndex(name);
}

void FlagOctreePass::SetNumOfNodes(std::vector<UINT>& numOfNodes, const std::string& name)
{
	assert(m_NumNode);
	m_NumNode->set(numOfNodes);
	BindNumOfNodes(name);
}

void FlagOctreePass::SetNodeIndex(std::vector<UINT>& nodeIndex, const std::string& name)
{
	assert(m_NodeIndex);
	m_NodeIndex->set(nodeIndex);
	BindNodeIndex(name);
}

void FlagOctreePass::SetBrickIndex(std::vector<UINT>& data, const std::string& name)
{
	assert(m_BrickInedx);
	m_BrickInedx->set(data);
	BindBrickIndex(name);
}

void FlagOctreePass::SetTotalNode(UINT totalNode)
{
	m_TotalNode = totalNode;
	const ShaderParameter::ShaderInputParameter total_node_buffer = {
		ShaderParameter::ShaderInputType::StructuredBuffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::UNKNOWN,
		CPUAccess::None,
		GPUAccess::ReadWrite
	};
	//Initialize NodesPool
	m_NodePool = m_RenderDevice->
		CreateStructuredBuffer(nullptr, m_TotalNode, sizeof(Node), total_node_buffer);
}

void FlagOctreePass::SetTotalLevel(UINT totalLevel)
{
	m_TotalLevel = totalLevel;
}


void FlagOctreePass::SetComputeShaders(std::shared_ptr<Shader> ss[], size_t size)
{
	m_shaders.reserve(size);
	for (int i = 0; i < size; ++i)
		m_shaders.push_back(ss[i]);
}

void FlagOctreePass::BindBrickIndex(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_BrickInedx);
}

void FlagOctreePass::BindNodeIndex(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_NodeIndex);
}

void FlagOctreePass::BindNumOfNodes(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_NumNode);
}

void FlagOctreePass::BindConstantInfo(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_cbInfo);
}

void FlagOctreePass::BindConstantGroup(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_groupInfo);
}

void FlagOctreePass::BindConstantBrick(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_BrickInfo);
}

void FlagOctreePass::BindAttriConstant(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_cbAttri);
}

void FlagOctreePass::BindVisualIndex(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_visualIndex);
}

void FlagOctreePass::BindVisualPool(const std::string& name)
{
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).set(m_visualPool);
}

void FlagOctreePass::PreRender(RenderEventArgs& e)
{
	if (!init)
	{
		assert(m_NodePool);
		m_NodePool->Clear();

		PipelineState* prePipeline = e.PipelineState;
		m_fragmentList = prePipeline->GetRenderTarget()->GetStructuredBuffer(0);
		m_fragmentList->copy(nullptr);
		auto rBuffer = prePipeline->GetRenderTarget()->GetBuffer(0);
		m_TotalVoxel = *(UINT*)rBuffer->get_data();
		prePipeline->unbind();
	}
	e.PipelineState = m_Pipeline.get();
	m_pRenderEventArgs = std::make_shared<RenderEventArgs>(e);
}

void FlagOctreePass::Render(RenderEventArgs& e)
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
			m_cbInfo->set(&cbInfo, sizeof(cbInfo));
			UINT sqrtVoxel = (UINT)std::sqrtf((float)m_TotalVoxel);

			UINT dd[] = {PAD16(sqrtVoxel) / VoxelDispatchUnit, PAD16(sqrtVoxel) / VoxelDispatchUnit, 1};

			cbGroup.groupInfo[0] = dd[0];
			cbGroup.groupInfo[1] = dd[1];
			cbGroup.groupInfo[2] = dd[2];
			m_groupInfo->set(&cbGroup, sizeof(cbGroup));

			m_shaders[0]->GetShaderParameterByName("FragmentList").set(m_fragmentList);
			m_shaders[0]->GetShaderParameterByName("cbInfo").set(m_cbInfo);
			m_shaders[0]->GetShaderParameterByName("cbGroupInfo").set(m_groupInfo);
			m_shaders[0]->GetShaderParameterByName("nodesPool").set(m_NodePool);

			m_Pipeline->bind();

			Vector3UI group(dd[0], dd[1], 1);
			m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(group);

#if _DEBUG
			m_NodePool->copy(nullptr);

#endif
			m_Pipeline->unbind();


			//pass Alloc
			m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[1]);

			m_shaders[1]->GetShaderParameterByName("nodesPool").set(m_NodePool);
			m_shaders[1]->GetShaderParameterByName("brickIndex").set(m_BrickInedx);
			m_shaders[1]->GetShaderParameterByName("numNode").set(m_NumNode);
			m_shaders[1]->GetShaderParameterByName("nodeIndex").set(m_NodeIndex);

			m_NumNode->copy_buffer_data();
			void* data = m_NumNode->get_data();
			mNumNodePerLevel.push_back(((UINT*)data)[level]);

			UINT sqrNode = (UINT)std::sqrtf((float)mNumNodePerLevel[level]);
			UINT ddd[] = {sqrNode + 1, sqrNode + 1, 1};
			cbInfo.curLevel = level;
			cbInfo.curNode = mNumNodePerLevel[level];
			cbInfo.sumVoxels = m_TotalVoxel;
			cbInfo.totalLevel = m_TotalLevel;
			m_cbInfo->set(&cbInfo, sizeof(cbInfo));

			cbGroup.groupInfo[0] = ddd[0];
			cbGroup.groupInfo[1] = ddd[1];
			cbGroup.groupInfo[2] = ddd[2];
			m_groupInfo->set(&cbGroup, sizeof(cbGroup));

			m_shaders[1]->GetShaderParameterByName("cbInfo").set(m_cbInfo);
			m_shaders[1]->GetShaderParameterByName("cbGroupInfo").set(m_groupInfo);

			m_Pipeline->bind();

			group = Vector3UI(ddd[0], ddd[1], ddd[2]);
			m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(group);

			m_BrickInedx->copy_buffer_data();

			m_Pipeline->unbind();
		}
		 
		//Create brickPool
		m_TotalBrick = *(UINT*)m_BrickInedx->get_data();

		UINT r = (UINT)std::pow(m_TotalBrick, 0.33333334f);
		while (r * r * r < m_TotalBrick)
			++r;
		UINT pp[3] = {r, r, r};
		//update brick info
		CBBrickInfo cbrickInfo;
		cbrickInfo.extent[0] = pp[0];
		cbrickInfo.extent[1] = pp[1];
		cbrickInfo.extent[2] = pp[2];
		m_BrickInfo->set(&cbrickInfo, sizeof(cbrickInfo));


		const ShaderParameter::ShaderInputParameter brick_pool_buffer = {
			ShaderParameter::ShaderInputType::Texture,
			ShaderParameter::AppendFlag::RAW,
			ShaderParameter::Format::UNKNOWN,
			CPUAccess::None,
			GPUAccess::Write
		};
		//Texture3D
		for (UINT i = 0; i < 3; ++i)
		{
			if (!m_BricksPool[i])
				m_BricksPool[i] = m_RenderDevice->CreateTexture3D(
					r * BrickRes, r * BrickRes, r * BrickRes,
					Texture::TextureFormat(
						Texture::Components::R,
						Texture::Type::UnsignedInteger,
						1,
						32
					),
					brick_pool_buffer);
			else
			{
				m_BricksPool[i]->Clear();
			}
		}
		m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[2]);
		UINT sqrVoxel = (UINT)std::sqrtf((float)m_TotalVoxel);
		UINT dd[] = {PAD16(sqrVoxel) / VoxelDispatchUnit,PAD16(sqrVoxel) / VoxelDispatchUnit, 1};
		//update CBGroup

		cbGroup.groupInfo[0] = dd[0];
		cbGroup.groupInfo[1] = dd[1];
		cbGroup.groupInfo[2] = dd[2];
		m_groupInfo->set(&cbGroup, sizeof(cbGroup));

		//Mipmap pass
		m_shaders[2]->GetShaderParameterByName("cbInfo").set(m_cbInfo);
		m_shaders[2]->GetShaderParameterByName("BrickInfo").set(m_BrickInfo);
		m_shaders[2]->GetShaderParameterByName("cbGroupInfo").set(m_groupInfo);

		m_shaders[2]->GetShaderParameterByName("FragmentList").set(m_fragmentList);

		m_shaders[2]->GetShaderParameterByName("nodesPools").set(m_NodePool);

		m_shaders[2]->GetShaderParameterByName("bricksPool_color").set(m_BricksPool[0]);
		m_shaders[2]->GetShaderParameterByName("bricksPool_normal").set(m_BricksPool[1]);
		m_shaders[2]->GetShaderParameterByName("bricksPool_irrandiance").set(m_BricksPool[2]);

		m_Pipeline->bind();
		Vector3UI g(dd[0], dd[1], dd[2]);
		m_shaders[2]->Dispatch(g);

		m_Pipeline->unbind();

		for (int level = m_TotalLevel - 2; level >= 0; --level)
		{
			m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[3]);
			UINT sqrNode = (UINT)std::sqrtf((float)mNumNodePerLevel[level]);
			UINT ddd[] = {sqrNode + 1, sqrNode + 1, 1};
			CBInfo cbinfo;
			cbinfo.curLevel = level;
			cbinfo.totalLevel = m_TotalLevel;
			cbinfo.sumVoxels = m_TotalVoxel;
			cbinfo.curNode = mNumNodePerLevel[level];
			m_cbInfo->set(&cbinfo, sizeof(cbinfo));

			cbGroup.groupInfo[0] = ddd[0];
			cbGroup.groupInfo[1] = ddd[1];
			cbGroup.groupInfo[2] = ddd[2];
			m_groupInfo->set(&cbGroup, sizeof(cbGroup));

			m_shaders[3]->GetShaderParameterByName("cbInfo").set(m_cbInfo);
			m_shaders[3]->GetShaderParameterByName("cbBrickInfo").set(m_BrickInfo);
			m_shaders[3]->GetShaderParameterByName("cbGroupInfo").set(m_groupInfo);

			m_shaders[3]->GetShaderParameterByName("nodesPool").set(m_NodePool);
			m_shaders[3]->GetShaderParameterByName("numNode").set(m_NumNode);

			m_shaders[3]->GetShaderParameterByName("bricksPool_color").set(m_BricksPool[0]);
			m_shaders[3]->GetShaderParameterByName("bricksPool_normal").set(m_BricksPool[1]);
			m_shaders[3]->GetShaderParameterByName("bricksPool_irradiance").set(m_BricksPool[2]);


			m_Pipeline->bind();
			Vector3UI ppp(ddd[0], ddd[1], 1);
			m_shaders[3]->Dispatch(ppp);
		}
		m_Pipeline->unbind();

		m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[4]);

		float res = std::powf(2.f, CURLEVEL);
		float size = (1.0f / res) * 0.5f;

		mCubeMesh = m_RenderDevice->CreateMesh();
		XMFLOAT3 v[8];
		v[0] = XMFLOAT3(-size, -size, -size);
		v[1] = XMFLOAT3(-size, size, -size);
		v[2] = XMFLOAT3(size, size, -size);
		v[3] = XMFLOAT3(size, -size, -size);

		v[4] = XMFLOAT3(-size, -size, size);
		v[5] = XMFLOAT3(-size, size, size);
		v[6] = XMFLOAT3(size, size, size);
		v[7] = XMFLOAT3(size, -size, size);

		float* tempV = new float[24];
		for (int i = 0; i < 24; i += 3)
		{
			tempV[i] = v[i / 3].x;
			tempV[i + 1] = v[i / 3].y;
			tempV[i + 2] = v[i / 3].z;
		}
		auto vertexbuffer = m_RenderDevice->CreateFloatVertexBuffer(tempV, 8, sizeof(XMFLOAT3));

		UINT indices[36];

		//前面
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		//左面
		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 1;
		indices[9] = 1;
		indices[10] = 0;
		indices[11] = 4;

		//上面	
		indices[12] = 1;
		indices[13] = 5;
		indices[14] = 6;
		indices[15] = 6;
		indices[16] = 2;
		indices[17] = 1;

		//右面
		indices[18] = 2;
		indices[19] = 6;
		indices[20] = 7;
		indices[21] = 7;
		indices[22] = 3;
		indices[23] = 2;

		//下面
		indices[24] = 4;
		indices[25] = 0;
		indices[26] = 3;
		indices[27] = 3;
		indices[28] = 7;
		indices[29] = 4;

		//后面
		indices[30] = 7;
		indices[31] = 6;
		indices[32] = 5;
		indices[33] = 5;
		indices[34] = 4;
		indices[35] = 7;

		auto indexbuffer = m_RenderDevice->CreateUIntIndexBuffer(indices, 36);

		mCubeMesh->SetIndexBuffer(indexbuffer);
		positionBind = std::make_shared<BufferBinding>("POSITION", 0);

		mCubeMesh->AddVertexBuffer(*positionBind, vertexbuffer);

		const ShaderParameter::ShaderInputParameter num_node_per_level = {
			ShaderParameter::ShaderInputType::StructuredBuffer,
			ShaderParameter::AppendFlag::RAW,
			ShaderParameter::Format::UNKNOWN,
			CPUAccess::None,
			GPUAccess::ReadWrite
		};
		if (!m_visualPool)
			m_visualPool = m_RenderDevice->CreateStructuredBuffer(nullptr, mNumNodePerLevel[CURLEVEL],
			                                                      sizeof(VisualPackage), num_node_per_level);
		else
			m_visualPool->Clear();
		//update cbuffer
		cbInfo.curLevel = CURLEVEL;
		cbInfo.curNode = mNumNodePerLevel[CURLEVEL];
		m_cbInfo->set(&cbInfo, sizeof(cbInfo));

		VoxelizationPass::Attri cbAttri;
		cbAttri.origin = Float4(-.5f, .5f, -.5f, 1.0f);
		cbAttri.extent = Float4(1.0f, 1.0f, 1.0f, 0.0f);
		m_cbAttri = m_RenderDevice->CreateConstantBuffer(&cbAttri, sizeof(cbAttri));

		//constant
		m_shaders[4]->GetShaderParameterByName("cbInfo").set(m_cbInfo);
		m_shaders[4]->GetShaderParameterByName("cbAttri").set(m_cbAttri);
		m_shaders[4]->GetShaderParameterByName("cbBrickInfo").set(m_BrickInfo);
		//shader source
		m_shaders[4]->GetShaderParameterByName("nodesPool").set(m_NodePool);
		//unordered
		m_shaders[4]->GetShaderParameterByName("visualIndex").set(m_visualIndex);
		m_shaders[4]->GetShaderParameterByName("visualPool").set(m_visualPool);
		m_shaders[4]->GetShaderParameterByName("bricksPool_color").set(m_BricksPool[0]);
		m_shaders[4]->GetShaderParameterByName("bricksPool_normal").set(m_BricksPool[1]);


		//bind buffer
		m_Pipeline->bind();
		Vector3UI ddd((UINT)res, (UINT)res, (UINT)res);
		m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(ddd);

		m_Pipeline->unbind();

		m_visualIndex->copy_buffer_data();
		UINT sum = *((UINT*)m_visualIndex->get_data());
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
	m_Pipeline->GetRenderTarget()->Clear(Float4(1, 1, 1, 1));
	m_Pipeline->SetShader(Shader::ShaderType::VertexShader, m_shaders[5]);
	m_Pipeline->SetShader(Shader::ShaderType::PixelShader, m_shaders[6]);
	Camera* mCamera = e.Camera;

	m_shaders[5]->GetShaderParameterByName("visualPool").set(m_visualPool);
	m_shaders[5]->GetShaderParameterByName("cbTrans").set(m_cbTrans);
	m_Pipeline->bind();
	Visit(*mCubeMesh);
}

void FlagOctreePass::PostRender(RenderEventArgs& e)
{
	if (m_Pipeline)
	{
		//m_Pipeline->unbind();
	}
}

void FlagOctreePass::Visit(Scene& scene)
{
}

void FlagOctreePass::Visit(Hikari::Node& node)
{
}


void FlagOctreePass::Visit(Mesh& mesh)
{
	Camera* camera = m_pRenderEventArgs->Camera;
	if (camera)
	{
		XMMATRIX viewProj = XMMatrixTranspose(camera->ViewProj());
		m_cbTrans->set(&viewProj, sizeof(XMMATRIX));
	}
	if (m_pRenderEventArgs)
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}
