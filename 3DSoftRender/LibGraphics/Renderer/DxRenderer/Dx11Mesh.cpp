#include "GraphicsPCH.h"
#include "Dx11Mesh.h"
#include "SceneGraph/Visitor.h"
#include "Dx11Shader.h"
#include "Dx11ShaderParameter.h"
#include "Resource/RasterizerState.h"
#include "SceneGraph/Material.h"
using namespace Hikari;

MeshDx::MeshDx(const std::shared_ptr<DirectRenderer>& render)
{
	m_pDevice = render->GetDevice();
	m_pDevice->GetImmediateContext(&m_pDeviceContext);
}


void MeshDx::Render(RenderEventArgs& renderArgs)
{
	std::shared_ptr<ShaderDx> pVS = nullptr;
	PipelineState* pipeline = renderArgs.PipelineState;
	if (pipeline)
	{
		pVS = std::static_pointer_cast<ShaderDx>(pipeline->GetShader(Shader::VertexShader));
		if (pVS)
		{
			for (auto buffer : m_VertexBuffers)
			{
				const auto binding = buffer.first;
				if (pVS->HasSemantic(binding))
				{
					const auto slot_id = pVS->GetSlotIDBySemantic(binding);

					buffer.second->bind(slot_id);
				}
			}
		}

		if (m_material_)
		{
			for (const auto shader : pipeline->GetShaders())
			{
				m_material_->bind(shader.second);
			}
		}
	}
	RasterizerState::PrimitiveMode primitiveMode;
	pipeline->GetRasterizerState().GetPrimitiveMode(primitiveMode);
	switch (primitiveMode)
	{
	case RasterizerState::PrimitiveMode::TRIANGLE_LIST:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case RasterizerState::PrimitiveMode::TRIANGLE_STRIP:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		break;
	case RasterizerState::PrimitiveMode::LINE_LIST:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case RasterizerState::PrimitiveMode::LINE_STRIP:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		break;
	default:
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	}



	if (m_index_buffer_ != nullptr && m_index_buffer_->get_instanced())
	{
		m_index_buffer_->bind(0);
		m_pDeviceContext->DrawIndexedInstanced(m_index_buffer_->get_element_count(),
			(m_VertexBuffers.begin()->second)->get_element_count(), 0, 0, 0);
		m_index_buffer_->unbind(0);
	}
	else if (m_index_buffer_.get() != nullptr && m_VertexBuffers.size() != 0)
	{
		m_index_buffer_->bind(0);
		m_pDeviceContext->DrawIndexed(m_index_buffer_->get_element_count(), 0, 0);
		m_index_buffer_->unbind(0);
	}

	else
	{
		const auto vertexCount = (*m_VertexBuffers.begin()).second->get_element_count();
		m_pDeviceContext->Draw(vertexCount, 0);
	}
	if (pVS)
	{
		for (auto buffer : m_VertexBuffers)
		{
			const auto binding = buffer.first;
			if (pVS->HasSemantic(binding))
			{
				const auto slot_id = pVS->GetSlotIDBySemantic(binding);
				buffer.second->bind(slot_id);
			}
		}
	}
}

void MeshDx::Accept(Visitor& visitor)
{
	visitor.Visit(*this);
}
