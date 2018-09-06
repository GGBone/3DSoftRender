#include "GraphicsPCH.h"
#include "Dx11Buffer.h"
#include "Resource/CPUAccess.h"
using namespace Hikari;

BufferDX11::BufferDX11(ID3D11Device* pDevice, const void* data, UINT count, UINT stride,
                       ShaderParameter::ShaderInputParameter shader_param)
	: m_pDevice(pDevice),
	  m_pSRV(nullptr),
	  m_pUAV(nullptr),
	  m_shader_input_parameter_(shader_param),
	  m_uiStride(stride),
	  m_BindFlags(0),
	  m_uiCount(count),
	  m_uiSlot(0),
	  m_bUAV(true)
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
		hr = m_pDevice->CreateBuffer(&bd, nullptr, &m_pBuffer);
	}
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd, sizeof(uavd));
	if (stride == 4)
		uavd.Format = DXGI_FORMAT_R32_SINT;
	else if (stride == 2)
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
	hr = m_pDevice->CreateBuffer(&bd, nullptr, &m_pStage);
	m_pDevice->GetImmediateContext(&m_pDeviceContext);

	m_data_ = new byte[m_uiStride * count];
	memset(m_data_, 0, m_uiStride * count);
}

BufferDX11::~BufferDX11() = default;

bool BufferDX11::bind(unsigned int id, Shader::ShaderType shaderType)

{
	const auto gpu_rw = m_shader_input_parameter_.m_gpuAccess;
	const auto parameter_type = m_shader_input_parameter_.m_parameterType;
	if (m_bIsDirty)
	{
		commit();
		m_bIsDirty = false;
	}
	assert((parameter_type == ShaderParameterDx11::ShaderInputType::Buffer) || (parameter_type == ShaderParameterDx11::
		ShaderInputType::Texture));
	if ((static_cast<int>(gpu_rw) == static_cast<int>(GPUAccess::Read)))
	{
		ID3D11ShaderResourceView* srv[] = {m_pSRV};

		switch (shaderType)
		{
		case Shader::VertexShader:
			m_pDeviceContext->VSSetShaderResources(id, 1, srv);
			break;
		case Shader::TessellationControlShader:
			m_pDeviceContext->HSSetShaderResources(id, 1, srv);
			break;
		case Shader::TessellationEvaluationShader:
			m_pDeviceContext->DSSetShaderResources(id, 1, srv);
			break;
		case Shader::GeometryShader:
			m_pDeviceContext->GSSetShaderResources(id, 1, srv);
			break;
		case Shader::PixelShader:
			m_pDeviceContext->PSSetShaderResources(id, 1, srv);
			break;
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetShaderResources(id, 1, srv);
			break;
		}
	}
	else if ((static_cast<int>(gpu_rw) & static_cast<int>(GPUAccess::Write)) != 0)
	{
		ID3D11UnorderedAccessView* uav[] = {m_pUAV};
		switch (shaderType)
		{
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetUnorderedAccessViews(id, 1, uav, nullptr);
			break;
		default:
			//Unsupported feature
			break;
		}
	}
	return true;
}

void BufferDX11::unbind(unsigned int ID, Shader::ShaderType shaderType)
{
	ID3D11UnorderedAccessView* uav[] = {nullptr};
	ID3D11ShaderResourceView* srv[] = {nullptr};
	const auto parameterType = m_shader_input_parameter_.m_parameterType;
	if (parameterType == ShaderParameterDx11::ShaderInputType::Buffer)
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
		default:
			assertion(0);
		}
	}
	else if (parameterType == ShaderParameterDx11::ShaderInputType::Buffer)
	{
		switch (shaderType)
		{
		case Shader::ComputeShader:
			m_pDeviceContext->CSSetUnorderedAccessViews(ID, 1, uav, nullptr);
			break;
		default:
			//Unsupported feature
			break;
		}
	}
}

unsigned int BufferDX11::get_element_count() const
{
	return m_uiCount;
}

void BufferDX11::copy(std::shared_ptr<BufferBase> other)
{
	if (!other)
	{
		assert(0);
		//copy(std::dynamic_pointer_cast<Buffer>(other));
	}
}

void BufferDX11::copy_buffer_data()
{
	m_pDeviceContext->CopyResource(m_pStage, m_pBuffer);
	D3D11_MAPPED_SUBRESOURCE ms;
	HRESULT hr = m_pDeviceContext->Map(m_pStage, 0, D3D11_MAP_READ, 0, &ms);
	memcpy_s(m_data_, m_uiCount * m_uiStride, ms.pData, m_uiCount * m_uiStride);
	m_pDeviceContext->Unmap(m_pStage, 0);
}

void BufferDX11::clear()
{
	if (m_pUAV)
	{
		UINT clearColor[4] = {0, 0, 0, 0};
		m_pDeviceContext->ClearUnorderedAccessViewUint(m_pUAV, clearColor);
	}
}


ID3D11UnorderedAccessView* BufferDX11::GetUnorderedAccessView() const
{
	return m_pUAV;
}

void* BufferDX11::get_data() const
{
	return m_data_;
}


void BufferDX11::set_data(const void* data, size_t elementSize, size_t offset, size_t numElements)
{
	const auto first = static_cast<const UINT*>(data) + (offset * elementSize);
	const auto last = first + (numElements * elementSize);
	m_Data.assign(first, last);
	m_bIsDirty = true;
}

void BufferDX11::commit()
{
	if (m_bIsDirty && m_pBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		// Copy the contents of the data buffer to the GPU.

		m_pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);


		const auto size_in_bytes = m_Data.size();
		memcpy_s(mappedResource.pData, size_in_bytes, m_Data.data(), size_in_bytes);

		m_pDeviceContext->Unmap(m_pBuffer, 0);

		m_bIsDirty = false;
	}
}
