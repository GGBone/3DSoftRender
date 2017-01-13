#pragma once
#include "Global.h"
#include "ReadFile.h"
#include "Math.h"

using namespace std;
using namespace  CORE;
//Bob Function


// this builds a 16 bit color value in 5.5.5 format (1-bit alpha mode)
#define _RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))

// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))

// this builds a 24 bit color value in 8.8.8 format 
#define _RGB24BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) )

// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

class VertexBuffer
{

};
class Visual
{
public:
	enum Primitype
	{
		NONE,POLYPOINT,
		POLYSEGMENTS,
		TRIANGLES
	};
	Visual(){}
	virtual ~Visual();
};

class Triangle :public Visual
{
public:
	Triangle(Primitype type = TRIANGLES);

	~Triangle();

private:

};

//基于外部定点列表的多边形
extern void LoadIdentity();

class Poly4DV1
{
public:
	int state;
	int attr;
	int color;
	Point4D* vlist;
	//save the index
	int vert[3];
	Poly4DV1(){}
};
class PolyF4DV1: public Object
{
public:
	int state;
	int attr;
	int color;
	Point4D vlist[3];
	Point4D tvlist[3];
	PolyF4DV1* next;
	PolyF4DV1* prev;
};

class SpotLight
{
	//Light Attenuated
	float alpha = 1;

	//P是光源，V是被照亮的定点
	//float beta = 1 / (c0+c1*abs(V-P)+c2*abs(V-P)*(V-P));
};

class Object4DV1:public Object
{
public:
	Object4DV1()
	{
	}
	int id;
	char name[64];
	int state;
	int attr;
	float avg_radius;
	float max_ratius;
	Point4D world_pos;

	Point4D dir;
	Vector4D ux, uy, uz;
	int num_vertices;
	Point4D vlist_local[OBJECT4DV1_MAX_VERTICES];
	Point4D vlist_trans[OBJECT4DV1_MAX_VERTICES];

	int num_polys;
	Poly4DV1 plist[OBJECT4DV1_MAX_POLYS];
	//const Rtti& GetRttiType()const;
	// Object* GetObjectByName(const std::string& name);
	// void GetAllObjectsByName(const std::string& name, std::vector<Object*>& objects);
	~Object4DV1()
	{

	}
};
class Phong:public Object
{
	//
public:
	Phong(){}
	int id;
	char name[64];
	int state;
	int attr;
	float avg_radius;
	float max_ratius;
	Point4D world_pos;

	Point4D dir;
	Vector4D ux, uy, uz;
	int num_vertices;
	Point4D vlist_local[OBJECT4DV1_MAX_VERTICES];
	Point4D vlist_trans[OBJECT4DV1_MAX_VERTICES];

	int num_polys;
	Poly4DV1 plist[OBJECT4DV1_MAX_POLYS];
	~Phong()
	{
	}
};


class RenderList
{
public:
	int state;
	int attr;
	vector<PolyF4DV1*> polyPoint_vector;
	PolyF4DV1* poly_ptrs[RENDERLIST4DV1_MAX_POLYS];

	PolyF4DV1 poly_data[RENDERLIST4DV1_MAX_POLYS];

	int num_polys;
public:
	int Insert_PolyF4DV1_RenderList(PolyF4DV1 & poly);
	RenderList() :polyPoint_vector(RENDERLIST4DV1_MAX_POLYS){}
	inline void Reset(){ num_polys = 0; }
};



extern DWORD Get_Clock(void);
extern DWORD Start_Clock(void);
extern DWORD Wait_Clock(DWORD count);



extern int Collision_Test(int x1, int y1, int w1, int h1,
	int x2, int y2, int w2, int h2);

extern int Color_Scan(int x1, int y1, int x2, int y2, UCHAR scan_start, UCHAR scan_end, UCHAR* scan_buffer, int scan_lpitch);

extern int Color_Scan16(int x1, int y1, int x2, int y2, USHORT sca_start, USHORT scan_end, UCHAR* scan_buffer, int scan_lpitch);

//Graphics function


extern int Load_Object_PLG(Object4DV1* obj, char* filename, Vector4D& scale, Vector4D& pos, Vector4D& rot);

//extern void Translate_Object(Object* obj, Vector4D* vt);
//extern void Scale_Object(Object* object, Vector4D* vs);
extern void Build_XYZ_Rotation__Matrix4X4();	//will be wrote in Constructure
extern void TransformRendList(RenderList& rendlist, Matrix4X4& mt, int select = TRANSFORM_LOCAL_ONLY);
extern void Rotate_XYZ_Object();
extern void RotateByAix(int x, int y, int z, float angle);
extern void ClearBuffer(HWND& hwnd, HDC& hdc, HBRUSH& hbrush, PAINTSTRUCT& ps,float color[4]);

extern void NDC2DC(RenderList& rendlist, int width, int height, float pr, float pl, float pb, float pt, float pf, float pn);
extern void NDC2DC(Object* object, int width, int height, float pr, float pl, float pb, float pt, float pf, float pn);

extern void Translate(Vector3D direction, float distance);
extern void pix(void* render, int x, int y, int color);
extern void rect(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
extern void fill(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
extern void linerect(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps, int x, int y, int width, int height, COLORREF colorR, COLORREF colorG, COLORREF colorB);
//extern void triangle(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
extern void lineBresenham(void* p, int x0, int y0, int x1, int y1, int Color);
extern void ellipse(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
extern void DrawContent(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);

extern void ObjectToWorld(Object* obj, int coord_select = TRANSFORM_LOCAL_TO_TRANS);

extern LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern int ClipLine(int& x1, int& y1, int& x2, int& y2);
extern int DrawLine(int x0, int y0, int x1, int y1, int color, void* vb_start);
extern int DrawClipLine(int x0, int y0, int x1, int y1, int color, void* dest_buffer);

extern USHORT(*RGB16Bit)(int r, int g, int b);
extern USHORT RGB16BIT565(int r, int g, int b);
extern USHORT RGB16BIT555(int r, int g, int b);

extern void Model_To_WorldRendlist(RenderList&, Point3D&, int coord_select = TRANSFORM_LOCAL_ONLY);
extern void Model_To_WorldObject(Object4DV1& object);
#if _DX | _DEBUG
class DXBase
{
public:
	DXBase();
	virtual ~DXBase();
	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void ShutDown();
	bool CompilerD3DShader(TCHAR* filepath, char* entry, char* shaderModel, ID3DBlob** buffer);
	virtual bool LoadContent();
	virtual void UnloadContent();
	virtual void Update(float dt) = 0;
	virtual void Render(RenderList&) = 0;
protected:
	HINSTANCE hInstance;
	HWND hwnd;
	D3D_FEATURE_LEVEL featurelevel;
	D3D_DRIVER_TYPE driverType;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;
	ID3D11Texture2D* backBufferTexture;
};

class DXRender : public DXBase
{
public:
	DXRender();
	virtual ~DXRender();
	bool LoadContent();
	void UnloadContent();
	void Update(float dt);
	void Render(RenderList&);
	void Render(Object4DV1& object);
	void ClearBuffer(float color[4]);
	void* drawBuffer;
private:
	ID3D11VertexShader* solidColorVS;
	ID3D11PixelShader* solidColorPS;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vertexBuffer;

	ID3D11ShaderResourceView* pSRView;
	ID3D11SamplerState* sampler;

	ID3D11Texture2D *renderTexture;

	D3D11_MAPPED_SUBRESOURCE mp;
};

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};
#endif
