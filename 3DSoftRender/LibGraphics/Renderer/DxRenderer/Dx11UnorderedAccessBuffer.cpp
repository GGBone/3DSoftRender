#include "Graphics\GraphicsPCH.h"
#include "Dx11UnorderedAccessBuffer.h"

Hikari::UnorderedAccessBufferDX11::UnorderedAccessBufferDX11(ID3D11Device * pDevice, uint8_t bindFlags, const void * data, uint32_t count, uint16_t stride, bool AppendFlag)
	: m_pDevice(pDevice),
	m_uiStride(stride),
	m_uiCount(count),
	m_BindFlags(bindFlags),
	m_bIsDirty(false)
{

	//Dynamic buffer cannot be uav

	uint32_t numBytes = m_uiCount * m_uiStride;
	//Initialize data
	if (data)
	{
		m_Data.assign((uint8_t*)data, (uint8_t*)data + numBytes);
	}
	else
	{
		m_Data.reserve(numBytes);
	}
	D3D11_BUFFER_DESC bufferDesc = {};

	bufferDesc.ByteWidth = numBytes;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bufferDesc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = m_uiStride;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = (void*)m_Data.data();
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	if (FAILED(m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pBuffer)))
	{
		ReportError("Failed to create read/write buffer.");
		return;
	}

	if ((bufferDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE) != 0)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = m_uiCount;

		if (FAILED(m_pDevice->CreateShaderResourceView(m_pBuffer, &srvDesc, &m_pSRV)))
		{
			ReportError("Failed to create shader resource view.");
			return;
		}
	}

	if ((bufferDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS) != 0)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = m_uiCount;
		uavDesc.Buffer.Flags = 0;
		if (FAILED(m_pDevice->CreateUnorderedAccessView(m_pBuffer, &uavDesc, &m_pUAV)))
		{
			ReportError("Failed to create shader resource view.");
			return;
		}
	}
	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}

Hikari::UnorderedAccessBufferDX11::~UnorderedAccessBufferDX11()
{
	m_pBuffer->Release();
	m_pSRV->Release();
	m_pUAV->Release();
	m_Data.erase(m_Data.begin(), m_Data.end());
}

bool Hikari::UnorderedAccessBufferDX11::Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType,...)
{
	ShaderParameter::GPURW gpuRW;
	va_list arguments;

	/* Initializing arguments to store all values after num */
	va_start(arguments, 1);
	/* Sum all the inputs; we still rely on the function caller to tell us how
	* many there are */
	for (int x = 0; x < 1; x++)
	{
		gpuRW = va_arg(arguments, ShaderParameter::GPURW);
	}
	va_end(arguments);



	return false;
}

void Hikari::UnorderedAccessBufferDX11::UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
}

unsigned int Hikari::UnorderedAccessBufferDX11::GetElementCount() const
{
	return m_uiCount;
}

void Hikari::UnorderedAccessBufferDX11::Copy(std::shared_ptr<UnorderedAccessBufferDX11> other)
{
}
void Hikari::UnorderedAccessBufferDX11::SetData(void * data, size_t elementSize, size_t offset, size_t numElements)
{
}
void Hikari::UnorderedAccessBufferDX11::Commit()
{
}
void Hikari::UnorderedAccessBufferDX11::Clear()
{
}

UINT Hikari::UnorderedAccessBufferDX11::GetStride() const
{
	return m_uiStride;
}

ID3D11UnorderedAccessView * Hikari::UnorderedAccessBufferDX11::GetUnorderedAccessView() const
{
	return m_pUAV;
}

ID3D11ShaderResourceView * Hikari::UnorderedAccessBufferDX11::GetShaderResourceView() const
{
	return m_pSRV;
}
