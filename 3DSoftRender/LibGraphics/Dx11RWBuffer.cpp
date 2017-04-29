#include "Dx11RWBuffer.h"
using namespace Hikari;
Hikari::RWBufferDX11::RWBufferDX11(ID3D11Device * pDevice, UINT bindFlags, const void * data, size_t count, UINT stride)
:m_pDevice(pDevice),
m_uiStride(stride),
m_uiCount(count)
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = stride;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	D3D11_SUBRESOURCE_DATA sd;
	if (data)
	{
		sd.pSysMem = data;
		hr = m_pDevice->CreateBuffer(&bd, &sd, &m_pBuffer);
	}
	else
	{
		hr = m_pDevice->CreateBuffer(&bd, 0, &m_pBuffer);
	}
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd, sizeof(uavd));
	if (stride == 4)
		uavd.Format = DXGI_FORMAT_R32_SINT;
	else if(stride == 2)
		uavd.Format = DXGI_FORMAT_R16_SINT;

	uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavd.Buffer.FirstElement = 0;
	uavd.Buffer.NumElements = 1;
	uavd.Buffer.Flags = 0;
	hr = m_pDevice->CreateUnorderedAccessView(m_pBuffer, &uavd, &m_pUAV);
	
	bd.Usage = D3D11_USAGE_STAGING;
	bd.BindFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	hr = m_pDevice->CreateBuffer(&bd, 0, &m_pStage);
	m_pDevice->GetImmediateContext(&m_pDeviceContext);

	m_data = new byte[m_uiStride*count];

}

Hikari::RWBufferDX11::~RWBufferDX11()
{
	
}

bool Hikari::RWBufferDX11::Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
	return false;
}

void Hikari::RWBufferDX11::UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
}

unsigned int Hikari::RWBufferDX11::GetElementCount() const
{
	return 1;
}

void Hikari::RWBufferDX11::Copy(RWBuffer * other)
{
	m_pDeviceContext->CopyResource(m_pStage, m_pBuffer);
	D3D11_MAPPED_SUBRESOURCE ms;
	HRESULT hr = m_pDeviceContext->Map(m_pStage, 0, D3D11_MAP_READ, 0, &ms);
	m_data = ms.pData;
	m_pDeviceContext->Unmap(m_pStage, 0);
}


ID3D11UnorderedAccessView * Hikari::RWBufferDX11::GetUnorderedAccessView() const
{
	return m_pUAV;
}

void Hikari::RWBufferDX11::Copy(Buffer * other)
{
	Copy((RWBufferDX11*)(other));
}

void Hikari::RWBufferDX11::SetData(void * data, size_t elementSize, size_t offset, size_t numElements)
{
}

void Hikari::RWBufferDX11::Commit()
{
}
