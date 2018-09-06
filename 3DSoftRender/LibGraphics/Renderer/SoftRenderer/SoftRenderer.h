#if 0
#pragma once
#include "Renderer.h"
#include "GraphicsLib.h"
#include "Visual.h"
#include "SoftRenderData.h"
#include "SoftVertexBuffer.h"
#include "SoftVertexShader.h"
#include <DirectXMath.h>
using namespace DirectX;
namespace Hikari
{
	class SoftVertexShader;

	class SoftRenderer : public Renderer
	{
		//============================================================================
		// Platform-dependent portion of the interface.
	public:
		SoftRenderData* GetRendererData();
		void IASetVertexBuffers(UINT startSlot, UINT numBuffers, Buffer** buffer, UINT stride, UINT offset);
		void VSSetConstantBuffers(UINT startSlot, UINT numBuffers, Buffer** cbuffer);
		virtual ~SoftRenderer();
		virtual void Bind(const VertexFormat* vFormat);
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
		virtual void ClearBackBuffer() = 0;
		virtual void ClearDepthBuffer();

		virtual void ClearStencilBuffer();

		virtual void ClearBuffers();

		virtual void ClearBackBuffer(int x, int y, int w, int h);

		virtual void ClearDepthBuffer(int x, int y, int w, int h);
		virtual void ClearStencilBuffer(int x, int y, int w, int h);
		virtual void ClearBuffers(int x, int y, int w, int h);

		virtual void Bind(const Buffer* vFormat);
		virtual void Unbind(const Buffer* vBuffer);
		virtual void Unbind(const VertexFormat* vFormat);

		virtual void Enable(const Buffer* vBuffer);
		virtual void Enable(const VertexFormat* vFormat);
		virtual void Enable(const VertexShader* vShader);

		virtual void Disable(const Buffer* vFormat);
		virtual void Disable(const VertexFormat* vFormat);
		virtual void Disable(const VertexShader* vShader);
	protected:
		SoftRenderer(SoftRenderData * input, int width, int height, int numMultisamples, HWND handle);
		virtual void ClearSubBackBuffer(int iXMin, int iXMax, int iYMin, int iYMax) = 0;

		virtual void SetColorBuffer(int iX, int iY, int iIndex, const ColorRGBA& rkColor) = 0;

		//Load Shader program

		//To-Be defined
		virtual void SetCullState(CullState* cullState);
		friend class SoftFrameBuffer;

		void SetRenderTarget(SoftFrameBuffer* frameBuffer);
		//VRAM
		SoftFrameBuffer mainFrameBuffer;
		//RAM
		//Shader Layout to-be continue

		//Store Vertex
		//VRAM
		Buffer** mVertexBuffer;

		//Input the External Setting like multisample,isFullScreen,Resolution and so on.

		SoftRenderData* mData;

	private:
		SoftVertexShader* mVertexShader;
		virtual void DrawPrimitive(const Visual* visual);
		void DrawPolypoint();

		void DrawPolylineDisjoint();

		void DrawPolylineContiguous();
		void DrawTriMesh();
		void RasterizePoint(XMFLOAT2 iV0, int Vcolor);
		void RasterizeEdge(XMFLOAT2 iV0, XMFLOAT2 iV1);
		void RasterizeTriangle(XMFLOAT2 iV0, XMFLOAT2 iV1, XMFLOAT2 iV2);


	};
}
#endif