#include "GraphicsPCH.h"
#include "Dx11VertexBuffer.h"
#include "Renderer.h"
#include "Dx11RenderData.h"


Hikari::PdrVertexBuffer::PdrVertexBuffer(DirectRenderer* renderer, const VertexBuffer * vbuffer)
{
	ID3D11Device* device = renderer->mData->mDevice;
	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 6;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	VertexPos* buffer = (VertexPos*)(vbuffer->GetData());
	resourceData.pSysMem = buffer;
	HRESULT hr = device->CreateBuffer(&vertexDesc, &resourceData, &mBuffer);
	
	UINT stride = sizeof(VertexPos);
	UINT offset = 0;
	renderer->mData->mImmediateContext->IASetVertexBuffers(0, 1, &mBuffer, &stride, &offset);
}

Hikari::PdrVertexBuffer::~PdrVertexBuffer()
{
}

void Hikari::PdrVertexBuffer::Enable(Renderer * renderer, unsigned int vertexSize, unsigned int streamIndex, unsigned int offset)
{
}

void Hikari::PdrVertexBuffer::Disable(Renderer * render, unsigned int streamIndex)
{
}

void * Hikari::PdrVertexBuffer::Lock(Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::PdrVertexBuffer::Unlock()
{
}

ID3D11Buffer* const* Hikari::PdrVertexBuffer::GetVertexBuffer() const
{
	return &mBuffer;
}
