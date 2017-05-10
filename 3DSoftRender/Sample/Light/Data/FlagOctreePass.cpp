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
#include "Dx11Texture.h"
#include "Dx11ConstantBuffer.h"
#include "Dx11Scene.h"
#include "Camera.h"
using namespace Hikari;
#define PAD16(x) ((x+15) & (~15))
#define CURLEVEL 6
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

void Hikari::FlagOctreePass::SetAttriConstant(ConstantBuffer * buffer, const std::string & name)
{
	m_cbAttri = buffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(buffer);

}

void Hikari::FlagOctreePass::SetVisualPool(StructuredBuffer * buffer, const std::string & name)
{
	m_visualPool = buffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(buffer);
}

void Hikari::FlagOctreePass::SetVisualIndex(RWBuffer * buffer, const std::string & name)
{
	m_visualIndex = buffer;
	m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->GetShaderParameterByName(name).Set(buffer);
}

void Hikari::FlagOctreePass::SetNodeBuffer(StructuredBuffer * buffer, const std::string & name)
{
	m_NodePool = buffer;
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



void Hikari::FlagOctreePass::SetComputeShaders(Shader * ss[])
{
	m_shaders[0] = ss[0];
	m_shaders[1] = ss[1];
	m_shaders[2] = ss[2];
	m_shaders[3] = ss[3];
	m_shaders[4] = ss[4];
	m_shaders[5] = ss[5];
	m_shaders[6] = ss[6];

}

void Hikari::FlagOctreePass::PreRender(RenderEventArgs & e)
{
	if (!init)
	{
		m_NodePool->Clear();

		PipelineState* prePipeline = e.PipelineState;
		m_fragmentList = prePipeline->GetRenderTarget()->GetStructuredBuffer(0);
		RWBuffer* rBuffer = prePipeline->GetRenderTarget()->GetRWBuffer(0);
		m_TotalVoxel = *(UINT*)rBuffer->GetData();
	}
	e.PipelineState = m_Pipeline;
	m_pRenderEventArgs = &e;

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
			UINT sqrtVoxel = (UINT)std::sqrtf((UINT)m_TotalVoxel);

			UINT dd[] = { PAD16(sqrtVoxel) / 16, PAD16(sqrtVoxel) / 16, 1 };
			
			cbGroup.groupInfo[0] = dd[0];
			cbGroup.groupInfo[1] = dd[1];
			cbGroup.groupInfo[2] = dd[2];
			m_groupInfo->Set(&cbGroup, sizeof(cbGroup));

			m_shaders[0]->GetShaderParameterByName("FragmentList").Set(m_fragmentList);
			m_shaders[0]->GetShaderParameterByName("cbInfo").Set(m_cbInfo);
			m_shaders[0]->GetShaderParameterByName("cbGroupInfo").Set(m_groupInfo);
			m_shaders[0]->GetShaderParameterByName("nodesPool").Set(m_NodePool);

			m_Pipeline->Bind();

			Vector3f group(dd[0], dd[1], 1);
			m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(group);
			
			m_Pipeline->UnBind();


			////Test
			//ID3D11Device* md3dDevice;
			//ID3D11DeviceContext* md3dImmediateContext;
			//md3dDevice = ((DirectRenderer*)m_RenderDevice)->mData->mDevice;
			//md3dImmediateContext = ((DirectRenderer*)m_RenderDevice)->mData->mImmediateContext;

			//ID3D11Buffer* nodepooluav = nullptr;
			//((StructuredBufferDX11*)(m_NodePool))->GetUnorderedAccessView()->GetResource((ID3D11Resource**)&nodepooluav);

			//ID3D11Buffer* TestBuffer;
			//D3D11_BUFFER_DESC bd;
			//ZeroMemory(&bd, sizeof(bd));
			//bd.ByteWidth = sizeof(Node) * m_TotalNode;
			//bd.MiscFlags = 0;
			//bd.StructureByteStride = 0;
			//bd.Usage = D3D11_USAGE_STAGING;
			//bd.BindFlags = 0;
			//bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			//md3dDevice->CreateBuffer(&bd, 0, &TestBuffer);
			//md3dImmediateContext->CopyResource(TestBuffer, nodepooluav);

			//D3D11_MAPPED_SUBRESOURCE ms;
			//md3dImmediateContext->Map(TestBuffer, 0, D3D11_MAP_READ, 0, &ms);

			//Node* v = (Node*)ms.pData;
			//Node vv = *v;
			//md3dImmediateContext->Unmap(TestBuffer, 0);
			//

			//m_BrickInedx->Copy(nullptr);
			//m_NodeIndex->Copy(nullptr);
			//m_NumNode->Copy(nullptr);

			//UINT t_brickIndex = *(UINT*)m_BrickInedx->GetData();
			//
			//UINT t_numnode = ((UINT*)m_NumNode->GetData())[level];


			//UINT t_nodeIndex = *(UINT*)m_NodeIndex->GetData();
			//

			////endTest


			//pass Alloc
			m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[1]);

			m_shaders[1]->GetShaderParameterByName("nodesPool").Set(m_NodePool);
			m_shaders[1]->GetShaderParameterByName("brickIndex").Set(m_BrickInedx);
			m_shaders[1]->GetShaderParameterByName("numNode").Set(m_NumNode);
			m_shaders[1]->GetShaderParameterByName("nodeIndex").Set(m_NodeIndex);

			m_NumNode->Copy(nullptr);
			void* data = m_NumNode->GetData();
			mNumNodePerLevel.push_back(((UINT*)data)[level]);

			UINT sqrNode = std::sqrtf(mNumNodePerLevel[level]);
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

			group = Vector3f(ddd[0], ddd[1], 1);
			m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(group);


			
			////test
			//((StructuredBufferDX11*)(m_NodePool))->GetUnorderedAccessView()->GetResource((ID3D11Resource**)&nodepooluav);


			//md3dImmediateContext->Map(TestBuffer, 0, D3D11_MAP_READ, 0, &ms);
			//md3dImmediateContext->CopyResource(TestBuffer, nodepooluav);

			//v = (Node*)ms.pData;
			//vv = *v;
			//md3dImmediateContext->Unmap(TestBuffer, 0);

			//m_BrickInedx->Copy(nullptr);
			//m_NodeIndex->Copy(nullptr);
			//m_NumNode->Copy(nullptr);

			//t_brickIndex = *(UINT*)m_BrickInedx->GetData();

			//t_numnode = ((UINT*)m_NumNode->GetData())[level];


			//t_nodeIndex = *(UINT*)m_NodeIndex->GetData();

			//TestBuffer->Release();
			////endTest
			m_BrickInedx->Copy(nullptr);
			data = m_BrickInedx->GetData();
			UINT bbb = *(UINT*)data;
			m_Pipeline->UnBind();
		}
		
		m_TotalBrick = *(UINT*)m_BrickInedx->GetData();
		
		UINT r = std::pow(m_TotalBrick, 0.33333334f);
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
				m_BricksPool[i] = m_RenderDevice->CreateTexture3D(r*2, r*2, r*2, Texture::TextureFormat(Texture::Components::R, Texture::Type::UnsignedInteger,1,32), CPUAccess::None, true);
			else
			{
				m_BricksPool[i]->Clear();
			}
		}
		m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[2]);
		UINT sqrVoxel = std::sqrtf(m_TotalVoxel);
		UINT dd[] = { PAD16(sqrVoxel) / 16,PAD16(sqrVoxel) / 16,1 };
		//update CBGroup

		cbGroup.groupInfo[0] = dd[0];
		cbGroup.groupInfo[1] = dd[1];
		cbGroup.groupInfo[2] = dd[2];
		m_groupInfo->Set(&cbGroup, sizeof(cbGroup));

		m_shaders[2]->GetShaderParameterByName("cbInfo").Set(m_cbInfo);
		m_shaders[2]->GetShaderParameterByName("BrickInfo").Set(m_BrickInfo);
		m_shaders[2]->GetShaderParameterByName("cbGroupInfo").Set(m_groupInfo);

		m_shaders[2]->GetShaderParameterByName("FragmentList").Set(m_fragmentList);

		m_shaders[2]->GetShaderParameterByName("nodesPools").Set(m_NodePool);

		m_shaders[2]->GetShaderParameterByName("bricksPool_color").Set(m_BricksPool[0]);
		m_shaders[2]->GetShaderParameterByName("bricksPool_normal").Set(m_BricksPool[1]);
		m_shaders[2]->GetShaderParameterByName("bricksPool_irrandiance").Set(m_BricksPool[2]);

		m_Pipeline->Bind();
		Vector3f g(dd[0], dd[1], 1);
		m_shaders[2]->Dispatch(g);

		////Test
		//ID3D11Device* md3dDevice;
		//ID3D11DeviceContext* md3dImmediateContext;
		//md3dDevice = ((DirectRenderer*)m_RenderDevice)->mData->mDevice;
		//md3dImmediateContext = ((DirectRenderer*)m_RenderDevice)->mData->mImmediateContext;

		//ID3D11Buffer* nodepooluav = nullptr;
		//((StructuredBufferDX11*)(m_NodePool))->GetUnorderedAccessView()->GetResource((ID3D11Resource**)&nodepooluav);

		//ID3D11Buffer* TestBuffer;
		//D3D11_BUFFER_DESC bd;
		//ZeroMemory(&bd, sizeof(bd));
		//bd.ByteWidth = sizeof(Node) * m_TotalNode;
		//bd.MiscFlags = 0;
		//bd.StructureByteStride = 0;
		//bd.Usage = D3D11_USAGE_STAGING;
		//bd.BindFlags = 0;
		//bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		//md3dDevice->CreateBuffer(&bd, 0, &TestBuffer);
		//md3dImmediateContext->CopyResource(TestBuffer, nodepooluav);

		//D3D11_MAPPED_SUBRESOURCE ms;
		//md3dImmediateContext->Map(TestBuffer, 0, D3D11_MAP_READ, 0, &ms);

		//Node* v = (Node*)ms.pData;
		//Node vv = *v;
		//md3dImmediateContext->Unmap(TestBuffer, 0);
		//TestBuffer->Release();

		////test texture3d
		//ID3D11Texture3D* TestTexture;
		//ID3D11Texture3D* brickPos = nullptr;
		//((TextureDX11*)(m_BricksPool[2]))->GetUnorderedAccessView()->GetResource((ID3D11Resource**)&brickPos);
		//D3D11_TEXTURE3D_DESC ds;
		//ds.BindFlags = 0;
		//ds.Width = 50;
		//ds.Height = 50;
		//ds.Depth = 50;
		//ds.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		//ds.Format = DXGI_FORMAT_R32_UINT;
		//ds.MipLevels = 1;
		//ds.MiscFlags = 0;
		//ds.Usage = D3D11_USAGE_STAGING;

		//md3dDevice->CreateTexture3D(&ds, 0, &TestTexture);
		//md3dImmediateContext->CopyResource(TestTexture, brickPos);

		//md3dImmediateContext->Map(TestTexture, 0, D3D11_MAP_READ, 0, &ms);

		//UINT* uv = (UINT*)ms.pData;
		//UINT uvv = *uv;
		//md3dImmediateContext->Unmap(TestTexture, 0);
		//TestTexture->Release();


		//m_BrickInedx->Copy(nullptr);
		//m_NodeIndex->Copy(nullptr);
		//m_NumNode->Copy(nullptr);

		//UINT t_brickIndex = *(UINT*)m_BrickInedx->GetData();
		//
		//UINT t_nodeIndex = *(UINT*)m_NodeIndex->GetData();
		//
		////endTest

		m_Pipeline->UnBind();
		
		for (int level = m_TotalLevel - 2; level >= 0; --level)
		{
			m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[3]);
			UINT sqrNode = std::sqrtf(mNumNodePerLevel[level]);
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
			m_shaders[3]->GetShaderParameterByName("bricksPool_irrandiance").Set(m_BricksPool[2]);


			m_Pipeline->Bind();
			Vector3f ppp(ddd[0], ddd[1], 1);
			m_shaders[3]->Dispatch(ppp);
		}
		m_Pipeline->UnBind();

		m_Pipeline->SetShader(Shader::ShaderType::ComputeShader, m_shaders[4]);

		float res = std::powf(2.f, CURLEVEL);
		float size = (1.0f / res) * 0.5f;
		//m_SceneBox = m_RenderDevice->CreateCube(size);
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

		//ID3D11Device* md3dDevice;
		//ID3D11DeviceContext* md3dImmediateContext;
		//md3dDevice = ((DirectRenderer*)m_RenderDevice)->mData->mDevice;
		//md3dImmediateContext = ((DirectRenderer*)m_RenderDevice)->mData->mImmediateContext;
		////创建Buffer
		//D3D11_BUFFER_DESC vbd;
		//vbd.Usage = D3D11_USAGE_IMMUTABLE;
		//vbd.ByteWidth = sizeof(XMFLOAT3) * 8;
		//vbd.CPUAccessFlags = 0;
		//vbd.MiscFlags = 0;
		//vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//vbd.StructureByteStride = 0;

		//D3D11_SUBRESOURCE_DATA vbsd;
		//vbsd.pSysMem = v;

		//md3dDevice->CreateBuffer(&vbd, &vbsd, &mVisualVB);
		float* tempV = new float[24];
		for (int i = 0; i < 24; i+=3)
		{
			tempV[i] = v[i / 3].x;
			tempV[i+1] = v[i / 3].y;
			tempV[i+2] = v[i / 3].z;

		}
		Buffer* vertexbuffer = m_RenderDevice->CreateFloatVertexBuffer(tempV, 8, sizeof(XMFLOAT3));

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

		//D3D11_BUFFER_DESC ibd;
		//ibd.Usage = D3D11_USAGE_IMMUTABLE;
		//ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//ibd.ByteWidth = sizeof(UINT) * 36;
		//ibd.CPUAccessFlags = 0;
		//ibd.MiscFlags = 0;
		//ibd.StructureByteStride = 0;

		//D3D11_SUBRESOURCE_DATA isd;
		//isd.pSysMem = indices;

		//md3dDevice->CreateBuffer(&ibd, &isd, &mVisualIB);
		Buffer*indexbuffer = m_RenderDevice->CreateUIntIndexBuffer(indices, 36);
		
		mCubeMesh->SetIndexBuffer(indexbuffer);
		positionBind = new BufferBinding("POSITION", 0);

		mCubeMesh->AddVertexBuffer(*positionBind,vertexbuffer);
	
		if (!m_visualPool)
			m_visualPool = m_RenderDevice->CreateStructuredBuffer(nullptr, mNumNodePerLevel[CURLEVEL], sizeof(VisualPackage), CPUAccess::None, true, true);
		else
			m_visualPool->Clear();
		//update cbuffer
		cbInfo.curLevel = CURLEVEL;
		cbInfo.curNode = mNumNodePerLevel[CURLEVEL];
		m_cbInfo->Set(&cbInfo,sizeof(cbInfo));

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
		Vector3f ddd(res,res,res);
		m_Pipeline->GetShader(Shader::ShaderType::ComputeShader)->Dispatch(ddd);
		
		////test texture3d
		//
		//ID3D11Device* md3dDevice;
		//ID3D11DeviceContext* md3dImmediateContext;
		//md3dDevice = ((DirectRenderer*)m_RenderDevice)->mData->mDevice;
		//md3dImmediateContext = ((DirectRenderer*)m_RenderDevice)->mData->mImmediateContext;

		//ID3D11Texture3D* TestTexture;
		//ID3D11Texture3D* brickPos = nullptr;
		//((TextureDX11*)(m_BricksPool[0]))->GetUnorderedAccessView()->GetResource((ID3D11Resource**)&brickPos);
		//D3D11_TEXTURE3D_DESC ds;
		//ds.BindFlags = 0;
		//ds.Width = 50;
		//ds.Height = 50;
		//ds.Depth = 50;
		//ds.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		//ds.Format = DXGI_FORMAT_R32_UINT;
		//ds.MipLevels = 1;
		//ds.MiscFlags = 0;
		//ds.Usage = D3D11_USAGE_STAGING;

		//md3dDevice->CreateTexture3D(&ds, 0, &TestTexture);
		//md3dImmediateContext->CopyResource(TestTexture, brickPos);

		//D3D11_MAPPED_SUBRESOURCE ms;
		//md3dImmediateContext->Map(TestTexture, 0, D3D11_MAP_READ, 0, &ms);

		//UINT* uv = (UINT*)ms.pData;
		//UINT uvv = *uv;
		//md3dImmediateContext->Unmap(TestTexture, 0);
		//TestTexture->Release();


		//m_BrickInedx->Copy(nullptr);
		//m_NodeIndex->Copy(nullptr);
		//m_NumNode->Copy(nullptr);
		//m_visualIndex->Copy(nullptr);
		//

		////test nodepool

		//ID3D11Buffer* nodepooluav = nullptr;
		//((StructuredBufferDX11*)(m_NodePool))->GetUnorderedAccessView()->GetResource((ID3D11Resource**)&nodepooluav);

		//ID3D11Buffer* TestBuffer;
		//D3D11_BUFFER_DESC bd;
		//ZeroMemory(&bd, sizeof(bd));
		//bd.ByteWidth = sizeof(Node) * m_TotalNode;
		//bd.MiscFlags = 0;
		//bd.StructureByteStride = 0;
		//bd.Usage = D3D11_USAGE_STAGING;
		//bd.BindFlags = 0;
		//bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		//md3dDevice->CreateBuffer(&bd, 0, &TestBuffer);
		//md3dImmediateContext->CopyResource(TestBuffer, nodepooluav);

		//md3dImmediateContext->Map(TestBuffer, 0, D3D11_MAP_READ, 0, &ms);

		//Node* np = (Node*)ms.pData;
		//Node nnp = *np;
		//md3dImmediateContext->Unmap(TestBuffer, 0);
		//TestBuffer->Release();

		////endtest

		////test visualPool
		//ID3D11Buffer* visualPool = nullptr;
		//((StructuredBufferDX11*)(m_visualPool))->GetUnorderedAccessView()->GetResource((ID3D11Resource**)&visualPool);

		//ZeroMemory(&bd, sizeof(bd));
		//bd.ByteWidth = sizeof(VisualPackage) * mNumNodePerLevel[6];
		//bd.MiscFlags = 0;
		//bd.StructureByteStride = 0;
		//bd.Usage = D3D11_USAGE_STAGING;
		//bd.BindFlags = 0;
		//bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		//md3dDevice->CreateBuffer(&bd, 0, &TestBuffer);
		//md3dImmediateContext->CopyResource(TestBuffer, visualPool);

		//md3dImmediateContext->Map(TestBuffer, 0, D3D11_MAP_READ, 0, &ms);

		//VisualPackage* vp = (VisualPackage*)ms.pData;
		//VisualPackage vvp = *vp;
		//md3dImmediateContext->Unmap(TestBuffer, 0);
		//TestBuffer->Release();
		////endTest
		m_Pipeline->UnBind();

		m_visualIndex->Copy(nullptr);
		UINT sum = *((UINT*)m_visualIndex->GetData());
		std::vector<UINT> instances;
		for (UINT i = 0; i < sum; ++i)
		{
			instances.push_back(i);
		}
		m_InstanceBuffer = m_RenderDevice->CreateVertexBuffer(instances);
		instantBind = new BufferBinding("INDEX", 0);

		mCubeMesh->AddVertexBuffer(*instantBind, m_InstanceBuffer);

		init = true;
	}
	m_Pipeline->GetRasterizerState().SetViewport(Viewport(0, 0, 1280, 760, 0.0f, 1.0f));
	m_Pipeline->SetRenderTarget(((DirectRenderer*)(m_RenderDevice))->mData->renderTarget);
	m_Pipeline->GetRenderTarget()->Clear(ClearFlags::All,Float4(1,1,1,1));
	m_Pipeline->SetShader(Shader::ShaderType::VertexShader, m_shaders[5]);
	m_Pipeline->SetShader(Shader::ShaderType::PixelShader, m_shaders[6]);
	Camera* mCamera = e.Camera;
	ConstantBuffer* cbTrans = m_RenderDevice->CreateConstantBuffer(&XMMatrixTranspose(mCamera->ViewProj()), sizeof(XMMATRIX));
	m_shaders[5]->GetShaderParameterByName("visualPool").Set(m_visualPool);
	m_shaders[5]->GetShaderParameterByName("cbTrans").Set(cbTrans);
	m_Pipeline->Bind();
	Visit(*mCubeMesh);
	e.PipelineState = m_Pipeline;
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
	if ( m_pRenderEventArgs)
	{
		mesh.Render(*m_pRenderEventArgs);
	}
}
