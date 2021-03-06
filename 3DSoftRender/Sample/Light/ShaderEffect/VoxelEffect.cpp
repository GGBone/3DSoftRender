#include "VoxelDefine.h"
#include "VoxelEffect.h"
#include "ClearRenderTargetPass.h"
#include "VoxelizationPass.h"
#include "FlagOctreePass.h"
#include "SceneGraph/Camera.h"
#include "Resource/RasterizerState.h"
#include "SceneGraph/VisualEffectInstance.h"
using namespace Hikari;

VoxelEffect::VoxelEffect(std::shared_ptr<RenderWindow> rwindow, std::shared_ptr<Renderer> renderer,
                         std::shared_ptr<Scene> scene)
{
	orthoCamera = new Camera;
	std::shared_ptr<Shader> vShader = renderer->CreateShader();
	std::shared_ptr<Shader> pShader = renderer->CreateShader();
	std::shared_ptr<Shader> gShader = renderer->CreateShader();
	vShader->LoadShaderFromFile(Shader::VertexShader, "../Assets/shaders/Voxelization/VoxelizationVS.hlsl",
	                            Shader::ShaderMacros(), "main", "latest");
	gShader->LoadShaderFromFile(Shader::GeometryShader, "../Assets/shaders/Voxelization/VoxelizationGS.hlsl",
	                            Shader::ShaderMacros(), "main", "latest");
	pShader->LoadShaderFromFile(Shader::PixelShader, "../Assets/shaders/Voxelization/VoxelizationPS.hlsl",
	                            Shader::ShaderMacros(), "main", "latest");

	//z
	XMFLOAT3 camPos = XMFLOAT3(0, 0, -0.5f);
	orthoCamera->LookAt(camPos, XMFLOAT3(camPos.x, camPos.y, camPos.z + 1), XMFLOAT3(0, 1, 0));
	orthoCamera->UpdateViewMatrix();
	XMMATRIX view0 = orthoCamera->View();

	//x
	camPos = XMFLOAT3(0.5f, 0, 0);
	orthoCamera->LookAt(camPos, XMFLOAT3(camPos.x - 1, camPos.y, camPos.z), XMFLOAT3(0, 1, 0));
	orthoCamera->UpdateViewMatrix();
	XMMATRIX view1 = orthoCamera->View();
	//y
	camPos = XMFLOAT3(0, 0.5f, 0);
	orthoCamera->LookAt(camPos, XMFLOAT3(camPos.x, camPos.y - 1, camPos.z), XMFLOAT3(0, 0, 1));
	orthoCamera->UpdateViewMatrix();
	XMMATRIX view2 = orthoCamera->View();

	XMMATRIX Proj = XMMatrixOrthographicLH(1, 1, 0.f, 1.0f);


	//set Pipeline
	std::shared_ptr<PipelineState> g_VoxelPipeline = renderer->CreatePipelineState();
	g_VoxelPipeline->SetShader(Shader::VertexShader, vShader);
	g_VoxelPipeline->SetShader(Shader::PixelShader, pShader);
	g_VoxelPipeline->SetShader(Shader::GeometryShader, gShader);
	g_VoxelPipeline->GetRasterizerState().SetCullMode(RasterizerState::CullMode::None);
	g_VoxelPipeline->GetRasterizerState().SetFillMode(RasterizerState::FillMode::Solid);
	g_VoxelPipeline->GetRasterizerState().SetFrontFacing(RasterizerState::FrontFace::ClockWise);
	g_VoxelPipeline->GetRasterizerState().SetDepthClipEnabled(FALSE);


	//Voxelization Pass
	VoxelizationPass::PerGeometry perGeometry{};
	perGeometry.zproj = XMMatrixTranspose(view0 * Proj);
	perGeometry.xproj = XMMatrixTranspose(view1 * Proj);
	perGeometry.yproj = XMMatrixTranspose(view2 * Proj);

	VoxelizationPass::Attri cbAttri{};
	cbAttri.origin = Float4(-.5f, .5f, -.5f, 1.0f);
	cbAttri.extent = Float4(3.0f, 3.0f, 3.0f, 0.0f);

	//fragment
	uint32_t fragmentSize = sizeof(VoxelizationPass::Voxel) * MaxLevelRes * MaxLevelRes * MaxLevelRes *
		FragmentMultiples;

	const ShaderParameter::ShaderInputParameter voxel_uav_parameter = {
		ShaderParameter::ShaderInputType::StructuredBuffer,
		ShaderParameter::AppendFlag::APPEND,
		ShaderParameter::Format::UNKNOWN,
		CPUAccess::None,
		GPUAccess::ReadWrite
	};
	//bind uav Views
	const auto voxelUAVBuffer = renderer->CreateStructuredBuffer(
		nullptr, fragmentSize / sizeof(VoxelizationPass::Voxel),
		sizeof(VoxelizationPass::Voxel), voxel_uav_parameter);

	//bind uav Views
	const ShaderParameter::ShaderInputParameter index_uav_parameter = {
		ShaderParameter::ShaderInputType::Buffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::R32_SINT,
		CPUAccess::Write,
		GPUAccess::Write
	};
	const auto indexData = 0;
	const auto indexUAVBuffer = renderer->CreateBuffer(indexData, index_uav_parameter);


	//RenderTarget
	std::shared_ptr<RenderTarget> renderTarget = renderer->CreateRenderTarget();
	renderTarget->AttachStructuredBuffer(0, voxelUAVBuffer);
	renderTarget->AttachBuffer(0, indexUAVBuffer);

	g_VoxelPipeline->SetRenderTarget(renderTarget);


	std::shared_ptr<VoxelizationPass> voxelPass = std::make_shared<VoxelizationPass>(renderer, scene, g_VoxelPipeline);

	//samplerstate
	std::shared_ptr<SamplerState> sampler = renderer->CreateSamplerState();
	sampler->SetFilter(SamplerState::MinFilter::MinLinear, SamplerState::MagFilter::MagLinear,
	                   SamplerState::MipFilter::MipLinear);
	sampler->SetWrapMode(SamplerState::WrapMode::Repeat, SamplerState::WrapMode::Repeat,
	                     SamplerState::WrapMode::Repeat);
	sampler->SetMaxAnisotropy(16);
	sampler->SetCompareFunction(SamplerState::CompareFunc::Never);
	sampler->SetMinLOD(-FLT_MAX);
	sampler->SetLODBias(0);
	sampler->SetMaxLOD(FLT_MAX);

	voxelPass->SetPerGeometryConstantData(perGeometry, "cbProj");
	voxelPass->SetAttriConstantData(cbAttri, "cbAttri");

	voxelPass->SetSampler(sampler, "sam");


	//std::shared_ptr<Query> query = renderer->CreateQuery(Query::QueryType::Timer, 2);
	std::shared_ptr<RenderTarget> renderTargetSVO = rwindow->GetRenderTarget();

	std::shared_ptr<ClearRenderTargetPass> clearPass = std::make_shared<ClearRenderTargetPass>(renderTargetSVO);

	std::shared_ptr<Shader> flagshader = renderer->CreateShader();
	std::shared_ptr<Shader> allocShader = renderer->CreateShader();
	std::shared_ptr<Shader> mipmapShader = renderer->CreateShader();
	std::shared_ptr<Shader> writeLeafNode = renderer->CreateShader();
	std::shared_ptr<Shader> visualSVO = renderer->CreateShader();
	std::shared_ptr<Shader> visualCubeVS = renderer->CreateShader();
	std::shared_ptr<Shader> visualCubePS = renderer->CreateShader();

	flagshader->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "../Assets/shaders/OctTree/FlagOctree.hlsl",
	                               Shader::ShaderMacros(), "main", "latest");
	allocShader->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "../Assets/shaders/OctTree/AllocOrtree.hlsl",
	                                Shader::ShaderMacros(), "main", "latest");
	mipmapShader->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "../Assets/shaders/OctTree/MipmapOctree.hlsl",
	                                 Shader::ShaderMacros(), "main", "latest");
	writeLeafNode->LoadShaderFromFile(Shader::ShaderType::ComputeShader,
	                                  "../Assets/shaders/OctTree/WriteLeafOctree.hlsl",
	                                  Shader::ShaderMacros(), "main", "latest");

	visualSVO->LoadShaderFromFile(Shader::ShaderType::ComputeShader, "../Assets/shaders/Visualization/VisualSVOCS.hlsl",
	                              Shader::ShaderMacros(), "main", "latest");

	visualCubeVS->LoadShaderFromFile(Shader::ShaderType::VertexShader,
	                                 "../Assets/shaders/Visualization/VisualSVOVS.hlsl",
	                                 Shader::ShaderMacros(), "main", "latest");

	visualCubePS->LoadShaderFromFile(Shader::ShaderType::PixelShader,
	                                 "../Assets/shaders/Visualization/VisualSVOPS.hlsl",
	                                 Shader::ShaderMacros(), "main", "latest");

	std::shared_ptr<PipelineState> g_SVOPipeline = renderer->CreatePipelineState();
	g_SVOPipeline->SetShader(Shader::ShaderType::ComputeShader, flagshader);
	g_SVOPipeline->SetRenderTarget(renderTargetSVO);

	const auto mTotalLevel = (UINT)std::log2f(MaxLevelRes) + 1;
	auto mTotalNode = 0;
	auto res = MaxLevelRes;
	while (res)
	{
		mTotalNode += (res * res * res);
		res /= 2;
	}

	FlagOctreePass::CBInfo cbInfo{};

	FlagOctreePass::CBBrickInfo cbBrickInfo{};

	FlagOctreePass::CBGroupInfo cbGroupInfo{};


	const ShaderParameter::ShaderInputParameter node_uav_pool = {
		ShaderParameter::ShaderInputType::StructuredBuffer,
		ShaderParameter::AppendFlag::RAW,
		ShaderParameter::Format::UNKNOWN,
		CPUAccess::None,
		GPUAccess::ReadWrite
	};
	std::shared_ptr<StructuredBuffer> nodePool = renderer->CreateStructuredBuffer(
		nullptr, mTotalNode, sizeof(FlagOctreePass::Node), node_uav_pool);

	std::vector<UINT> visualIndex;
	visualIndex.push_back(0);
	
	std::shared_ptr<FlagOctreePass> svoPass = std::make_shared<FlagOctreePass>(renderer, scene, g_SVOPipeline);
	svoPass->SetTotalLevel(mTotalLevel);
	svoPass->SetTotalNode(mTotalNode);

	svoPass->SetConstantInfo(cbInfo, "");
	svoPass->SetConstantGroup(cbGroupInfo, "");

	svoPass->SetConstantBrick(cbBrickInfo, "");
	svoPass->SetAttriConstant(cbAttri, "");

	std::shared_ptr<Shader> shaders[7]
	{
		flagshader,
		allocShader,

		writeLeafNode,
		mipmapShader,

		visualSVO,
		visualCubeVS,
		visualCubePS
	};
	svoPass->SetComputeShaders(shaders, 7);
	std::shared_ptr<VisualTechnique> forwardTechnique = std::make_shared<VisualTechnique>();


	forwardTechnique->AddPass(clearPass);
	forwardTechnique->AddPass(voxelPass);
	forwardTechnique->AddPass(svoPass);
	InsertTechnique(forwardTechnique);
}

VoxelEffect::~VoxelEffect()
= default;

std::shared_ptr<VisualEffectInstance> VoxelEffect::CreateInstance()
{
	const auto instance = std::make_shared<VisualEffectInstance>(shared_from_this(), 0);
	return instance;
}
