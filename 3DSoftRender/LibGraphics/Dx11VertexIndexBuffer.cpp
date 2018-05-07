#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11VertexIndexBuffer.h"
#include "Graphics\Dx11Renderer.h"
#include "Graphics\Shader.h"
using namespace Hikari;

Hikari::VertexIndexBufferDx11::VertexIndexBufferDx11(std::shared_ptr<DirectRenderer>& render, UINT bindFlags, const void * data, size_t count, UINT stride)
	:m_pBuffer(nullptr),
	m_uiStride(stride),
	m_BindFlags(bindFlags),
	m_uiCount((UINT)count),
	m_bIsBound(false)
{
	m_pDevice = (render->GetDevice());
	
	D3D11_BUFFER_DESC bufferDesc;
	D3D11_SUBRESOURCE_DATA resourceData;

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = bindFlags;
	bufferDesc.ByteWidth = m_uiStride * m_uiCount;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	resourceData.pSysMem = data;
	resourceData.SysMemPitch = 0;
	resourceData.SysMemSlicePitch = 0;

	m_pDevice->CreateBuffer(&bufferDesc, &resourceData, &m_pBuffer);
	m_pDevice->GetImmediateContext2(&m_pDeviceContext);
}

Hikari::VertexIndexBufferDx11::~VertexIndexBufferDx11()
{
}

bool Hikari::VertexIndexBufferDx11::Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType,...)
{
	ID3D11Buffer* buffers[] = { m_pBuffer };
	UINT offset[] = { 0 };
	UINT stride[] = { m_uiStride };
	switch (m_BindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		m_pDeviceContext->IASetVertexBuffers(id, 1, buffers, stride, offset);
		m_bIsBound = true;
		break;
	case D3D11_BIND_INDEX_BUFFER:
		m_pDeviceContext->IASetIndexBuffer(m_pBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_bIsBound = true;
		break;
	default:
		break;
	}
	return false;
}

void Hikari::VertexIndexBufferDx11::UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
{
	ID3D11Buffer* buffers[] = { nullptr };

	switch (m_BindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		m_pDeviceContext->IASetVertexBuffers(id, 1, buffers, nullptr, nullptr);
		m_bIsBound = true;
		break;
	case D3D11_BIND_INDEX_BUFFER:
		m_pDeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
		m_bIsBound = true;
		break;
	default:
	
		break;
	}
}

void Hikari::VertexIndexBufferDx11::Copy(std::shared_ptr<BufferBase> other)
{
	std::shared_ptr<VertexIndexBufferDx11> srcBuffer = std::dynamic_pointer_cast<VertexIndexBufferDx11>(other);

	if (m_uiCount * m_uiStride == srcBuffer->m_uiCount * srcBuffer->m_uiStride)
	{
		m_pDeviceContext->CopyResource(m_pBuffer, srcBuffer->m_pBuffer);
	}
}

BufferBase::BufferType Hikari::VertexIndexBufferDx11::GetType() const
{
	switch (m_BindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		return BufferBase::BufferType::VertexBuffer;
		break;
	case D3D11_BIND_INDEX_BUFFER:
		return BufferBase::BufferType::IndexBuffer;
		break;
	case D3D11_BIND_CONSTANT_BUFFER:
		return BufferBase::BufferType::ConstantBuffer;
		break;
	default:
		return BufferBase::BufferType::Unknown;
		break;
	}
}

unsigned int Hikari::VertexIndexBufferDx11::GetElementCount() const
{
	return m_uiCount;
}
