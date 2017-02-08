#pragma once

#include "Renderer.h"

#include "GraphicsLib.h"

#include "SoftRenderData.h"

namespace Hikari
{
	class SoftRenderer : public Renderer
	{
		//============================================================================

		// Platform-dependent portion of the interface.
	public:

		virtual ~SoftRenderer();

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

		VertexBuffer* mVertexBuffer;

		//Input the External Setting like multisample,isFullScreen,Resolution and so on.

		SoftRenderData* mData;

	private:

		virtual void DrawPrimitive(const Visual* visual);

		void DrawPolypoint();

		void DrawPolylineDisjoint();

		void DrawPolylineContiguous();

		void DrawTriMesh();

	};

}