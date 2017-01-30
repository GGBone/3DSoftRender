#include "GraphicsPCH.h"
#include "Buffer.h"
using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, Buffer);
IMPLEMENT_DEFAULT_NAMES(Object, Buffer);

Buffer::Buffer()
	:mNumElements(0),
	mElementSize(0),
	mUsage(Buffer::BU_STATIC),
	mNumBytes(0),
	mData(0)
{

}

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

