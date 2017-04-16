#pragma once
#include "WindowApplication3.h"
#include "ConfigurationSetting.h"
using namespace Hikari;
class Lights : public WindowApplication3
{
	DECLARE_INITIALIZE;
	DECLEAR_TERMINATE;
public:
	Lights();
	virtual bool OnInitialize() override;
	virtual void OnTerminate();
	virtual void OnIdle();
	virtual bool OnKeyDown(unsigned char key, int x, int y);

protected:
	void CreateScene();
	void CreatePlane();
	void CreateSphere();
	Scene* mainScene;

	Scene* g_FullScreenQuad;
	
	Float4 g_ClearColor;

	static ConfigurationSettings g_Setting;
	uint32_t g_NumLightToGenerate;

	VisualEffectInstance* mInstance;
};
REGISTER_INITIALIZE(Lights);
REGISTER_TERMINATE(Lights);