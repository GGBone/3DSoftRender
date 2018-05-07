#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11Buffer.h"
using namespace Hikari;
Hikari::BufferDX11::BufferDX11(ID3D11Device * pDevice, UINT bindFlags, const void * data, UINT count, UINT stride)
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
	bd.ByteWidth = stride * count;
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
	uavd.Buffer.NumElements = m_uiCount;
	uavd.Buffer.Flags = 0;
	hr = m_pDevice->CreateUnorderedAccessView(m_pBuffer, &uavd, &m_pUAV);
	
	//set CPUAccess for copying data from m_pBuffer
	bd.Usage = D3D11_USAGE_STAGING;
	bd.BindFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	hr = m_pDevice->CreateBuffer(&bd, 0, &m_pStage);
	m_pDevice->GetImmediateContext(&m_pDeviceContext);

	m_data = new byte[m_uiStride*count];
	memset(m_data, 0, m_uiStride * count);
}

Hikari::BufferDX11::~BufferDX11()
{
	
}

bool Hikari::BufferDX11::Bind(unsigned int ID, Shader::ShaderType shaderType, ShaderParameter::Type parameterType,...)

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

	if (m_bIsDirty)
	{
		Commit();
		m_bIsDirty = false;
	}
	assert((parameterType == ShaderParameter::Type::Buffer) || (parameterType == ShaderParameter::Type::Texture));
	if (((int)gpuRW & (int)ShaderParameter::GPURW::Read)!=0)
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
	else if (((int)gpuRW & (int)ShaderParameter::GPURW::Write))
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

void Hikari::BufferDX11::UnBind(unsigned int ID, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
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
	else if (parameterType == ShaderParameter::Type::Buffer)
	{
		switch (shaderType)
		{
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetUnorderedAccessViews(ID, 1, uav, nullptr);
			break;
		}
	}
}

unsigned int Hikari::BufferDX11::GetElementCount() const
{
	return m_uiCount;
}

void Hikari::BufferDX11::Copy(std::shared_ptr<BufferBase> other)
{
	if (!other)
	{
		Copy(std::dynamic_pointer_cast<Buffer>(other));
	}
}

void Hikari::BufferDX11::Copy(std::shared_ptr<Buffer> other)
{
	
}

void Hikari::BufferDX11::CopyBufferData()
{
	m_pDeviceContext->CopyResource(m_pStage, m_pBuffer);
	D3D11_MAPPED_SUBRESOURCE ms;
	HRESULT hr = m_pDeviceContext->Map(m_pStage, 0, D3D11_MAP_READ, 0, &ms);
	memcpy_s(m_data, m_uiCount*m_uiStride, ms.pData, m_uiCount*m_uiStride);
	m_pDeviceContext->Unmap(m_pStage, 0);
}

void Hikari::BufferDX11::Clear()
{
	if (m_pUAV)
	{
		UINT clearColor[4] = { 0, 0, 0, 0 };
		m_pDeviceContext->ClearUnorderedAccessViewUint(m_pUAV, clearColor);
	}
}


ID3D11UnorderedAccessView * Hikari::BufferDX11::GetUnorderedAccessView() const
{
	return m_pUAV;
}

void * Hikari::BufferDX11::GetData() const
{
	return m_data;
}


void Hikari::BufferDX11::SetData(void * data, size_t elementSize, size_t offset, size_t numElements)
{
	UINT* first = (UINT*)data + (offset * elementSize);
	UINT* last = first + (numElements * elementSize);
	m_Data.assign(first, last);
	m_bIsDirty = true;
}

void Hikari::BufferDX11::Commit()
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
