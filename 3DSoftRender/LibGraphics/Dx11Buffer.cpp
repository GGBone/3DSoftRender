#include "GraphicsPCH.h"
#include "Dx11Buffer.h"
#include "Dx11Renderer.h"
using namespace Hikari;

Hikari::BufferDx::BufferDx(DirectRenderer * render, UINT bindFlags, const void * data, size_t count, UINT stride)
	:m_pBuffer(nullptr),
	m_uiStride(stride),
	m_BindFlags(bindFlags),
	m_uiCount((UINT)count),
	m_bIsBound(false)
{
	m_pDevice = render->mData->mDevice;
	
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

Hikari::BufferDx::~BufferDx()
{
}

bool Hikari::BufferDx::Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
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

void Hikari::BufferDx::UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType)
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

void Hikari::BufferDx::Copy(Buffer * other)
{
	BufferDx* srcBuffer = (BufferDx*)other;

	if (m_uiCount * m_uiStride == srcBuffer->m_uiCount * srcBuffer->m_uiStride)
	{
		m_pDeviceContext->CopyResource(m_pBuffer, srcBuffer->m_pBuffer);
	}
}

Buffer::BufferType Hikari::BufferDx::GetType() const
{
	switch (m_BindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		return Buffer::VertexBuffer;
		break;
	case D3D11_BIND_INDEX_BUFFER:
		return Buffer::IndexBuffer;
		break;
	case D3D11_BIND_CONSTANT_BUFFER:
		return Buffer::ConstantBuffer;
		break;
	default:
		return Buffer::Unknown;
		break;
	}
}

unsigned int Hikari::BufferDx::GetElementCount() const
{
	return m_uiCount;
}
