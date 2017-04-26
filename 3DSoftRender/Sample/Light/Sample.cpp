#include "Sample.h"
#include "Scene.h"
#include "GraphicsPCH.h"
WINDOW_APPLICATION(Lights);
std::wstring configFileName = L"../Conf/DefaultConfiguration.conf";

ConfigurationSettings Lights::g_Setting;
Lights::Lights()
	:WindowApplication3("Light", 0, 0, 1366, 768,
		Float4(0.0f, 0.25f, 0.75f, 1.0f))
{
	if (!g_Setting.Load(configFileName))
		return;
	g_NumLightToGenerate = static_cast<uint32_t>(g_Setting.Lights.size());
	int width = g_Setting.WindowWidth;
	int height = g_Setting.WindowHeight;
	WindowApplication::SetWidth(width);
	WindowApplication::SetHeight(height);
}

bool Lights::OnInitialize()
{
	if (!WindowApplication3::OnInitialize())
		return false;

	mCamera->LookAt(XMFLOAT3(0.0f, 0.0f, -3.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));
	mCamera->SetLens(45.0f, mWidth / (float)mHeight, .1f, 1000.0f);
	mCamera->UpdateViewMatrix();
	CreateScene();
	
	
	return true;
}

void Lights::OnTerminate()
{
}

void Lights::OnIdle()
{
	mRenderer->Draw(nullptr,const_cast<VisualEffect*>(mInstance->GetEffect()));
}

bool Lights::OnKeyDown(unsigned char key, int x, int y)
{
	return false;
}

void Lights::CreateScene()
{
	mainScene = mRenderer->CreateScene();
	fs::path configFilePath(configFileName);
	fs::path sceneFilePath(g_Setting.SceneFileName);

	mainScene->LoadFromFile((configFilePath.parent_path() / sceneFilePath).wstring());
	mainScene->GetRootNode()->SetLocalTransform(HMatrix(
		g_Setting.SceneScaleFactor, 0, 0, 0,
		0, g_Setting.SceneScaleFactor, 0, 0,
		0, 0, g_Setting.SceneScaleFactor, 0,
		0, 0, 0, 1
	));
	LightEffect* lightEffect = new LightEffect(static_cast<DirectRenderer*>(mRenderer),mainScene,g_Setting.Lights);
	mInstance = lightEffect->CreateInstance();
}

void Lights::CreatePlane()
{
}

void Lights::CreateSphere()
{
}
