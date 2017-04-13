#pragma once
#include "Object.h"
#include "ShaderParameter.h"
#include "Shader.h"
// A buffer is an index buffer or vertex buffer to 
// geometry that should be stored on the GPU.
namespace Hikari
{
	class Shader;
	class ShaderParameter;
	class Buffer : public Object
	{
	public:
		typedef Object base;

		enum BufferType
		{
			Unknown = 0,
			VertexBuffer,
			IndexBuffer,
			StructuredBuffer,
			ConstantBuffer
		};

		// Bind the buffer for rendering.
		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) = 0;
		// Unbind the buffer for rendering.
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) = 0;

		// Copy the contents of another buffer to this one.
		// Buffers must be the same size in bytes.
		virtual void Copy(Buffer* other) = 0;

		// Is this an index buffer or an attribute/vertex buffer?
		virtual BufferType GetType() const = 0;
		// How many elements does this buffer contain?
		virtual unsigned int GetElementCount() const = 0;

	};
}