#pragma once
#include "WindowApplication3.h"
#include "Float4.h"
#include "VisualEffectInstance.h"
#include "DefaultEffect.h"
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
	Visual* scene;
protected:
	void CreateScene();
	void CreatePlane();
	void CreateSphere();

	Float4 mTextColor;
	VisualEffectInstance* mInstance;
};
REGISTER_INITIALIZE(Lights);
REGISTER_TERMINATE(Lights);