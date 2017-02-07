#pragma once

#include "GraphicsLIB.h"
#include "Float4.h"
#include "Buffer.h"
#include "VertexBuffer.h"
#include "Visual.h"
#include <DirectXMath.h>
using namespace DirectX;
// this builds a 16 bit color value in 5.5.5 format (1-bit alpha mode)
#define _RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))

// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))

// this builds a 24 bit color value in 8.8.8 format 
#define _RGB24BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) )

// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))
namespace Hikari
{
	struct VertexPos
	{
		XMFLOAT3 pos;
	};
	class Texture
	{
	public:
		class Format
		{
		public:
			Format()
			{

			}
		};
	};
	class AlphaState;
	class CullState;
	class DepthState;
	class OffsetState;
	class StencilState;
	class WireState;
	class Camera;

	class VertexFormat;
	class IndexBuffer;

	class Texture1D;
	class Texture2D;
	class Texture3D;
	class TextureCube;

	class RenderTarget;

	class VertexShader;

	class PixelShader;

	class HMatrix;

	class Mutex;

	class APoint;
	class AVector;
	class VisibleSet;
	class GlobalEffect;
	class VisualEffectInstance;
	class RendererData;
	class Renderer
	{
	public:
		void Initialize(int width, int height, Texture::Format colorFormat,
			Texture::Format depthStencilFormat, int numMultisamples);
		void Terminate();
		inline int GetWidth() const;
		inline int GetHeight() const;
		inline Texture::Format GetColorFormat()const;
		inline Texture::Format GetDepthStencilFormat() const;
		inline int GetNumMultisamples() const;


		void Bind(const VertexFormat* vFormat);
		static void BindAll(const VertexFormat* vformat);
		void Unbind(const VertexFormat* vFormat);
		static void UnBindAll(const VertexFormat* vFormat);

		void Enable(const VertexFormat* vFormat);
		void Disable(const VertexFormat* vFormat);

		//Vertex
		void Bind(const VertexBuffer* vFormat);
		static void BindAll(const VertexBuffer* vformat);
		void Unbind(const VertexBuffer* vFormat);
		static void UnBindAll(const VertexBuffer* vFormat);

		void Enable(const VertexBuffer* vFormat);
		void Disable(const VertexBuffer* vFormat);

		void* Lock(const VertexBuffer* vbuffer, Buffer::Locking mode);
		void UnLock(const VertexBuffer* vbBuffer);

		void Update(const VertexBuffer* vbuffer);
		static void UpdateAll(const VertexBuffer* vbuffer);


		//Index
		void Bind(const IndexBuffer* vFormat);
		static void BindAll(const IndexBuffer* vformat);
		void Unbind(const IndexBuffer* vFormat);
		static void UnBindAll(const IndexBuffer* vFormat);

		void Enable(const IndexBuffer* vFormat);
		void Disable(const IndexBuffer* vFormat);

		void* Lock(const IndexBuffer* vbuffer, Buffer::Locking mode);
		void UnLock(const IndexBuffer* vbBuffer);

		void Update(const IndexBuffer* vbuffer);
		static void UpdateAll(const IndexBuffer* vbuffer);

		//1D Texture
		void Bind(const Texture1D* vFormat);
		static void BindAll(const Texture1D* vformat);
		void Unbind(const Texture1D* vFormat);
		static void UnBindAll(const Texture1D* vFormat);

		void Enable(const Texture1D* vFormat);
		void Disable(const Texture1D* vFormat);

		void* Lock(const Texture1D* vbuffer, Buffer::Locking mode);
		void UnLock(const Texture1D* vbBuffer);

		void Update(const Texture1D* vbuffer);
		static void UpdateAll(const Texture1D* vbuffer);

		//2D Texture
		void Bind(const Texture2D* vFormat);
		static void BindAll(const Texture2D* vformat);
		void Unbind(const Texture2D* vFormat);
		static void UnBindAll(const Texture2D* vFormat);

		void Enable(const Texture2D* vFormat);
		void Disable(const Texture2D* vFormat);

		void* Lock(const Texture2D* vbuffer, Buffer::Locking mode);
		void UnLock(const Texture2D* vbBuffer);

		void Update(const Texture2D* vbuffer);
		static void UpdateAll(const Texture2D* vbuffer);

		//3d Texture
		void Bind(const Texture3D* vFormat);
		static void BindAll(const Texture3D* vformat);
		void Unbind(const Texture3D* vFormat);
		static void UnBindAll(const Texture3D* vFormat);

		void Enable(const Texture3D* vFormat);
		void Disable(const Texture3D* vFormat);

