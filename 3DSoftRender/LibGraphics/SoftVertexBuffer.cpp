#include "GraphicsPCH.h"
#include "SoftVertexBuffer.h"
using namespace Hikari;
Hikari::SoftVertexBuffer::SoftVertexBuffer(SoftRenderer* renderer, const VertexBuffer * vbuffer)
{
	int numElement = vbuffer->GetNumElements();
	int bufferSize = vbuffer->GetNumBytes();
	int elementSize = vbuffer->GetElementSize();
	mBuffer = new Buffer(numElement, elementSize);
	mBuffer->SetData(vbuffer->GetData());
	renderer->IASetVertexBuffers(0, 1, &mBuffer, sizeof(VertexPos), 0);
}

Hikari::SoftVertexBuffer::~SoftVertexBuffer()
{
}

void Hikari::SoftVertexBuffer::Enable(SoftRenderer* renderer, unsigned int index, unsigned int offset)
{
	renderer->IASetVertexBuffers(0, 1, &mBuffer, sizeof(VertexPos), offset);
}

void Hikari::SoftVertexBuffer::Disable(SoftRenderer* renderer, unsigned int index)
{
	delete mBuffer;
	//renderer->mVertexBuffer->Release()
}
