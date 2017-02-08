#pragma once
#include "Renderer.h"
#include "Dx11RenderData.h"
namespace Hikari
{
	class PdrVertexFormat;
	class PdrVertexBuffer;
	class PdrIndexBuffer;
	class PdrTexture1D;
	class PdrTexture2D;
	class PdrTexture3D;
	class PdrTextureCube;
	class PdrRenderTarget;
	class PdrVertexShader;
	class PdrPixelShader;
	class DirectRenderer : public Renderer
	{
		//============================================================================
		// Platform-dependent portion of the interface.
	public:
		DirectRenderData* mData;
	public:
	

		DirectRenderer(DirectRenderData* input, int width, int height, Texture::Format colorFormat, Texture::Format depthStencilFormat, int numMultisamples);
		DirectRenderer(int width, int height, int numMultisamples, HWND handle);
		~DirectRenderer();

		void SetAlphaState(const AlphaState* alphaState);
		void SetCullState(const CullState* cullState);
		void SetDepthState(const DepthState* depthState);
		void SetOffsetState(const OffsetState* offsetState);
		void SetStencilState(const StencilState* stencilState);
		void SetWireState(const WireState* wireState);

		void SetViewport(int xPosition, int yPosition, int width,
			int height);
		void GetViewport(int& xPosition, int& yPosition, int& width,
			int& height) const;
		void SetDepthRange(float zMin, float zMax);
		void GetDepthRange(float& zMin, float& zMax) const;
		void Resize(int width, int height);

		// Support for clearing the color, depth, and stencil buffers.
		void ClearColorBuffer();
		void ClearDepthBuffer();
		void ClearStencilBuffer();
		void ClearBuffers();
		void ClearColorBuffer(int x, int y, int w, int h);
		void ClearDepthBuffer(int x, int y, int w, int h);
		void ClearStencilBuffer(int x, int y, int w, int h);
		void ClearBuffers(int x, int y, int w, int h);
		void DisplayColorBuffer();

		void SetColorMask(bool allowRed, bool allowGreen,
			bool allowBlue, bool allowAlpha);


		PdrVertexFormat* GetResource(const VertexFormat* vformat);
		PdrVertexBuffer* GetResource(const VertexBuffer* vbuffer);
		PdrIndexBuffer* GetResource(const IndexBuffer* ibuffer);
		PdrTexture1D* GetResource(const Texture1D* texture);
		PdrTexture2D* GetResource(const Texture2D* texture);
		PdrTexture3D* GetResource(const Texture3D* texture);
		PdrTextureCube* GetResource(const TextureCube* texture);
		PdrRenderTarget* GetResource(const RenderTarget* renderTarget);
		PdrVertexShader* GetResource(const VertexShader* vshader);
		PdrPixelShader* GetResource(const PixelShader* pshader);

		

		bool PreDraw();
		void PostDraw();


		void Draw(const unsigned char* screenBuffer, bool reflectY = false);
		void DrawPrimitive(const Visual* visual);
		// The entry point for drawing 2D text.
		void Draw(int x, int y, const Float4& color,
			const std::string& message);

	private:
		typedef std::map<const VertexFormat*, PdrVertexFormat*> VertexFormatMap;
		typedef std::map<const VertexBuffer*, PdrVertexBuffer*> VertexBufferMap;
		typedef std::map<const IndexBuffer*, PdrIndexBuffer*> IndexBufferMap;
		typedef std::map<const Texture1D*, PdrTexture1D*> Texture1DMap;
		typedef std::map<const Texture2D*, PdrTexture2D*> Texture2DMap;
		typedef std::map<const Texture3D*, PdrTexture3D*> Texture3DMap;

		typedef std::map<const TextureCube*, PdrTextureCube*> TextureCubeMap;
		typedef std::map<const RenderTarget*, PdrTextureCube*> RenderTargetMap;
		typedef std::map<const VertexShader*, PdrVertexShader*> VertexShaderMap;
		typedef std::map<const PixelShader*, PdrPixelShader*> PixelShaderMap;

		VertexFormatMap mVertexFormats;
		VertexBufferMap mVertexBuffers;
		IndexBufferMap mIndexBuffers;
		Texture1DMap mTexture1Ds;
		Texture2DMap mTexture2Ds;
		Texture3DMap mTexture3Ds;

		TextureCubeMap mTextureCubeMaps;
		RenderTargetMap mRenderTargets;
		VertexShaderMap mVertexShaders;
		PixelShaderMap mPixelShaders;
		inline void InsertInTexture2DMap(const Texture2D* texture,
			PdrTexture2D* platformTexture);
	};
}
