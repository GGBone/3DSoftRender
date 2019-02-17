#pragma once
#include "../../LibApplication/WindowApplicationEngine.h"
#include "../../LibCore/InitTerm.h"
#include "../../LibMathematics/Base/Float4.h"

namespace Hikari
{
	class EventArgs;
}

using namespace Hikari;

class Lights : public WindowApplicationEngine
{
DECLARE_INITIALIZE;
DECLEAR_TERMINATE;
	typedef WindowApplicationEngine base;
public:
	Lights();
	bool OnInitialize(EventArgs& e) override;
	void OnRender(RenderEventArgs& e) override;
	void MouseMoved(MouseMotionEventArgs& e)override;
	void KeyPress(KeyEventArgs& e) override;
	void MouseButtonReleased(MouseButtonEventArgs& e) override;
	void MouseButtonPressed(MouseButtonEventArgs& e) override;
	virtual ~Lights();
public:

protected:
	void CreateScene();
	static void CreatePlane();
	static void CreateSphere();
	void CreateLightShape();
	void CreateAxis();
	static void CreateTransparentSlice();
private:
	Float4 g_ClearColor;
	//observer
	Camera* mCamera;
	uint32_t g_NumLightToGenerate{};
};

REGISTER_INITIALIZE(Lights);
REGISTER_TERMINATE(Lights);
