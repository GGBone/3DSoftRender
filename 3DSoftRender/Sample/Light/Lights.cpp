#include <Windows.h>
#include <gdiplus.h>

#include "Lights.h"


#pragma comment(lib,"gdiplus.lib")

//
//using namespace Spirit2D;
//
//
//
//Camera4DV1 mainCamera;
//
//Vector4D vscale = { 1, 1, 1, 1 },
//vpos = { 0, 0, 0, 1 },
//vrot = { 0, 0, 0, 1 };
//
//RenderList rend_list;
//
//const int UNIVERSE_RADIUS = 4000;
//const int POINT_SIZE = 200;
//const int NUM_POINT_X = 2 * UNIVERSE_RADIUS / POINT_SIZE;
//const int NUM_POINT_Z = 2 * UNIVERSE_RADIUS / POINT_SIZE;
//const int NUM_POINTS = NUM_POINT_X * NUM_POINT_Z;
//
//const int NUM_TOWERS = 96;
//const int NUM_TANKS = 24;
//const int TANK_SPEED = 15;
//
//
//Object4DV1 obj_tower, obj_tank, obj_marker, obj_player;
//Point4D towers[NUM_TOWERS], tanks[NUM_TANKS];
//
//Point3D poly_pos = { 0, 0, 100};
//float bgcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
//void Game_Main();
//void Game_ShutDown();
//int Game_Init();
//HWND hWnd;
//HINSTANCE g_hInstance;
//HDC hdc;
//PAINTSTRUCT ps;
//HBRUSH hbr;
//#if _DX | _DEBUG
//	DXRender triangle;
//#endif

//
//void DrawLine(Vertex_2D v1, Vertex_2D v2)
//{
//	Line_2D(v1, v2);
//}
//
//int Game_Init()
//{
//#if _DX | _DEBUG
//	triangle.Initialize(g_hInstance, hWnd);
//
//	//float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	//triangle.ClearBuffer(color);
//#endif
//	
//	srand(Start_Clock());
//	
//	Open_Error_File("Error.txt");
//	Build_Sin_Cos_Tables();
//	RGB16Bit = RGB16BIT565;
//	
//	Point3D camPos(0, 0, -1000.0f);
//	Point3D camTarget(0, 0, 0);
//	mainCamera.SetViewParams(&camPos, &camTarget);
//	mainCamera.SetProjParams(120.0f, WIDTH / HEIGHT, 600.0f, 12000.0f);
//
//
//	vscale = Vector4D(.75, .75, .75, 1.0);
//	Load_Object_PLG(&obj_tank, "tank2.plg", vscale, vpos, vrot);
//
//	Load_Object_PLG(&obj_player, "tank3.plg", vscale, vpos, vrot);
//
//	Load_Object_PLG(&obj_tower, "tower1.plg", vscale, vpos, vrot);
//
//	Load_Object_PLG(&obj_marker, "marker1.plg", vscale, vpos, vrot);
//
//	for (auto index = 0; index < NUM_TANKS; ++index)
//	{
//		srand(time(0));
//		tanks[index][0] = (rand() % 400 - UNIVERSE_RADIUS);
//		tanks[index][1] = 0;
//		tanks[index][2] = (rand() % 400 - UNIVERSE_RADIUS);
//		tanks[index][3] = (rand() % 360);
//
//	}
//
//	for (auto i = 0; i < NUM_TOWERS; i++)
//	{
//		towers[i][0] = (rand() % 400 - UNIVERSE_RADIUS);
//		towers[i][1] = 0;
//		towers[i][2] = (rand() % 400 - UNIVERSE_RADIUS);
//	}
//	return 1;
//}
//
//void Reset_OBJECT4DV1(Object4DV1* obj)
//{
//	// this function resets the sent object and redies it for 
//	// transformations, basically just resets the culled, clipped and
//	// backface flags, but here's where you would add stuff
//	// to ready any object for the pipeline
//	// the object is valid, let's rip it apart polygon by polygon
//
//	// reset object's culled flag
//	//obj->state |= OBJECTDV1_STATE_CULLED;
//
//	// now the clipped and backface flags for the polygons 
//	for (int poly = 0; poly < obj->num_polys; poly++)
//	{
//		// acquire polygon
//		Poly4DV1* curr_poly = &obj->plist[poly];
//
//		// first is this polygon even visible?
//		if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE))
//			continue; // move onto next poly
//
//					  // reset clipped and backface flags
//		curr_poly->state &= ~POLY4DV1_STATE_CLIPPED;
//		curr_poly->state &= ~POLY4DV1_STATE_BACKFACE;
//
//	} // end for poly
//
//}
//
//
//void Game_Main()
//{
//	static Matrix4X4 mrot;
//	static float ang_y = 0;
//	static float camera_distance = 6000;
//	static Vector4D pos = { 0,0,0,0 };
//	static float tank_speed;
//	static float turning = 0;
//
//	char work_string[256];
//	Start_Clock();
//
//	//LoadIdentity();
//	//Reset_OBJECT4DV1(&obj);
//
//	//mainCamera.Reset();
//	if (KEY_DOWN(VK_DOWN))
//	{
//		mainCamera.FrameMove(-0.1F);
//	}
//	else if(KEY_DOWN(VK_UP))
//	{
//		mainCamera.FrameMove(0.1F);
//	}
//	//rend_list.Insert_PolyF4DV1_RenderList(poly1);
//	//绘制与代码顺序相反
//	//RotateByAix(0, 1, 0, ang_y);
//	//Translate(Vector3D(0, 0, 1), 1.0f);
//	//if (++ang_y >= 360.0) ang_y = 0.0f;
//	Model_To_WorldObject(obj_tank);
//
//	//ObjectToWorld(&obj);
//
//	mainCamera.Perspective(&obj_tank);
//	NDC2DC(&obj_tank, WIDTH - 1, HEIGHT - 1, 1.0f, 0.0f, 0.0f, 1.0f, 1.0, 0.0f);
//	//NDC2DC(rend_list,WIDTH - 1, HEIGHT - 1, 1.0f, 0.0f, 0.0f, 1.0f, 1.0, 0.0f);
//#if _DX || _DEBUG
//	triangle.Update(0.0f);
//	triangle.Render(obj_tank);
//#endif
//	Wait_Clock(1000/60);
//
//}
//void Game_ShutDown()
//{
//	
//}
//
//void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContex)
//{
//	mainCamera.FrameMove(fElapsedTime);
//}

