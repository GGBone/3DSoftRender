#include "GraphicsPCH.h"
#include "Dx11ConstantBuffer.h"
#include "Dx11ShaderParameter.h"
using namespace Hikari;

ConstantBufferDX11::ConstantBufferDX11(ID3D11Device* pDevice, size_t size)
	: m_pDevice(pDevice),
	  m_BufferSize(size)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = static_cast<UINT>(m_BufferSize);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pBuffer);

	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}

ConstantBufferDX11::~ConstantBufferDX11() = default;

void ConstantBufferDX11::bind(unsigned int id, Shader::ShaderType shaderType)
{
	ID3D11Buffer* pBuffers[] = {m_pBuffer};

	switch (shaderType)
	{
	case Shader::VertexShader:
		m_pDeviceContext->VSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::TessellationControlShader:
		m_pDeviceContext->HSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::TessellationEvaluationShader:
		m_pDeviceContext->DSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::GeometryShader:
		m_pDeviceContext->GSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::PixelShader:
		m_pDeviceContext->PSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::ComputeShader:
		m_pDeviceContext->CSSetConstantBuffers(id, 1, pBuffers);
		break;
	default:
		assertion(false);
		break;
	}
}

void ConstantBufferDX11::unbind(unsigned int id, Shader::ShaderType shaderType)
{
	ID3D11Buffer* pBuffers[] = {nullptr};

	switch (shaderType)
	{
	case Shader::VertexShader:
		m_pDeviceContext->VSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::TessellationControlShader:
		m_pDeviceContext->HSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::TessellationEvaluationShader:
		m_pDeviceContext->DSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::GeometryShader:
		m_pDeviceContext->GSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::PixelShader:
		m_pDeviceContext->PSSetConstantBuffers(id, 1, pBuffers);
		break;
	case Shader::ComputeShader:
		m_pDeviceContext->CSSetConstantBuffers(id, 1, pBuffers);
		break;
	default:
		break;
	}
}


void ConstantBufferDX11::copy(std::shared_ptr<BufferBase> other)
{
	std::shared_ptr<ConstantBufferDX11> srcBuffer = std::dynamic_pointer_cast<ConstantBufferDX11>(other);
	if (!srcBuffer)
		return;
	m_pDeviceContext->CopyResource(m_pBuffer, srcBuffer->m_pBuffer);
}

void ConstantBufferDX11::set(const void* data, size_t size)
{
	if (size <= 0)
		return;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	m_pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, data, m_BufferSize);
	m_pDeviceContext->Unmap(m_pBuffer, 0);
}
