#include "GraphicsPCH.h"
#include "Dx11StructureBuffer.h"

using namespace Hikari;


StructuredBufferDX11::StructuredBufferDX11(ID3D11Device* pDevice, const void* data, size_t count, UINT stride,
                                           ShaderParameter::ShaderInputParameter inputParameter)
	: m_pDevice(pDevice),
	  m_uiStride(stride),
	  m_uiCount(static_cast<UINT>(count))
{
	m_shader_input_param_ = inputParameter;
	m_bDynamic = static_cast<int>(m_shader_input_param_.m_cpuAccess) == 2;
	m_bUAV = (static_cast<int>(GPUAccess::Write) & static_cast<int>(m_shader_input_param_.m_gpuAccess)) && !m_bDynamic;
	m_bSRV = !(static_cast<int>(inputParameter.m_gpuAccess) == static_cast<int>(GPUAccess::Write));
	const size_t numBytes = m_uiCount * m_uiStride;

	if (data)
	{
		m_Data.assign((uint8_t*)data, (uint8_t*)data + numBytes);
	}
	m_data_ = new byte[m_uiStride * count];
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = (UINT)numBytes;
	bufferDesc.BindFlags = 0;

	bufferDesc.MiscFlags = 0;
	if (m_bSRV)
	{
		bufferDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
		bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	}

	if (m_bUAV)
	{
		bufferDesc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	}

	switch (inputParameter.m_cpuAccess)
	{
	case CPUAccess::Read:
		bufferDesc.Usage = D3D11_USAGE_STAGING;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		bufferDesc.BindFlags = 0;
		break;
	case CPUAccess::Write:
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		break;
	case CPUAccess::ReadWrite:
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		bufferDesc.Usage = D3D11_USAGE_STAGING;
		bufferDesc.BindFlags = 0;
		break;
	case CPUAccess::None:
		//pure GPU resource
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;

		break;
	default:
		break;
	}

	bufferDesc.StructureByteStride = m_uiStride;

	if (m_Data.size() == 0)
	{
		if(bufferDesc.BindFlags == 0)
		{
			m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pStage);
		}
		m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pBuffer);
	}
	else
	{
		D3D11_SUBRESOURCE_DATA subResourceData;
		subResourceData.pSysMem = (void*)m_Data.data();
		subResourceData.SysMemPitch = 0;
		subResourceData.SysMemSlicePitch = 0;
		m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pBuffer);
	}

	if ((bufferDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

		srvDesc.Format = DXGI_FORMAT_UNKNOWN;

		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = m_uiCount;

		m_pDevice->CreateShaderResourceView(m_pBuffer, &srvDesc, &m_pSRV);
	}

	if ((bufferDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS))
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
		switch (inputParameter.m_appendFlag)
		{
		case ShaderParameterDx11::AppendFlag::COUNTER:
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
			break;
		case ShaderParameterDx11::AppendFlag::APPEND:
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;
			break;
		default:
			uavDesc.Buffer.Flags = 0;
			break;
		}
		//Will be refine
		if (!m_bSRV && inputParameter.m_format == ShaderParameterDx11::Format::R32_SINT)
			uavDesc.Format = DXGI_FORMAT_R32_SINT;
		else
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;

		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = m_uiCount;

		m_pDevice->CreateUnorderedAccessView(m_pBuffer, &uavDesc, &m_pUAV);
	}
	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}


StructuredBufferDX11::~StructuredBufferDX11()
= default;

