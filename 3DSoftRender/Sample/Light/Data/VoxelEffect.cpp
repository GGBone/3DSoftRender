#include "VoxelEffect.h"
#include "PipelineState.h"
#include "ClearRenderTargetPass.h"
#include "VoxelizationPass.h"
#include "Camera.h"
#include "RenderTarget.h"
#include "SamplerState.h"
#include "Dx11RWBuffer.h"
#include "FlagOctreePass.h"
using namespace Hikari;
#define PAD16(x) ((x+15) & (~15))
#define MaxLevelRes 128
#define BrickRes 2
#define BricksPoolRes 128
#define FragmentMultiples 1
#define CURLEVEL 6
#define VoxelDispatchUnit 16
#define NodeDispatchUnit 4

Hikari::VoxelEffect::VoxelEffect(DirectRenderer * renderer, Scene * scene)
{

	orthoCamera = new Camera;

	Shader* vShader = renderer->CreateShader();
	Shader* pShader = renderer->CreateShader();
	Shader* gShader = renderer->CreateShader();
	vShader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/VoxelizationVS.hlsl",Shader::ShaderMacros(),"main","latest");
	gShader->LoadShaderFromFile(Shader::GeometryShader, "../Assets/shaders/VoxelizationGS.hlsl", Shader::ShaderMacros(), "main", "latest");
	pShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/VoxelizationPS.hlsl", Shader::ShaderMacros(), "main", "latest");
	
	//z
	XMFLOAT3 camPos = XMFLOAT3(0, 0, -0.5f);
	orthoCamera->LookAt(camPos, XMFLOAT3(camPos.x, camPos.y, camPos.z + 1), XMFLOAT3(0, 1, 0));
	orthoCamera->UpdateViewMatrix();
	XMMATRIX view0 = orthoCamera->View();

	//x
	camPos = XMFLOAT3(0.5f, 0, 0);
	orthoCamera->LookAt(camPos, XMFLOAT3(camPos.x-1, camPos.y, camPos.z), XMFLOAT3(0, 1, 0));
	orthoCamera->UpdateViewMatrix();
	XMMATRIX view1 = orthoCamera->View();
	//y
	camPos = XMFLOAT3(0, 0.5f, 0);
	orthoCamera->LookAt(camPos, XMFLOAT3(camPos.x, camPos.y-1, camPos.z), XMFLOAT3(0, 0, 1));
	orthoCamera->UpdateViewMatrix();
	XMMATRIX view2 = orthoCamera->View();

	XMMATRIX Proj = XMMatrixOrthographicLH(1, 1, 0.f, 1.0f);


	//Set Pipeline
	PipelineState* g_VoxelPipeline = renderer->CreatePipelineState();
	g_VoxelPipeline->SetShader(Shader::VertexShader, vShader);
	g_VoxelPipeline->SetShader(Shader::PixelShader, pShader);
	g_VoxelPipeline->SetShader(Shader::GeometryShader, gShader);
	g_VoxelPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::None);
	g_VoxelPipeline->GetRasterizerState().SetFillMode(RasterizerState::FillMode::Solid);
	g_VoxelPipeline->GetRasterizerState().SetFrontFacing(RasterizerState::FrontFace::ClockWise);
	g_VoxelPipeline->GetRasterizerState().SetDepthClipEnabled(FALSE);


	//Voxelization Pass
	VoxelizationPass::PerGeometry perGeometry;
	perGeometry.zproj = XMMatrixTranspose( view0*Proj);
	perGeometry.xproj = XMMatrixTranspose( view1*Proj);
	perGeometry.yproj = XMMatrixTranspose( view2*Proj);
	ConstantBuffer* geometryConstant = renderer->CreateConstantBuffer(&perGeometry, sizeof(perGeometry));

	VoxelizationPass::cbAttri cbAttri;
	cbAttri.origin = Float4(-.5f, .5f, -.5f,1.0f);
	cbAttri.extent = Float4(3.0f, 3.0f, 3.0f,0.0f);
	ConstantBuffer* cbAttrConstant = renderer->CreateConstantBuffer(&cbAttri, sizeof(cbAttri));

	//fragment
	uint32_t fragmentSize = sizeof(VoxelizationPass::Voxel) * 128 * 128 * 128;

	//bind uav Views
	StructuredBuffer* voxelUAVBuffer = renderer->CreateStructuredBuffer(nullptr, fragmentSize / sizeof(VoxelizationPass::Voxel),
		sizeof(VoxelizationPass::Voxel), CPUAccess::None, true, true,true);
	
	//bind uav Views
	RWBuffer* indexUAVBuffer = renderer->CreateRWBuffer(nullptr,1,4);


	//RenderTarget
	RenderTarget* renderTarget = renderer->CreateRenderTarget();
	renderTarget->AttachStructuredBuffer(0, voxelUAVBuffer);
	renderTarget->AttachRWBuffer(0, indexUAVBuffer);

	g_VoxelPipeline->SetRenderTarget(renderTarget);

	VoxelizationPass* voxelPass = new VoxelizationPass(renderer, scene, g_VoxelPipeline);

	//samplerstate
	SamplerState* sampler = renderer->CreateSamplerState();
	sampler->SetFilter(SamplerState::MinFilter::MinLinear,SamplerState::MagFilter::MagLinear,SamplerState::MipFilter::MipLinear);
	sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat);
	sampler->SetMaxAnisotropy(16);
	sampler->SetCompareFunction(SamplerState::CompareFunc::Never);
	sampler->SetMinLOD(-FLT_MAX);
	sampler->SetLODBias(0);
	sampler->SetMaxLOD(FLT_MAX);
	
	voxelPass->SetGeometryConstantBuffer(geometryConstant,"cbProj");
	voxelPass->SetCbAttriConstantBufferData(cbAttrConstant,"cbAttri");
	voxelPass->SetVoxelBuffer(voxelUAVBuffer,"FragmentList");
	voxelPass->SetIndexBuffer(indexUAVBuffer,"voxelIndex");
	voxelPass->SetSampler(sampler,"sam");
	
	ClearRenderTargetPass* clearPass = new ClearRenderTargetPass(renderer->mData->renderTarget);

	Shader* flagshader = renderer->CreateShader();
	Shader* allocShader = renderer->CreateShader();
	Shader* mipmapShader = renderer->CreateShader();
	Shader* writeLeafNode = renderer->CreateShader();
	Shader* visualSVO = renderer->CreateShader();
	Shader* visualCubeVS = renderer->CreateShader();
	Shader* visualCubePS = renderer->CreateShader();

	flagshader->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "FlagOctree.hlsl",
		Shader::ShaderMacros(), "main", "latest");
	allocShader->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "AllocOrtree.hlsl",
		Shader::ShaderMacros(), "main", "latest");
	mipmapShader->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "WriteLeafOctree.hlsl",
		Shader::ShaderMacros(), "main", "latest");
	writeLeafNode->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "MipmapOctree.hlsl",
		Shader::ShaderMacros(), "main", "latest");

	visualSVO->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "VisualSVOCS.hlsl", 
		Shader::ShaderMacros(),"main", "latest");

	visualCubeVS->LoadShaderFromFile(Shader::ShaderType::VertexShader, "VisualSVOVS.hlsl",
		Shader::ShaderMacros(), "main", "latest");

	visualCubePS->LoadShaderFromFile(Shader::ShaderType::PixelShader, "VisualSVOPS.hlsl",
		Shader::ShaderMacros(), "main", "latest");
	PipelineState* g_SVOPipeline = renderer->CreatePipelineState();
	g_SVOPipeline->SetShader(Shader::ShaderType::ComputeShader, flagshader);

	UINT u_brickInit = 0;
	UINT u_nodeInit = 1;
	RWBuffer* brickIndex = renderer->CreateRWBuffer(&u_brickInit, 1, sizeof(UINT));
	RWBuffer* nodeInedx = renderer->CreateRWBuffer(&u_nodeInit, 1, sizeof(UINT));
	UINT mTotalLevel = std::log2f(128) + 1;
	UINT mTotalNode = 0;
	UINT res = 128;
	while (res)
	{
		mTotalNode += (res * res * res);
		res /= 2;
	}
	std::vector<UINT> initNum;
	initNum.push_back(1);
	for (UINT i = 1; i < mTotalLevel; ++i)
	{
		initNum.push_back(0);
	}
	RWBuffer* numNode = renderer->CreateRWBuffer(initNum.data(), initNum.size(), sizeof(UINT));

	FlagOctreePass::CBInfo cbInfo;
	ConstantBuffer* cbConstantBuffer = renderer->CreateConstantBuffer(&cbInfo, sizeof(FlagOctreePass::CBInfo));

	FlagOctreePass::CBBrickInfo cbBrickInfo;
	ConstantBuffer* cbBrickConstant = renderer->CreateConstantBuffer(&cbBrickInfo, PAD16(sizeof(FlagOctreePass::CBBrickInfo)));

	FlagOctreePass::CBGroupInfo cbGroupInfo;
	ConstantBuffer* cbGroupConstant = renderer->CreateConstantBuffer(&cbGroupInfo, PAD16(sizeof(FlagOctreePass::CBGroupInfo)));

	StructuredBuffer* nodePool = renderer->CreateStructuredBuffer(nullptr, mTotalNode, sizeof(FlagOctreePass::Node), CPUAccess::None, true, true);
	
	UINT i[] = { 0 };
	RWBuffer* visualIndex = renderer->CreateRWBuffer(i,1,sizeof(UINT));
	FlagOctreePass* svoPass = new FlagOctreePass(renderer, scene, g_SVOPipeline);
	svoPass->SetTotalLevel(mTotalLevel);
	svoPass->SetTotalNode(mTotalNode);
	svoPass->SetBrickIndex(brickIndex, "");
	svoPass->SetNodeIndex(nodeInedx, "");
	svoPass->SetNumNode(numNode, "");
	svoPass->SetConstantInfo(cbConstantBuffer,"");
	svoPass->SetConstantGroup(cbGroupConstant, "");
	svoPass->SetNodeBuffer(nodePool, "");
	svoPass->SetConstantBrick(cbBrickConstant, "");
	svoPass->SetAttriConstant(cbAttrConstant, "");
	svoPass->SetVisualIndex(visualIndex,"");

	Shader* shaders[7]
	{
		flagshader,
		allocShader,
		mipmapShader,
		writeLeafNode,
		visualSVO,
		visualCubeVS,
		visualCubePS
	};
	svoPass->SetComputeShaders(shaders);
	VisualTechnique* forwardTechnique = new VisualTechnique();


	forwardTechnique->AddPass(clearPass);
	forwardTechnique->AddPass(voxelPass);
	forwardTechnique->AddPass(svoPass);
	InsertTechnique(forwardTechnique);
}

Hikari::VoxelEffect::~VoxelEffect()
{
}

VisualEffectInstance * Hikari::VoxelEffect::CreateInstance() const
{
	VisualEffectInstance* instance = new VisualEffectInstance(this, 0);
	return instance;
}
