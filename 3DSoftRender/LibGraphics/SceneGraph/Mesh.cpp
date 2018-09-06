#include "GraphicsPCH.h"

#include "Mesh.h"

void Hikari::Mesh::AddVertexBuffer(const BufferBinding& binding, std::shared_ptr<VertexIndexBuffer> buffer)
{
	m_VertexBuffers[binding] = buffer;
}

void Hikari::Mesh::SetIndexBuffer(std::shared_ptr<VertexIndexBuffer> buffer)
{
	m_index_buffer_ = buffer;
}

void Hikari::Mesh::SetInstanceBuffer(std::shared_ptr<VertexIndexBuffer> buffer)
{
	m_instance_buffer_ = buffer;
}

void Hikari::Mesh::SetMaterial(std::shared_ptr<Material> material)
{
	m_material_ = material;
}

std::shared_ptr<Hikari::Material> Hikari::Mesh::GetMaterial() const
{
	return m_material_;
}
