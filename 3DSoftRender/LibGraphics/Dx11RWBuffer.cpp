#include "Dx11RWBuffer.h"
using namespace Hikari;
Hikari::RWBufferDX11::RWBufferDX11(ID3D11Device * pDevice, UINT bindFlags, const void * data, size_t count, UINT stride)
	:m_pDevice(pDevice),
	m_uiStride(stride),
	m_uiCount(count),
	m_bUAV(true),
	m_pSRV(nullptr),
	m_pUAV(nullptr)
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

bool Hikari::RWBufferDX11::Bind(unsigned int ID, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
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

void Hikari::RWBufferDX11::UnBind(unsigned int ID, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
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

unsigned int Hikari::RWBufferDX11::GetElementCount() const
{
	return m_uiCount;
}

void Hikari::RWBufferDX11::Copy(RWBuffer * other)
{
	m_pDeviceContext->CopyResource(m_pStage, m_pBuffer);
	D3D11_MAPPED_SUBRESOURCE ms;
	HRESULT hr = m_pDeviceContext->Map(m_pStage, 0, D3D11_MAP_READ, 0, &ms);
	memcpy_s(m_data, m_uiCount*m_uiStride, ms.pData, m_uiCount*m_uiStride);
	m_pDeviceContext->Unmap(m_pStage, 0);
}


ID3D11UnorderedAccessView * Hikari::RWBufferDX11::GetUnorderedAccessView() const
{
	return m_pUAV;
}

void * Hikari::RWBufferDX11::GetData() const
{
	return m_data;
}

void Hikari::RWBufferDX11::Copy(Buffer * other)
{
	Copy((RWBufferDX11*)(other));
}

void Hikari::RWBufferDX11::SetData(void * data, size_t elementSize, size_t offset, size_t numElements)
{
	unsigned char* first = (unsigned char*)data + (offset * elementSize);
	unsigned char* last = first + (numElements * elementSize);
	m_Data.assign(first, last);
	m_bIsDirty = true;
}

void Hikari::RWBufferDX11::Commit()
{
	if (m_bIsDirty && m_pBuffer)
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
