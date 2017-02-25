#pragma once

#include "GraphicsLIB.h"

#include "Float4.h"

#include "Buffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexBuffer.h"

#include "Visual.h"

#include <DirectXMath.h>
#include "HPoint.h"
#include "RenderData.h"
#include "VisualEffectInstance.h"
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
		HPoint pos;
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

		virtual void Bind(const VertexFormat* vFormat) = 0;

		static void BindAll(const VertexFormat* vformat);

		virtual void Unbind(const VertexFormat* vFormat) = 0;

		static void UnBindAll(const VertexFormat* vFormat);

		virtual void Enable(const VertexFormat* vFormat) = 0;

		virtual void Disable(const VertexFormat* vFormat) = 0;

		//Vertex

		virtual void Bind(const VertexBuffer* vFormat) = 0;

		static void BindAll(const VertexBuffer* vformat);

		virtual void Unbind(const VertexBuffer* vFormat) = 0;

		static void UnBindAll(const VertexBuffer* vFormat);

		virtual void Enable(const VertexBuffer* vBuffer) = 0;

		virtual void Disable(const VertexBuffer* vFormat) = 0;

		void* Lock(const VertexBuffer* vbuffer, Buffer::Locking mode);

		void UnLock(const VertexBuffer* vbBuffer);


		void Update(const VertexBuffer* vbuffer);

		static void UpdateAll(const VertexBuffer* vbuffer);

		//Index

		void Bind(const IndexBuffer* vFormat);

		static void BindAll(const IndexBuffer* vformat);

		void Unbind(const IndexBuffer* vFormat);

		static void UnBindAll(const IndexBuffer* vFormat);

		virtual void Enable(const IndexBuffer* iBuffer) = 0;

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
		//Bind will add the parameter into a the std::map<type-param,type-wrapped>
		virtual void Bind(const VertexShader* vShader);

		static void BindAll(const VertexShader* vformat);

		virtual void Unbind(const VertexShader* vFormat);

		static void UnBindAll(const VertexShader* vFormat);

		//Enable will find the vshader in the map first,if it exists,call is Enble,else new one the insert
		//in the map and call it Enable.
		virtual void Enable(const VertexShader* vShader, const ShaderParameters* vParam) = 0;



		void* Lock(const VertexShader* vbuffer, Buffer::Locking mode);

		void UnLock(const VertexShader* vbBuffer);

		void Update(const VertexShader* vbuffer);

		static void UpdateAll(const VertexShader* vbuffer);


		//Pixel Shader

		void Bind(const PixelShader* vFormat);

		static void BindAll(const PixelShader* vformat);

		void Unbind(const PixelShader* vFormat);

		static void UnBindAll(const PixelShader* vFormat);

		virtual void Enable(const PixelShader* pShader, const ShaderParameters* vParam) = 0;

		void Disable(const PixelShader* pShader);

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

		inline void swap_int(int *a, int*b)
		{
			*a ^= *b;
			*b ^= *a;
			*a ^= *b;
		}
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
		//DrawScene()               (etc.Draw(VisibleSet))
		//->DrawGeometry(Geometry)  (etc.Draw(Visiable))
		//->ApplyEffect()           (etc.Draw(Effect))
		//-> DrawElements();        (etc.DrawPrimitive(Visiable))
		virtual void DrawPrimitive(const Visual* visual) = 0;
	public:
		virtual void ClearBackBuffer() = 0;
		virtual void ClearDepthBuffer() = 0;
		virtual void ClearStencilBuffer() = 0;
		virtual void ClearBuffers() = 0;
		virtual void ClearBackBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearDepthBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearStencilBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearBuffers(int x, int y, int w, int h) = 0;
		virtual void DisplayBackBuffer() = 0;
		RendererData* mData;
		Renderer(RendererData* data);

		// For render target access to allow creation of color/depth textures.

		inline bool InTexture2DMap(const Texture2D* texture);

		void SetColorMask(bool allowRed, bool allowGreen,

			bool allowBlue, bool allowAlpha);

	};
}