#include "Dx11IndexBuffer.h"
using namespace Hikari;
Hikari::PdrIndexBuffer::PdrIndexBuffer(DirectRenderer * renderer, const IndexBuffer * ibuffer)
{
	ID3D11Device* device = renderer->mData->mDevice;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = ibuffer->GetNumBytes();
	desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = ibuffer->GetData();

	HRESULT hr = device->CreateBuffer(&desc, &resourceData, &mbuffer);


	renderer->mData->mImmediateContext->IASetIndexBuffer(mbuffer, DXGI_FORMAT_R32_UINT, 0);
}

Hikari::PdrIndexBuffer::~PdrIndexBuffer()
{
}

void Hikari::PdrIndexBuffer::Enable(DirectRenderer * renderer, unsigned int vertexSize, unsigned int streamIndex, unsigned int offset)
{
	renderer->mData->mImmediateContext->IASetIndexBuffer(mbuffer, DXGI_FORMAT_R32_UINT, offset);
}

ID3D11Buffer* const * Hikari::PdrIndexBuffer::GetIndexBuffer() const
{
	return &mbuffer;
}


