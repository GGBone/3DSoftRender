#include <Windows.h>
#include <gdiplus.h>

#include "Lights.h"


#pragma comment(lib,"gdiplus.lib")

WINDOW_APPLICATION(Lights);
Lights::Lights()
	: WindowApplication3("Light",0, 0, 1366, 768,
		Float4(0.0f, 0.25f, 0.75f, 1.0f))
{
}

bool Lights::OnInitialize()
{
	if (!WindowApplication3::OnInitialize())
		return false;

	mCamera->SetProjParams(60.0f, GetAspectRatio(), 0.1f, 1000.0f);
	APoint camPosition(0, 64.0f, -500.0f);

	mCamera->SetViewParams(camPosition, APoint::ORIGIN);

	CreateScene();

	scene->Update();
	
	return true;
}

void Lights::OnTerminate()
{
}

void Lights::OnIdle()
{
	mRenderer->Draw((Visual*)scene->GetChild(0),mInstance);
}

bool Lights::OnKeyDown(unsigned char key, int x, int y)
{
	return false;
}

void Lights::CreateScene()
{
	scene = new Node();
	
	VertexFormat* vformat = VertexFormat::Create(3, VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT4, 0,
		VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 1);

	DefaultEffect* effect = new DefaultEffect();
	mInstance = effect->CreateInstance();

	StandardMesh sm(vformat);
	//scene = new Visual(vertexBuffer,indexBuffer);
	VertexBufferAccessor vba;

	mPlane = sm.Box(128,128,128);
	vba.ApplyTo(mPlane);
	for (int i = 0; i < vba.GetNumVertices(); ++i)
	{
//		vba.TCoord<Float3>(1, i) = vba.Normal<Float3>(i);
	}
	mPlane->localTransfrom.SetTranslate(APoint(0.0f, 8.0f, 0.0f));
	mPlane->SetEffectInstance(mInstance);
	scene->AttachChild(mPlane);
}

void Lights::CreatePlane()
{
}

void Lights::CreateSphere()
{
}
