#include "Sample.h"
#include "Scene.h"
WINDOW_APPLICATION(Lights);

ConfigurationSettings Lights::g_Setting;
Lights::Lights()
	:WindowApplication3("Light", 0, 0, 1366, 768,
		Float4(0.0f, 0.25f, 0.75f, 1.0f))
{
	std::wstring configFileName = L"../../Conf/DefaultConfiguration.3dgep";
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

	mCamera->SetTranslate(Vector3f(g_Setting.CameraPosition.X, g_Setting.CameraPosition.Y, g_Setting.CameraPosition.Z));
	mCamera->SetRotate(Vector3f(g_Setting.CameraRotation.X, g_Setting.CameraRotation.Y, g_Setting.CameraRotation.Z));
	mCamera->SetPivotDistance(g_Setting.CameraPivotDistance);

	mCamera->SetViewport(Viewport(0, 0, mWidth, mHeight));
	mCamera->SetProjectionRH(45.0f, mWidth / (float)mHeight, .1f, 1000.0f);

	LightEffect* light = new LightEffect;
	mInstance = light->CreateInstance(mRenderer);
	CreateScene();
	
	
	return true;
}

void Lights::OnTerminate()
{
}

void Lights::OnIdle()
{
	
}

bool Lights::OnKeyDown(unsigned char key, int x, int y)
{
	return false;
}

void Lights::CreateScene()
{
	mainScene = mRenderer->CreateScene();
	mainScene->LoadFromFile(g_Setting.SceneFileName);
	mainScene->GetRootNode()->SetLocalTransform(HMatrix(
		g_Setting.SceneScaleFactor, 0, 0, 0,
		0, g_Setting.SceneScaleFactor, 0, 0,
		0, 0, g_Setting.SceneScaleFactor, 0,
		0, 0, 0, 1
	));
	

}

void Lights::CreatePlane()
{
}

void Lights::CreateSphere()
{
}
