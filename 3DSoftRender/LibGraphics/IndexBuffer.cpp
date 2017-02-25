#pragma once
#include "GraphicsPCH.h"
#include "IndexBuffer.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Buffer, IndexBuffer);
IMPLEMENT_RTTI(Hikari, Buffer, IndexBuffer);
IndexBuffer::IndexBuffer(int numVertics, int vertexSize, Usage usage)
	:Buffer(numVertics,vertexSize)
{

}

Hikari::IndexBuffer::~IndexBuffer()
{
}


