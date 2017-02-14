#include "SoftFrameBuffer.h"
using namespace Hikari;

inline int SoftFrameBuffer::GetWidth()const
{
	return mWidth;
}

inline int Hikari::SoftFrameBuffer::GetHeight() const
{
	return mHeight;
}

inline int Hikari::SoftFrameBuffer::GetQuantity() const
{
	
	return mQuantity;
}

inline void Hikari::SoftFrameBuffer::SetColorBuffer(Buffer * colorBuffer)
{
	mColorBuffer = colorBuffer;
}

inline Buffer* Hikari::SoftFrameBuffer::GetColorBuffer() const
{
	return mColorBuffer;
}

inline ColorRGBA * Hikari::SoftFrameBuffer::GetColorBufferRGBA() const
{
	return mBufferColor;
}

inline unsigned int Hikari::SoftFrameBuffer::GetMaxDepthValue() const
{
	return mMaxDepthValue;
}

inline Buffer * Hikari::SoftFrameBuffer::GetDepthBuffer() const
{
	return mDepthBuffer;
}

inline void Hikari::SoftFrameBuffer::SetDepthBuffer(Buffer * buffer)
{
	mDepthBuffer = buffer;
}

inline unsigned int Hikari::SoftFrameBuffer::GetMaxStencilValue() const
{
	return mMaxStencilValue;
}

inline Buffer * Hikari::SoftFrameBuffer::GetStencilBuffer() const
{
	return mStencilBuffer;
}


