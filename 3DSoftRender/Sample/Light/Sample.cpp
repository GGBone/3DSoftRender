#include "Sample.h"

#include "ShaderEffect/VoxelEffect.h"
#include "ShaderEffect/LightEffect.h"
#include "ShaderEffect/ClearEffect.h"
#include "ShaderEffect/DefaultEffect.h"
#include "SceneGraph/Camera.h"
#include "SceneGraph/Scene.h"
#include "SceneGraph/Node.h"
#include "Renderer/ProgressWindow.h"

WINDOW_APPLICATION(Lights);
std::wstring configFileName = L"../Conf/DefaultConfiguration.conf";
extern ConfigurationSettings g_Setting;

Lights::Lights()
	: base("Light", 0, 0, 1280, 760)
{
	if (!g_Setting.Load(configFileName))
		return;
	g_NumLightToGenerate = static_cast<uint32_t>(g_Setting.Lights.size());
	int width = g_Setting.WindowWidth;
	int height = g_Setting.WindowHeight;
	SetWidth(width);
	SetHeight(height);
}


bool Lights::OnInitialize(EventArgs& e)
{
	if (!base::OnInitialize(e))
		return false;

	mCamera->LookAt(XMFLOAT3(0.0f, 0.0f, -10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));
	mCamera->SetProjectLH(XMConvertToRadians(45.0f), mWidth / (float)mHeight, .1f, 5000.0f);
	mCamera->UpdateViewMatrix();

	std::shared_ptr<ClearEffect> clearEffect = std::make_shared<ClearEffect>(mRenderWindow, m_pRenderDevice);
	mInstance.push_back(clearEffect->CreateInstance());
	CreateScene();
	//CreatePlane();
	CreateLightShape();
	CreateAxis();

	return true;
}

Lights::~Lights()
= default;

void Lights::CreateAxis()
{
	auto g_Axis = m_pRenderDevice->CreateAxis(0.01f, 0.1f);
	g_Axis->GetRootNode()->SetLocalTransform(HMatrix::IDENTITY);
	auto axisEffect = make_shared<DefaultEffect>(m_pRenderDevice, g_Axis);

	mInstance.push_back(axisEffect->CreateInstance());
}

void Lights::CreateTransparentSlice()
{
}

void Lights::CreateLightShape()
{
	std::vector<std::shared_ptr<Scene>> lightSphere;
	lightSphere.reserve(10);

	for (const Light& e : g_Setting.Lights)
	{
		std::shared_ptr<Scene> temp;
		switch (e.m_Type)
		{
		case Light::LightType::Point:
			{
				temp = m_pRenderDevice->CreateSphere(1.0f);
				HMatrix sphereTransform(
					1.0f, 0, 0, 0,
					0, 1.0f, 0, 0,
					0, 0, 1.0f, 0.f,
					e.m_PositionWS[0], e.m_PositionWS[1],
					e.m_PositionWS[2], 1.0f
				);
				temp->GetRootNode()->SetLocalTransform(sphereTransform);
				lightSphere.push_back(temp);
			}
			break;
		case Light::LightType::Directional:
			{
				//e.m_DirectionWS
				temp = m_pRenderDevice->CreateCylinder(1.f, 1.0f, 2.0f, AVector(1.0f, 1.0f, 1.0f));
				HMatrix sphereTransform(
					1.0f, 0, 0, 0,
					0, 1.0f, 0, 0,
					0, 0, 1.0f, 0.f,
					e.m_PositionWS[0], e.m_PositionWS[1],
					e.m_PositionWS[2], 1.0f
				);

				temp->GetRootNode()->SetLocalTransform(sphereTransform);
				lightSphere.push_back(temp);
			}
			break;
		case Light::LightType::Spot:
			{
				temp = m_pRenderDevice->CreateCylinder(0.f, 1.0f, 2.0f, AVector(e.m_DirectionWS));
				HMatrix sphereTransform(
					1.0f, 0, 0, 0,
					0, 1.0f, 0, 0,
					0, 0, 1.0f, 0.f,
					e.m_PositionWS[0], e.m_PositionWS[1],
					e.m_PositionWS[2], 1.0f
				);
				temp->GetRootNode()->SetLocalTransform(sphereTransform);
				lightSphere.push_back(temp);
			}
			break;
		default:
			break;
		}
	}
	vector<shared_ptr<Scene>> transScene;
	for (int i = 0; i != g_NumLightToGenerate; ++i)
	{
		auto sphereEffect = std::make_shared<LightEffect>(mRenderWindow, m_pRenderDevice, lightSphere, transScene);
		mInstance.push_back(sphereEffect->CreateInstance());
		sphereEffect.reset();
	}
}

void Lights::CreateScene()
{
	vector<shared_ptr<Scene>> opaqueScene;
	mainScene = m_pRenderDevice->CreateScene();
	fs::path configFilePath(configFileName);
	fs::path sceneFilePath(g_Setting.SceneFileName);

	mainScene->LoadFromFile((configFilePath.parent_path() / sceneFilePath).wstring());
	mProgressWindow->CloseWindows();

	mRenderWindow->ShowWindow();
	HMatrix CubeTransform(
		g_Setting.SceneScaleFactor, 0, 0, 0,
		0, g_Setting.SceneScaleFactor, 0, 0,
		0, 0, g_Setting.SceneScaleFactor, 0.f,
		0, -1.f, 0.f, 1
	);
	mainScene->GetRootNode()->SetLocalTransform(CubeTransform);
	opaqueScene.push_back(mainScene);
	//transScene
	vector<shared_ptr<Scene>> transScene;
	transScene.reserve(12);
	for (int i = 0; i < 12; ++i)
	{
		auto slice1 = m_pRenderDevice->CreatePlane(1.f, AVector(0, 0, 1));
		slice1->GetRootNode()->SetLocalTransform(HMatrix(
			1.0f, 0, 0, 0,
			0, 1.0f, 0, 0,
			0, 0, 1.0f, 0.f,
			0.0f, 1.0f, -10.0f + i * 0.02, 1.0f
		));
		transScene.push_back(slice1);
	}

	std::shared_ptr<Scene> ground = m_pRenderDevice->CreatePlane(10.0f);
	HMatrix groundTransform(g_Setting.SceneScaleFactor, 0, 0, 0,
	                        0, g_Setting.SceneScaleFactor, 0, 0,
	                        0, 0, g_Setting.SceneScaleFactor, 0.f,
	                        0, -2.0f, 0.f, 1);
	ground->GetRootNode()->SetLocalTransform(groundTransform);
	opaqueScene.push_back(ground);

	auto lightEffect = std::make_shared<LightEffect>(mRenderWindow, m_pRenderDevice, opaqueScene, transScene);
	mInstance.push_back(lightEffect->CreateInstance());
#if !defined(VOXEL)
	std::shared_ptr<VoxelEffect> voxelEffect = std::make_shared<VoxelEffect>(mRenderWindow, m_pRenderDevice, mainScene);
	mInstance.push_back(voxelEffect->CreateInstance());
#endif
}

void Lights::CreatePlane()
{
	//std::shared_ptr<LightEffect> groundEffect = std::make_shared<LightEffect>(mRenderWindow, m_pRenderDevice, ground,nullptr);
	//mInstance.push_back(groundEffect->CreateInstance());
}

void Lights::CreateSphere()
{
}
