#pragma once

#include "Object.h"
#include "Resource/BufferBinding.h"
#include	"Resource/VertexIndexBuffer.h"

namespace Hikari
{
	class BufferBase;
	class Shader;
	class Material;
	class RenderEventArgs;
	class Visitor;

	// A mesh contains the geometry and materials required to render this mesh.
	class Mesh : public Object
	{
	public:
		// Adds a buffer to this mesh with a particular semantic (HLSL) or register ID (GLSL).
		virtual void AddVertexBuffer(const BufferBinding& binding, std::shared_ptr<VertexIndexBuffer> buffer);
		virtual void SetIndexBuffer(std::shared_ptr<VertexIndexBuffer> buffer);
		virtual void SetInstanceBuffer(std::shared_ptr<VertexIndexBuffer> buffer);

		virtual void SetMaterial(std::shared_ptr<Material> material);
		virtual std::shared_ptr<Material> GetMaterial() const;
		virtual void Render(RenderEventArgs& renderEventArgs) = 0;

		virtual void Accept(Visitor& visitor) = 0;
	protected:
		typedef std::map<BufferBinding, std::shared_ptr<VertexIndexBuffer>> BufferMap;
		BufferMap m_VertexBuffers{};

		shared_ptr<VertexIndexBuffer> m_index_buffer_{};
		shared_ptr<VertexIndexBuffer> m_instance_buffer_{};
		shared_ptr<Material> m_material_{};
	};
}
