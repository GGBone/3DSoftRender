#pragma once
#include "GraphicsLib.h"
#include "BufferBase.h"

namespace Hikari
{
	class StructuredBuffer : public BufferBase
	{
	public:
		friend class ShaderParameter;
		BufferType get_type() const override { return BufferType::StructuredBuffer; };

		template <typename T>
		void set(const std::vector<T>& value);

		virtual void Clear() = 0;

		virtual UINT GetStride() const = 0;

		// Bind the buffer for rendering.
		virtual void bind(unsigned int id, Shader::ShaderType shaderType) = 0;
		// Unbind the buffer for rendering.
		virtual void unbind(unsigned int id, Shader::ShaderType shaderType) = 0;
	protected:
		virtual void SetData(const void* data, size_t elementSize, size_t offset, size_t numElements) = 0;

		ShaderParameter::ShaderInputParameter m_shader_input_param_;

	};

	template <typename T>
	void StructuredBuffer::set(const std::vector<T>& values)
	{
		SetData(static_cast<const void*>(values.data()), sizeof(T), 0, values.size());
	}
}
