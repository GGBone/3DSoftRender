#pragma once

#include "SoftRendererLIB.h"

#include "Renderer.h"

#include "Buffer.h"

#include "ColorRGBA.h"

namespace Hikari
{
	//virtualize the GPU FrameBuffer

	class SoftFrameBuffer : public Object
	{

		DECLARE_RTTI;

		DECLARE_NAMES;

	public:

		enum FormatType
		{
			FT_FORMAT_NONE,

			FT_FORMAT_RGB,

			FT_FORMAT_RGBA,

			FT_FORMAT_DEPTH

		};
		enum DepthType
		{
			DT_DEPTH_NONE,

			DT_DEPTH_16,

			DT_DEPTH_24,

			DT_DEPTH_32
		};
		enum StencilType
		{
			ST_STENCIL_NONE,
			ST_STENCIL_8
		};

		enum BufferingType
		{
			BT_BUFFERED_SINGLE,
			BT_BUFFERED_DOUBLE
		};
		enum MultisamplingType
		{
			MT_SAMPLING_NONE,

			MT_SAMPLING_2,

			MT_SAMPLING_4

		};

		SoftFrameBuffer(int width, int height, FormatType format = FT_FORMAT_RGB, DepthType depthType = DT_DEPTH_24, StencilType stencilType = ST_STENCIL_8, BufferingType buffType = BT_BUFFERED_DOUBLE,

			MultisamplingType multiSampling = MT_SAMPLING_NONE);

		virtual ~SoftFrameBuffer();

		virtual void Enable();

		virtual void Disable();

		virtual void CopyToTexture(bool fillImage);

		inline int GetWidth()const;

		inline int GetHeight()const;

		inline int GetQuantity()const;

		inline void SetColorBuffer(Buffer* colorBuffer);

		inline Buffer* GetColorBuffer()const;

		inline ColorRGBA* GetColorBufferRGBA()const;

		inline unsigned int GetMaxDepthValue()const;

		inline Buffer* GetDepthBuffer()const;

		inline void SetDepthBuffer(Buffer* buffer);

		inline unsigned int GetMaxStencilValue()const;

		Buffer* GetStencilBuffer()const;
	protected:

		int mWidth;

		int mHeight;

		int mQuantity;
		Buffer* mColorBuffer;
		Buffer* mBackColorBuffer;
		ColorRGBA* mBufferColor;
		//The depth buffer(16bit,24bit,32bit) all stored in 32 integer to avoid data loss
		unsigned int mMaxDepthValue;

		Buffer* mDepthBuffer;

		//8 bit stencil buffer.Stored as 32-bit integers to avoid

		//performance loss due to masking and shifting

		unsigned int mMaxStencilValue;

		Buffer* mStencilBuffer;

		//The colorBuffer for the main framebuffer might have been passed to

		//this object.If so,the caller is responsible for deleting it.If not,

		//this object allocated it and must delete it.

		bool mColorBufferOwner;

		static SoftFrameBuffer* Create(Renderer* pkRenderer);

		static void Destroy(SoftFrameBuffer* pkBuffer);

		friend class SoftRenderer;

		friend class WinSoftRenderer;

	private:

		HDC mWindowDC, mMemoryDC;

		HBITMAP mHBitMap;

		HWND mHwnd;

		//This cannot be write by renderer directly,It will

		//be update by (Buffer*)mColorBuffer

		//unsigned int* mColorBuffer;

		bool ScreenShot();

	};

#include "SoftFrameBuffer.inl"

}