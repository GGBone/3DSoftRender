#include "GraphicsPCH.h"
#include "Dx11Mesh.h"
#include "Visitor.h"
#include "Dx11Buffer.h"
#include "Dx11Shader.h"
#include "Dx11PipelineState.h"
#include "RenderEventArgs.h"
#include "Material.h"
using namespace Hikari;

Hikari::MeshDx::MeshDx(DirectRenderer * render)
	:m_pIndexBuffer(nullptr),
	m_pMaterial(nullptr)
{
	m_pDevice = render->mData->mDevice;
	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}

Hikari::MeshDx::~MeshDx()
{
}

void Hikari::MeshDx::AddVertexBuffer(const BufferBinding & binding, Buffer * buffer)
{
	m_VertexBuffers[binding] = buffer;
}

void Hikari::MeshDx::SetIndexBuffer(Buffer * buffer)
{
	m_pIndexBuffer = buffer;
}

void Hikari::MeshDx::SetMaterial(Material * material)
{
	m_pMaterial = material;
}

void Hikari::MeshDx::SetInstanceBuffer(Buffer * buffer)
{
	m_pInstanceBuffer = buffer;
}

Material* Hikari::MeshDx::GetMaterial() const
{
	return m_pMaterial;
}

void Hikari::MeshDx::Render(RenderEventArgs & renderArgs)
{
	
	ShaderDx* pVS = nullptr;
	PipelineState* pipeline = renderArgs.PipelineState;
	if (pipeline)
	{
		pVS = static_cast<ShaderDx*>(pipeline->GetShader(Shader::VertexShader));
		if(pVS)
		{
			for (BufferMap::value_type buffer:m_VertexBuffers)
			{
				BufferBinding binding = buffer.first;
				if (pVS->HasSemantic(binding))
				{
					UINT slotID = pVS->GeetSlotIDBySemantic(binding);

					buffer.second->Bind(slotID, Shader::VertexShader, ShaderParameter::Type::Buffer);
				}
			}
		}

		if (m_pMaterial)
		{
			for (auto shader : pipeline->GetShaders())
			{
				m_pMaterial->Bind(shader.second);
			}
		}
	}

	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	if (m_pIndexBuffer != nullptr && m_VertexBuffers.size() == 3)
	{
		m_pIndexBuffer->Bind(0, Shader::VertexShader, ShaderParameter::Type::Buffer);
		m_pDeviceContext->DrawIndexed(m_pIndexBuffer->GetElementCount(), 0, 0);
		m_pIndexBuffer->UnBind(0, Shader::VertexShader, ShaderParameter::Type::Buffer);
	}
	else if (m_pIndexBuffer != nullptr && m_VertexBuffers.size() != 0)
	{
		m_pIndexBuffer->Bind(0, Shader::VertexShader, ShaderParameter::Type::Buffer);
		m_pDeviceContext->DrawIndexedInstanced(m_pIndexBuffer->GetElementCount(),((BufferDx*)m_VertexBuffers.begin()->second)->GetElementCount(),0,0, 0);
		m_pIndexBuffer->UnBind(0, Shader::VertexShader, ShaderParameter::Type::Buffer);
	}
	else
	{
		UINT vertexCount = (*m_VertexBuffers.begin()).second->GetElementCount();
		m_pDeviceContext->Draw(vertexCount, 0);
	}
	if (pVS)
	{
		for (BufferMap::value_type buffer : m_VertexBuffers)
		{
			BufferBinding binding = buffer.first;
			if (pVS->HasSemantic(binding))
			{
				UINT slotID = pVS->GeetSlotIDBySemantic(binding);
				buffer.second->Bind(slotID, Shader::VertexShader, ShaderParameter::Type::Buffer);

			}
		}
	}
	
}

void Hikari::MeshDx::Accept(Visitor & visitor)
{
	visitor.Visit(*this);
}

