#pragma once
#include "Application\WindowApplicationEngine.h"

using namespace Hikari;
class Lights : public WindowApplicationEngine
{
	DECLARE_INITIALIZE;
	DECLEAR_TERMINATE;
	typedef WindowApplicationEngine base;
public:
	Lights();
	virtual bool OnInitialize(EventArgs& e) override;
	virtual ~Lights();
public:
	
protected:
	void CreateScene();
	void CreatePlane();
	void CreateSphere();
	void CreateLightShape();
	void CreateAxis();
	void CreateTransparentSlice();
private:
	Float4 g_ClearColor;

	uint32_t g_NumLightToGenerate;



};
REGISTER_INITIALIZE(Lights);
REGISTER_TERMINATE(Lights);