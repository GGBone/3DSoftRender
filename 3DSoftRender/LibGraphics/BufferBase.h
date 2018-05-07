#pragma once
#include "Core\Object.h"
#include "Graphics\ShaderParameter.h"
#include "Graphics\Shader.h"
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
			VertexBuffer,
			IndexBuffer,
			ConstantBuffer,
			//SM5
			Buffer,				//R/W
			StructuredBuffer,	//R/W
			ByteAddressBuffer,
			UnoderedAccessBuffer	//Append and Comsume
		};

		// Bind the buffer for rendering.
		virtual bool Bind(unsigned int ID, Shader::ShaderType shaderType, ShaderParameter::Type parameterType,...) = 0;
		// Unbind the buffer for rendering.
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) = 0;

		// Copy the contents of another buffer to this one.
		// Buffers must be the same size in bytes.
		virtual void Copy(std::shared_ptr<BufferBase> other) = 0;

		// Is this an index buffer or an attribute/vertex buffer?
		virtual BufferType GetType() const = 0;
		// How many elements does this buffer contain?
		virtual unsigned int GetElementCount() const = 0;

	};
}