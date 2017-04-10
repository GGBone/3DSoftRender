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
	APoint camPosition(1.0f, .0f, 1.5f);
	//XMVECTOR UP = XMVectorSet(0.0f, 1.0f, 0.0, 0.0f);
	//XMVECTOR Pos = XMVectorSet(0, 100.0f, -1000.0f,1.0f);
	//XMVECTOR Target = XMVectorSet(0, .0f,.0f,1.0f);

	//XMMATRIX temp = XMMatrixLookAtLH(Pos,Target,UP);
	//XMFLOAT4X4 matrix;
	//XMStoreFloat4x4(&matrix, XMMatrixTranspose(temp));
	//
	//XMVECTOR dirNor = XMVector4Normalize(Target - Pos);
	//XMFLOAT4 dirNorTemp;
	//XMStoreFloat4(&dirNorTemp, dirNor);
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

	const char * path = "../../External/Data/cube.obj";
	std::vector<unsigned short>  out_indices;
	std::vector<Vector3f> out_vertices;
	std::vector<Vector2f> out_uvs;
	std::vector<Vector3f> out_normals;
	MeshLoader mesh;
	mesh.loadMesh_assimp(path, out_indices, out_vertices, out_uvs, out_normals);

	scene = new Node();

	VertexFormat* vformat = VertexFormat::Create(3, VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
	DefaultEffect* effect = new DefaultEffect();
	mInstance = effect->CreateInstance();

	StandardMesh sm(vformat);

	VertexBufferAccessor vba;

	//mPlane = sm.Box(128,128,128);
	//vba.ApplyTo(mPlane);
	
	mPlane = sm.ExternalModel(4, out_indices, out_vertices, out_uvs, out_normals);
	vba.ApplyTo(mPlane);
	mPlane->localTransfrom.SetTranslate(APoint(0.0f, 0.0f, 0.0f));
	mPlane->SetEffectInstance(mInstance);
	scene->AttachChild(mPlane);
}

void Lights::CreatePlane()
{
}

void Lights::CreateSphere()
{
}
