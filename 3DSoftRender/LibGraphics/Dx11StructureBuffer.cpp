#include "GraphicsPCH.h"
#include "Dx11StructureBuffer.h"

using namespace Hikari;
Hikari::StructuredBufferDX11::StructuredBufferDX11(ID3D11Device * pDevice, UINT bindFlags, const void * data, size_t count, UINT stride, CPUAccess cpuAccess, bool bUAV)
	:m_pDevice(pDevice),
	m_uiStride(stride),
	m_uiCount((UINT)count),
	m_BindFlags(bindFlags),
	m_bIsDirty(false),
	m_CPUAccess(cpuAccess)
{
	m_bDynamic = (int)m_CPUAccess != 0;
	m_bUAV = bUAV && !m_bDynamic;
	size_t numBytes = m_uiCount * m_uiStride;

	if (data)
	{
		m_Data.assign((uint8_t*)data, (uint8_t*)data + numBytes);
	}
	else
		m_Data.reserve(numBytes);

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = (UINT)numBytes;
	if (((int)m_CPUAccess & (int)CPUAccess::Read) != 0)
	{
		bufferDesc.Usage = D3D11_USAGE_STAGING;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	}
	else if ((((int)m_CPUAccess) & (int)CPUAccess::Write) != 0)
	{
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	}
	else
	{
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		if (m_bUAV)
		{
			bufferDesc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
		}
	}
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = m_uiSlot;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = (void*)m_Data.data();
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pBuffer);

	if ((bufferDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = m_uiCount;
		
		m_pDevice->CreateShaderResourceView(m_pBuffer, &srvDesc, &m_pSRV);
	}

	if ((bufferDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS) != 0)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = m_uiCount;
		uavDesc.Buffer.Flags = 0;

		m_pDevice->CreateUnorderedAccessView(m_pBuffer, &uavDesc, &m_pUAV);
	}
	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}

Hikari::StructuredBufferDX11::~StructuredBufferDX11()
{
}

bool Hikari::StructuredBufferDX11::Bind(unsigned int ID, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
	if (m_bIsDirty)
	{
		Commit();
		m_bIsDirty = false;
	}
	if (parameterType == ShaderParameter::Type::Buffer && m_pSRV)
	{
		ID3D11ShaderResourceView* srv[] = { m_pSRV };

		switch (shaderType)
		{
		case Shader::VertexShader:
			m_pDeviceContext->VSSetShaderResources(ID, 1, srv);
			break;
		case Shader::TessellationControlShader:
			m_pDeviceContext->HSSetShaderResources(ID, 1, srv);
			break;
		case Shader::TessellationEvaluationShader:
			m_pDeviceContext->DSSetShaderResources(ID, 1, srv);
			break;
		case Shader::GeometryShader:
			m_pDeviceContext->GSSetShaderResources(ID, 1, srv);
			break;
		case Shader::PixelShader:
			m_pDeviceContext->PSSetShaderResources(ID, 1, srv);
			break;
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetShaderResources(ID, 1, srv);
			break;
		}
	}
	else if (parameterType == ShaderParameter::Type::RWBuffer && m_pUAV)
	{
		ID3D11UnorderedAccessView* uav[] = { m_pUAV };
		switch (shaderType)
		{
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetUnorderedAccessViews(ID, 1, uav, nullptr);
			break;
		}
	}
	return true;
}

void Hikari::StructuredBufferDX11::UnBind(unsigned int ID, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
	ID3D11UnorderedAccessView* uav[] = { nullptr };
	ID3D11ShaderResourceView* srv[] = { nullptr };

	if (parameterType == ShaderParameter::Type::Buffer)
	{
		switch (shaderType)
		{
		case Shader::VertexShader:
			m_pDeviceContext->VSSetShaderResources(ID, 1, srv);
			break;
		case Shader::TessellationControlShader:
			m_pDeviceContext->HSSetShaderResources(ID, 1, srv);
			break;
		case Shader::TessellationEvaluationShader:
			m_pDeviceContext->DSSetShaderResources(ID, 1, srv);
			break;
		case Shader::GeometryShader:
			m_pDeviceContext->GSSetShaderResources(ID, 1, srv);
			break;
		case Shader::PixelShader:
			m_pDeviceContext->PSSetShaderResources(ID, 1, srv);
			break;
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetShaderResources(ID, 1, srv);
			break;
		}
	}
	else if (parameterType == ShaderParameter::Type::RWBuffer)
	{
		switch (shaderType)
		{
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetUnorderedAccessViews(ID, 1, uav, nullptr);
			break;
		}
	}
}

Buffer::BufferType StructuredBufferDX11::GetType() const
{
	return Buffer::BufferType::StructuredBuffer;
}

unsigned int Hikari::StructuredBufferDX11::GetElementCount() const
{
	return m_uiCount;
}

void Hikari::StructuredBufferDX11::Copy(StructuredBuffer * other)
{
	StructuredBufferDX11* srcBuffer = (StructuredBufferDX11*) other;
	if (srcBuffer->m_bIsDirty)
	{
		srcBuffer->Commit();
	}
	m_pDeviceContext->CopyResource(m_pBuffer, srcBuffer->m_pBuffer);

	if (((int)m_CPUAccess & (int)CPUAccess::Read) != 0)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_READ, 0, &mappedResource);
		memcpy_s(m_Data.data(), m_Data.size(), mappedResource.pData, m_Data.size());
		m_pDeviceContext->Unmap(m_pBuffer, 0);
	}
}

void Hikari::StructuredBufferDX11::Clear()
{
	if (m_pUAV)
	{
		FLOAT clearColor[4] = { 0, 0, 0, 0 };
		m_pDeviceContext->ClearUnorderedAccessViewFloat(m_pUAV, clearColor);
	}
}

ID3D11UnorderedAccessView * Hikari::StructuredBufferDX11::GetUnorderedAccessView() const
{
	return m_pUAV;
}

void Hikari::StructuredBufferDX11::Copy(Buffer * other)
{
	Copy((StructuredBuffer*)(other));
}

void Hikari::StructuredBufferDX11::SetData(void * data, size_t elementSize, size_t offset, size_t numElements)
{
	unsigned char* first = (unsigned char*)data + (offset * elementSize);
	unsigned char* last = first + (numElements * elementSize);
	m_Data.assign(first, last);
	m_bIsDirty = true;
}

void Hikari::StructuredBufferDX11::Commit()
{
	if (m_bIsDirty && m_bDynamic && m_pBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		// Copy the contents of the data buffer to the GPU.

		m_pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		

		size_t sizeInBytes = m_Data.size();
		memcpy_s(mappedResource.pData, sizeInBytes, m_Data.data(), sizeInBytes);

		m_pDeviceContext->Unmap(m_pBuffer, 0);

		m_bIsDirty = false;
	}
}
