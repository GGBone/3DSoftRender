#include "GraphicsPCH.h"
#include "Dx11VertexIndexBuffer.h"
#include "Dx11Renderer.h"
#include "Shader/Shader.h"
using namespace Hikari;

VertexIndexBufferDx11::VertexIndexBufferDx11(std::shared_ptr<DirectRenderer>& render, UINT bindFlags, const void* data,
	size_t count, UINT stride)
	:
	m_uiStride(stride),
	m_BindFlags(bindFlags),
	m_uiCount(static_cast<UINT>(count)),
	m_bIsBound(false),
	m_bInstanced(false)
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
	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}

VertexIndexBufferDx11::~VertexIndexBufferDx11()
= default;

void VertexIndexBufferDx11::bind(unsigned int id)
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
}

void VertexIndexBufferDx11::unbind(unsigned int id)
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

void VertexIndexBufferDx11::set(const void* data, size_t size)
{
	assert(0);
}

void VertexIndexBufferDx11::copy(std::shared_ptr<BufferBase> other)
{
	const auto srcBuffer = std::dynamic_pointer_cast<VertexIndexBufferDx11>(other);

	if (m_uiCount * m_uiStride == srcBuffer->m_uiCount * srcBuffer->m_uiStride)
	{
		m_pDeviceContext->CopyResource(m_pBuffer, srcBuffer->m_pBuffer);
	}
}

BufferBase::BufferType VertexIndexBufferDx11::get_type() const
{
	switch (m_BindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		return BufferType::VertexBuffer;
		break;
	case D3D11_BIND_INDEX_BUFFER:
		return BufferType::IndexBuffer;
		break;
	case D3D11_BIND_CONSTANT_BUFFER:
		return BufferType::ConstantBuffer;
		break;
	default:
		return BufferType::Unknown;
		break;
	}
}

unsigned VertexIndexBufferDx11::get_element_count() const
{
	return m_uiCount;
}