		void* Lock(const Texture3D* vbuffer, Buffer::Locking mode);
		void UnLock(const Texture3D* vbBuffer);

		void Update(const Texture3D* vbuffer);
		static void UpdateAll(const Texture3D* vbuffer);

		//Texture Cube
		void Bind(const TextureCube* vFormat);
		static void BindAll(const TextureCube* vformat);
		void Unbind(const TextureCube* vFormat);
		static void UnBindAll(const TextureCube* vFormat);

		void Enable(const TextureCube* vFormat);
		void Disable(const TextureCube* vFormat);

		void* Lock(const TextureCube* vbuffer, Buffer::Locking mode);
		void UnLock(const TextureCube* vbBuffer);

		void Update(const TextureCube* vbuffer);
		static void UpdateAll(const TextureCube* vbuffer);

		//Render Target
		void Bind(const RenderTarget* vFormat);
		static void BindAll(const RenderTarget* vformat);
		void Unbind(const RenderTarget* vFormat);
		static void UnBindAll(const RenderTarget* vFormat);

		void Enable(const RenderTarget* vFormat);
		void Disable(const RenderTarget* vFormat);

		void* Lock(const RenderTarget* vbuffer, Buffer::Locking mode);
		void UnLock(const RenderTarget* vbBuffer);

		void Update(const RenderTarget* vbuffer);
		static void UpdateAll(const RenderTarget* vbuffer);

		//Vertex Shader
		void Bind(const VertexShader* vFormat);
		static void BindAll(const VertexShader* vformat);
		void Unbind(const VertexShader* vFormat);
		static void UnBindAll(const VertexShader* vFormat);

		void Enable(const VertexShader* vFormat);
		void Disable(const VertexShader* vFormat);

		void* Lock(const VertexShader* vbuffer, Buffer::Locking mode);
		void UnLock(const VertexShader* vbBuffer);

		void Update(const VertexShader* vbuffer);
		static void UpdateAll(const VertexShader* vbuffer);

		//Pixel Shader
		void Bind(const PixelShader* vFormat);
		static void BindAll(const PixelShader* vformat);
		void Unbind(const PixelShader* vFormat);
		static void UnBindAll(const PixelShader* vFormat);

		void Enable(const PixelShader* vFormat);
		void Disable(const PixelShader* vFormat);

		void* Lock(const PixelShader* vbuffer, Buffer::Locking mode);
		void UnLock(const PixelShader* vbBuffer);

		void Update(const PixelShader* vbuffer);
		static void UpdateAll(const PixelShader* vbuffer);

		inline const AlphaState* GetAlphaState() const;
		inline const CullState* GetCullState() const;
		inline const DepthState* GetDepthState() const;
		inline const OffsetState* GetOffsetState() const;
		inline const StencilState* GetStencilState() const;
		inline const WireState* GetWireState() const;

		inline void SetCamera(Camera* camera);
		inline Camera* GetCamera();
		inline const Camera* GetCamera() const;
		inline const HMatrix& GetViewMatrix() const;
		inline const HMatrix& GetProjectionMatrix() const;
		inline const HMatrix& GetPostProjectionMatrix() const;

		bool GetPickRay(int x, int y, APoint& origin, AVector& direction) const;

		inline void SetClearColor(const Float4& color);
		inline const Float4& GetClearColor() const;
		inline void SetClearDepth(float clearDepth);
		inline float GetClearDepth() const;

		inline void SetClearStencil(unsigned int clearStencil);
		inline unsigned int GetClearStencil()const;

		inline void GetColorMask(bool& allowRed, bool& allowGreen, bool& allowBlue, bool& allowAlpha)const;

		inline void SetOverrideAlphaState(const AlphaState* alphaState);
		inline void SetOverrideCullState(const CullState* cullState);
		inline void SetOverrideDepthState(const DepthState* depthState);
		inline void SetOverrideOffsetState(const OffsetState* offsetState);
		inline void SetOverrideStencilState(const StencilState* stencilState);
		inline void SetOverrideWireState(const WireState* wireState);
		inline const AlphaState* GetOverrideAlphaState() const;
		inline const CullState* GetOverrideCullState() const;
		inline const DepthState* GetOverrideDepthState() const;
		inline const OffsetState* GetOverrideOffsetState() const;
		inline const StencilState* GetOverrideStencilState() const;
		inline const WireState* GetOverrideWireState() const;

		inline void SetReverseCullOrder(bool reverseCullOrder);
		inline bool GetReverseCullOrder() const;


