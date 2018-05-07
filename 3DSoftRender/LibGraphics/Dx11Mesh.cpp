#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11Mesh.h"
#include "Graphics\Visitor.h"
#include "Graphics\Dx11VertexIndexBuffer.h"
#include "Graphics\Dx11Shader.h"
#include "Graphics\Dx11PipelineState.h"
#include "Graphics\RenderEventArgs.h"
#include "Graphics\Material.h"
using namespace Hikari;

Hikari::MeshDx::MeshDx(std::shared_ptr<DirectRenderer>& render)
	:m_pIndexBuffer(nullptr),
	m_pMaterial(nullptr)
{
	m_pDevice = render->GetDevice();
	m_pDevice->GetImmediateContext2(&m_pDeviceContext);
}

Hikari::MeshDx::~MeshDx()
{
}

void Hikari::MeshDx::AddVertexBuffer(const BufferBinding & binding, std::shared_ptr<BufferBase> buffer)
{
	m_VertexBuffers[binding] = buffer;
}

void Hikari::MeshDx::SetIndexBuffer(std::shared_ptr<BufferBase> buffer)
{
	m_pIndexBuffer = buffer;
}

void Hikari::MeshDx::SetMaterial(std::shared_ptr<Material> material)
{
	m_pMaterial = material;
}

void Hikari::MeshDx::SetInstanceBuffer(std::shared_ptr<BufferBase> buffer)
{
	m_pInstanceBuffer = buffer;
}

std::shared_ptr<Material> Hikari::MeshDx::GetMaterial() const
{
	return m_pMaterial;
}

void Hikari::MeshDx::Render(RenderEventArgs & renderArgs)
{
	
	std::shared_ptr<ShaderDx> pVS = nullptr;
	PipelineState* pipeline = renderArgs.PipelineState;
	if (pipeline)
	{
		pVS = std::dynamic_pointer_cast<ShaderDx>(pipeline->GetShader(Shader::VertexShader));
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
	RasterizerState::PrimitiveMode primitiveMode;
	pipeline->GetRasterizerState().GetPrimitiveMode(primitiveMode);
	switch (primitiveMode)
	{
	case Hikari::RasterizerState::PrimitiveMode::TRIANGLE_LIST:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case Hikari::RasterizerState::PrimitiveMode::TRIANGLE_STRIP:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		break;
	case Hikari::RasterizerState::PrimitiveMode::LINE_LIST:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case Hikari::RasterizerState::PrimitiveMode::LINE_STRIP:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		break;
	default:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	}
	
	
	if (m_pIndexBuffer != nullptr && m_VertexBuffers.size() != 0)
	{
		m_pIndexBuffer->Bind(0, Shader::VertexShader, ShaderParameter::Type::Buffer);
		m_pDeviceContext->DrawIndexed(m_pIndexBuffer->GetElementCount(), 0, 0);
		m_pIndexBuffer->UnBind(0, Shader::VertexShader, ShaderParameter::Type::Buffer);
		
	}
	else if (m_pIndexBuffer != nullptr && (m_VertexBuffers.size() == 2))
	{
		m_pIndexBuffer->Bind(0, Shader::VertexShader, ShaderParameter::Type::Buffer);
		m_pDeviceContext->DrawIndexedInstanced(m_pIndexBuffer->GetElementCount(), (m_VertexBuffers.begin()->second)->GetElementCount(), 0, 0, 0);
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

