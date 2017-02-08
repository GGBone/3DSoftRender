#include "GraphicsPCH.h"
#include "Buffer.h"
using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, Buffer);
IMPLEMENT_DEFAULT_NAMES(Object, Buffer);

Hikari::Buffer::Buffer(int numElements, int elementSize, Usage usage)
	:mNumElements(numElements),
	mElementSize(elementSize),
	mUsage(usage),
	mNumBytes(numElements * elementSize)
{
	mData = new char[mNumBytes];
}

Hikari::Buffer::~Buffer()
{
}