		// The entry point to drawing the visible set of a scene graph.
		void Draw(const VisibleSet& visibleSet, GlobalEffect* globalEffect = 0);

		// The entry points for drawing a single object.
		void Draw(const Visual* visual);
		void Draw(const Visual* visual, const VisualEffectInstance* instance);
	protected:
		void DestroyAllVertexFormats();
		void DestroyAllVertexBuffers();
		void DestroyAllIndexBuffers();
		void DestroyAllTexture1Ds();
		void DestroyAllTexture2Ds();
		void DestroyAllTexture3Ds();
		void DestroyAllTextureCubes();
		void DestroyAllRenderTargets();
		void DestroyAllVertexShaders();
		void DestroyAllPixelShaders();

		int mWidth;
		int mHeight;

		Texture::Format mColorFormat;
		Texture::Format mDepthStencilFormat;
		int mNumMultisamples;

		AlphaState* mDefaultAlphaState;
		CullState* mDefaultCullState;
		DepthState* mDefaultDepthState;
		OffsetState* mDefaultOffsetState;
		StencilState* mDefaultStencilState;
		WireState* mDefaultWireState;
		const AlphaState* mAlphaState;
		const CullState* mCullState;
		const DepthState* mDepthState;
		const OffsetState* mOffsetState;
		const StencilState* mStencilState;
		const WireState* mWireState;
		bool mReverseCullOrder;

		const AlphaState* mOverrideAlphaState;
		const CullState* mOverrideCullState;
		const DepthState* mOverrideDepthState;
		const OffsetState* mOverrideOffsetState;
		const StencilState* mOvverrideStencilState;
		const WireState* mOverrideWireState;

		Camera* mCamera;
		Float4 mClearColor;
		float mClearDepth;
		unsigned int mClearStencil;

		bool mAllowRed, mAllowGreen, mAllowBlue, mAllowAlpha;

		static Mutex msMutex;
		typedef std::set<Renderer*> RendererSet;
		static RendererSet msRenderers;

		// The main entry point to drawing in the derived-class renderers.
		//dependence in Device
		//Same as DrawPrimitive in WM5
		//Call Sequence 
		//DrawScene()				(etc.Draw(VisibleSet)) 
		//->DrawGeometry(Geometry)  (etc.Draw(Visiable))
		//->ApplyEffect()			(etc.Draw(Effect))
		//-> DrawElements();		(etc.DrawPrimitive(Visiable))
		virtual void DrawPrimitive(const Visual* visual) = 0;
	public:
		virtual void ClearBackBuffer() = 0 ;
		virtual void ClearDepthBuffer() = 0;
		virtual void ClearStencilBuffer() = 0;
		virtual void ClearBuffers() = 0;
		virtual void ClearBackBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearDepthBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearStencilBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearBuffers(int x, int y, int w, int h) = 0;
		virtual void DisplayBackBuffer() = 0;

		RendererData* mData;

		Renderer(RendererData* data,int width,int height);
		// For render target access to allow creation of color/depth textures.
		inline bool InTexture2DMap(const Texture2D* texture);
		void SetColorMask(bool allowRed, bool allowGreen,
			bool allowBlue, bool allowAlpha);
	};
	
}


