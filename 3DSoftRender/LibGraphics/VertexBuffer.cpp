#include "GraphicsPCH.h"

#include "VertexBuffer.h"
#include "Renderer.h"

using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Buffer, VertexBuffer);
IMPLEMENT_DEFAULT_NAMES(Buffer, VertexBuffer);

Hikari::VertexBuffer::VertexBuffer(int numVertics, int vertexSize, Usage usage)
	:Buffer(numVertics, vertexSize, usage)
{
	
}

inline Hikari::VertexBuffer::~VertexBuffer()
{
	Renderer::UnBindAll(this);
}