WINDOW_APPLICATION(Lights);
Lights::Lights()
	: WindowApplication3("Light",0, 0, 800, 600,
		Float4(0.0f, 0.25f, 0.75f, 1.0f))
{
}

bool Lights::OnInitialize()
{
	CreateScene();
	return true;
}

void Lights::OnTerminate()
{
}

void Lights::OnIdle()
{
	mRenderer->Draw(scene);
}

bool Lights::OnKeyDown(unsigned char key, int x, int y)
{
	return false;
}

void Lights::CreateScene()
{
	
	static VertexPos vertices[] =
	{
		XMFLOAT3(-0.5f, -0.5f, 0.5f),
		XMFLOAT3(0.5f, 0.5f, 0.5f), 
		XMFLOAT3(0.5f, -0.5f, 0.5f), 

		XMFLOAT3(0.5f, 0.5f, 0.5f),
		XMFLOAT3(-0.5f, -0.5f, 0.5f),
		XMFLOAT3(-0.5f, 0.5f, 0.5f)
	};
	int size = sizeof(VertexPos);
	VertexBuffer* vertexBuffer = new VertexBuffer(6,sizeof(VertexPos));
	vertexBuffer->SetData((void*)vertices);
	VisualPass* pass = new VisualPass();
	VertexShader* vshader = new VertexShader("SolidGreenColor.fx");
	PixelShader* pshader = new PixelShader("SolidGreenColor.fx");
	pass->SetVertexShader(vshader);
	pass->SetPixelShader(pshader);
	scene = new Visual(vertexBuffer, pass);
}

void Lights::CreatePlane()
{
}

void Lights::CreateSphere()
{
}