////基于外部定点列表的多边形
//extern void LoadIdentity();
//
//class Poly4DV1
//{
//public:
//  int state;
//  int attr;
//  int color;
//  Point4D* vlist;
//  //save the index
//  int vert[3];
//  Poly4DV1(){}
//};
//class PolyF4DV1: public Object
//{
//public:
//  int state;
//  int attr;
//  int color;
//  Point4D vlist[3];
//  Point4D tvlist[3];
//  PolyF4DV1* next;
//  PolyF4DV1* prev;
//};
//
//class SpotLight
//{
//  //Light Attenuated
//  float alpha = 1;
//
//  //P是光源，V是被照亮的定点
//  //float beta = 1 / (c0+c1*abs(V-P)+c2*abs(V-P)*(V-P));
//};
//
//class Object4DV1:public Object
//{
//public:
//  Object4DV1()
//  {
//  }
//  int id;
//  char name[64];
//  int state;
//  int attr;
//  float avg_radius;
//  float max_ratius;
//  Point4D world_pos;
//
//  Point4D dir;
//  Vector4D ux, uy, uz;
//  int num_vertices;
//  Point4D vlist_local[OBJECT4DV1_MAX_VERTICES];
//  Point4D vlist_trans[OBJECT4DV1_MAX_VERTICES];
//
//  int num_polys;
//  Poly4DV1 plist[OBJECT4DV1_MAX_POLYS];
//  //const Rtti& GetRttiType()const;
//  // Object* GetObjectByName(const std::string& name);
//  // void GetAllObjectsByName(const std::string& name, std::vector<Object*>& objects);
//  ~Object4DV1()
//  {
//
//  }
//};
//class Phong:public Object
//{
//  //
//public:
//  Phong(){}
//  int id;
//  char name[64];
//  int state;
//  int attr;
//  float avg_radius;
//  float max_ratius;
//  Point4D world_pos;
//
//  Point4D dir;
//  Vector4D ux, uy, uz;
//  int num_vertices;
//  Point4D vlist_local[OBJECT4DV1_MAX_VERTICES];
//  Point4D vlist_trans[OBJECT4DV1_MAX_VERTICES];
//
//  int num_polys;
//  Poly4DV1 plist[OBJECT4DV1_MAX_POLYS];
//  ~Phong()
//  {
//  }
//};
//
//
//class RenderList
//{
//public:
//  int state;
//  int attr;
//  vector<PolyF4DV1*> polyPoint_vector;
//  PolyF4DV1* poly_ptrs[RENDERLIST4DV1_MAX_POLYS];
//
//  PolyF4DV1 poly_data[RENDERLIST4DV1_MAX_POLYS];
//
//  int num_polys;
//public:
//  int Insert_PolyF4DV1_RenderList(PolyF4DV1 & poly);
//  RenderList() :polyPoint_vector(RENDERLIST4DV1_MAX_POLYS){}
//  inline void Reset(){ num_polys = 0; }
//};
//


//extern DWORD Get_Clock(void);
//extern DWORD Start_Clock(void);
//extern DWORD Wait_Clock(DWORD count);
//
//
//
//extern int Collision_Test(int x1, int y1, int w1, int h1,
//  int x2, int y2, int w2, int h2);
//
//extern int Color_Scan(int x1, int y1, int x2, int y2, UCHAR scan_start, UCHAR scan_end, UCHAR* scan_buffer, int scan_lpitch);
//
//extern int Color_Scan16(int x1, int y1, int x2, int y2, USHORT sca_start, USHORT scan_end, UCHAR* scan_buffer, int scan_lpitch);
//
////Graphics function
//
//
//extern int Load_Object_PLG(Object4DV1* obj, char* filename, Vector4D& scale, Vector4D& pos, Vector4D& rot);
//
////extern void Translate_Object(Object* obj, Vector4D* vt);
////extern void Scale_Object(Object* object, Vector4D* vs);
//extern void Build_XYZ_Rotation__Matrix4X4();  //will be wrote in Constructure
//extern void TransformRendList(RenderList& rendlist, Matrix4X4& mt, int select = TRANSFORM_LOCAL_ONLY);
//extern void Rotate_XYZ_Object();
//extern void RotateByAix(int x, int y, int z, float angle);
//extern void ClearBuffer(HWND& hwnd, HDC& hdc, HBRUSH& hbrush, PAINTSTRUCT& ps,float color[4]);
//
//extern void NDC2DC(RenderList& rendlist, int width, int height, float pr, float pl, float pb, float pt, float pf, float pn);
//extern void NDC2DC(Object* object, int width, int height, float pr, float pl, float pb, float pt, float pf, float pn);
//
//extern void Translate(Vector3D direction, float distance);
//extern void pix(void* render, int x, int y, int color);
//extern void rect(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
//extern void fill(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
//extern void linerect(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps, int x, int y, int width, int height, COLORREF colorR, COLORREF colorG, COLORREF colorB);
////extern void triangle(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
//extern void lineBresenham(void* p, int x0, int y0, int x1, int y1, int Color);
//extern void ellipse(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
//extern void DrawContent(HWND& hWnd, HDC& hdc, HBRUSH& NewBrush, PAINTSTRUCT& ps);
//
//extern void ObjectToWorld(Object* obj, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
//
//extern LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//extern int ClipLine(int& x1, int& y1, int& x2, int& y2);
//extern int DrawLine(int x0, int y0, int x1, int y1, int color, void* vb_start);
//extern int DrawClipLine(int x0, int y0, int x1, int y1, int color, void* dest_buffer);
//
//extern USHORT(*RGB16Bit)(int r, int g, int b);
//extern USHORT RGB16BIT565(int r, int g, int b);
//extern USHORT RGB16BIT555(int r, int g, int b);
//
//extern void Model_To_WorldRendlist(RenderList&, Point3D&, int coord_select = TRANSFORM_LOCAL_ONLY);
//extern void Model_To_WorldObject(Object4DV1& object);
#if _DX
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


#endif
