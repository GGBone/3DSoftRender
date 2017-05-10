#pragma once

#include <Object.h>
#include <BufferBinding.h>
namespace Hikari
{
	class Buffer;
	class Shader;
	class Material;
	class RenderEventArgs;
	class Visitor;

	// A mesh contains the geometry and materials required to render this mesh.
	class Mesh : public Object
	{
	public:
		// Adds a buffer to this mesh with a particular semantic (HLSL) or register ID (GLSL).
		virtual void AddVertexBuffer(const BufferBinding& binding, Buffer* buffer) = 0;
		virtual void SetIndexBuffer(Buffer* buffer) = 0;
		virtual void SetInstanceBuffer(Buffer* buffer) = 0;

		virtual void SetMaterial(Material* material) = 0;
		virtual Material* GetMaterial() const = 0;
		virtual void Render(RenderEventArgs& renderEventArgs) = 0;

		virtual void Accept(Visitor& visitor) = 0;
	};
}