#pragma once
#include "GraphicsLib.h"
#include "Buffer.h"
namespace Hikari
{
	class StructuredBuffer : public Buffer
	{
	public:
		// Bind the buffer for rendering.
		virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) = 0;
		// Unbind the buffer for rendering.
		virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) = 0;

		// Is this an index buffer or an attribute/vertex buffer?
		virtual BufferType GetType() const = 0;
		// How many elements does this buffer contain?
		virtual unsigned int GetElementCount() const = 0;

		// Copy the contents of another buffer to this one.
		// Buffers must be the same size.
		virtual void Copy(StructuredBuffer* other) = 0;

		// Set the buffer data.
		template<typename T>
		void Set(const std::vector<T>& value);

		// Clear the contents of the buffer.
		virtual void Clear() = 0;

	protected:
		virtual void SetData(void* data, size_t elementSize, size_t offset, size_t numElements) = 0;

	};

	template<typename T>
	void StructuredBuffer::Set(const std::vector<T>& values)
	{
		SetData((void*)values.data(), sizeof(T), 0, values.size());
	}

}