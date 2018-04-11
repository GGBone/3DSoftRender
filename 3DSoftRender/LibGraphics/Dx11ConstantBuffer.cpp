#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11ConstantBuffer.h"
using namespace Hikari;

Hikari::ConstantBufferDX11::ConstantBufferDX11(ID3D11Device * pDevice, size_t size)
:m_pDevice(pDevice),
m_BufferSize(size)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = (UINT)m_BufferSize;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pBuffer);

	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}

Hikari::ConstantBufferDX11::~ConstantBufferDX11()
{
}

bool Hikari::ConstantBufferDX11::Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
	bool result = true;
	ID3D11Buffer* pBuffers[] = { m_pBuffer };

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
		result = false;
		break;
	}
	return result;
}

void Hikari::ConstantBufferDX11::UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
	ID3D11Buffer* pBuffers[] = { nullptr };

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

void Hikari::ConstantBufferDX11::Copy(std::shared_ptr<ConstantBuffer> other)
{
	std::shared_ptr<ConstantBufferDX11> srcBuffer = std::dynamic_pointer_cast<ConstantBufferDX11>(other);
	if (!srcBuffer)
		return;
	m_pDeviceContext->CopyResource(m_pBuffer, srcBuffer->m_pBuffer);
}

void Hikari::ConstantBufferDX11::Copy(std::shared_ptr<Buffer> other)
{
	Copy(std::dynamic_pointer_cast<ConstantBuffer>(other));
}

void Hikari::ConstantBufferDX11::Set(const void * data, size_t size)
{
	if (size <= 0)
		return;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	m_pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, data, m_BufferSize);
	m_pDeviceContext->Unmap(m_pBuffer, 0);
}