void StructuredBufferDX11::bind(unsigned int ID, Shader::ShaderType shaderType)
{
	if (m_bIsDirty)
	{
		Commit();
		m_bIsDirty = false;
	}
	assert(m_shader_input_param_.m_parameterType == ShaderParameterDx11::ShaderInputType::StructuredBuffer);
	if ((static_cast<int>(GPUAccess::Read) == static_cast<int>(m_shader_input_param_.m_gpuAccess)) != 0 && m_pSRV)
	{
		ID3D11ShaderResourceView* srv[] = {m_pSRV};

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
			{
				m_pDeviceContext->CSSetShaderResources(ID, 1, srv);
			}
			break;
		}
	}
	if ((static_cast<int>(GPUAccess::Write) & static_cast<int>(m_shader_input_param_.m_gpuAccess)) != 0 && m_pUAV)
	{
		ID3D11UnorderedAccessView* uav[] = {m_pUAV};
		switch (shaderType)
		{
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetUnorderedAccessViews(ID, 1, uav, nullptr);
			break;
		default:
			assert(0);
			break;
		}
	}
}

void StructuredBufferDX11::unbind(unsigned int ID, Shader::ShaderType shaderType)
{
	ID3D11UnorderedAccessView* uav[] = {nullptr};
	ID3D11ShaderResourceView* srv[] = {nullptr};

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
	default:
		assert(0);
	}


	switch (shaderType)
	{
	case Shader::ComputeShader:
		m_pDeviceContext->CSSetUnorderedAccessViews(ID, 1, uav, nullptr);
		break;
	}
}

unsigned int StructuredBufferDX11::get_element_count() const
{
	return m_uiCount;
}


void StructuredBufferDX11::Clear()
{
	if (m_pUAV)
	{
		UINT clearColor[4] = {0, 0, 0, 0};
		m_pDeviceContext->ClearUnorderedAccessViewUint(m_pUAV, clearColor);
	}
}

UINT StructuredBufferDX11::GetStride() const
{
	return m_uiStride;
}

ID3D11UnorderedAccessView* StructuredBufferDX11::GetUnorderedAccessView() const
{
	return m_pUAV;
}

void StructuredBufferDX11::copy(std::shared_ptr<BufferBase> other)
{
	std::shared_ptr<StructuredBufferDX11> srcBuffer = std::dynamic_pointer_cast<StructuredBufferDX11>(other);
	if(srcBuffer.get() == nullptr)
	{
		if (m_pStage == nullptr)
			return;
		m_pDeviceContext->CopyResource(m_pStage, m_pBuffer);
		D3D11_MAPPED_SUBRESOURCE ms;
		HRESULT hr = m_pDeviceContext->Map(m_pStage, 0, D3D11_MAP_READ, 0, &ms);
		memcpy_s(m_data_, m_uiCount * m_uiStride, ms.pData, m_uiCount * m_uiStride);
		m_pDeviceContext->Unmap(m_pStage, 0);
		return;
	}
	if (srcBuffer->m_bIsDirty)
	{
		srcBuffer->Commit();
	}
	m_pDeviceContext->CopyResource(m_pBuffer, srcBuffer->m_pBuffer);

	if ((static_cast<int>(m_shader_input_param_.m_cpuAccess) & static_cast<int>(CPUAccess::Read)) != 0)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_READ, 0, &mappedResource);
		memcpy_s(m_Data.data(), m_Data.size(), mappedResource.pData, m_Data.size());
		m_pDeviceContext->Unmap(m_pBuffer, 0);
	}
}

void StructuredBufferDX11::SetData(const void* data, size_t elementSize, size_t offset, size_t numElements)
{
	unsigned char* first = (unsigned char*)data + (offset * elementSize);
	unsigned char* last = first + (numElements * elementSize);
	m_Data.assign(first, last);
	m_bIsDirty = true;
}

void StructuredBufferDX11::Commit()
{
	if (m_bIsDirty && m_bDynamic && m_pBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		// Copy the contents of the data buffer to the GPU.

		m_pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);


		const size_t sizeInBytes = m_Data.size();
		memcpy_s(mappedResource.pData, sizeInBytes, m_Data.data(), sizeInBytes);

		m_pDeviceContext->Unmap(m_pBuffer, 0);

		m_bIsDirty = false;
	}
}
