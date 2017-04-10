#include "GraphicsPCH.h"
#include "Dx11ConstantBuffer.h"
using namespace Hikari;
Hikari::PdrConstantBuffer::PdrConstantBuffer(DirectRenderer * render, ConstantBuffer * constanBuffer)
{
	ID3D11Device* device = render->mData->mDevice;
	ID3D11DeviceContext* context;
	device->GetImmediateContext(&context);
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = constanBuffer->GetNumBytes();
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	
	HRESULT hr = device->CreateBuffer(&bufferDesc, nullptr, &mBuffer);


	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = context->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, constanBuffer->GetData(), constanBuffer->GetNumBytes());
	context->Unmap(mBuffer, 0);
}
