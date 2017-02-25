#include "SoftFrameBuffer.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Object, SoftFrameBuffer);
IMPLEMENT_RTTI(Hikari, Object, SoftFrameBuffer);
Hikari::SoftFrameBuffer::~SoftFrameBuffer()
{
}

void Hikari::SoftFrameBuffer::Enable()
{
}

void Hikari::SoftFrameBuffer::Disable()
{
}

void Hikari::SoftFrameBuffer::CopyToTexture(bool fillImage)
{
}


SoftFrameBuffer::SoftFrameBuffer(int width, int height, FormatType format, DepthType depthType, StencilType stencilType, BufferingType buffType,
	MultisamplingType multiSampling)
	:mWidth(width),
	mHeight(height)
{
	//mColorBuffer = new Buffer(mWidth*mHeight, 4, Buffer::BU_STATIC);
}