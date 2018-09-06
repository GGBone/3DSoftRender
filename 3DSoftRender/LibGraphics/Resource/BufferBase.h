#pragma once
#include "Core.h"
#include "Object.h"

// A buffer is an index buffer or vertex buffer to 
// geometry that should be stored on the GPU.
namespace Hikari
{
	class ShaderParameter;

	class BufferBase : public Object
	{
	public:
		typedef Object base;

		enum class BufferType
		{
			Unknown = 0,
			VertexBuffer = 1 << 1,
			IndexBuffer= 1 << 2,
			ConstantBuffer = 1 << 3,
			//SM5
			Buffer = 1 << 4,
			//R/W
			StructuredBuffer = 1 << 5,
			//R/W
			ByteAddressBuffer = 1 << 6,
			UnorderedAccessBuffer = 1 << 7,
			//Append and Comsume
			VertexIndexBuffer = VertexBuffer | IndexBuffer,
		};

		// Copy the contents of another buffer to this one.
		// Buffers must be the same size in bytes.
		virtual void copy(shared_ptr<BufferBase> other) = 0;

		// Is this an index buffer or an attribute/vertex buffer?
		virtual BufferType get_type() const = 0;
		// How many elements does this buffer contain?
		virtual unsigned int get_element_count() const = 0;
	};
}
