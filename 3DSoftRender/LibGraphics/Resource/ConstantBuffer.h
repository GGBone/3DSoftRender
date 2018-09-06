#pragma once
#include "BufferBase.h"
#include "Shader/Shader.h"

namespace Hikari
{
	class ConstantBuffer : public BufferBase
	{
	public:
		BufferType get_type() const override
		{
			return BufferType::ConstantBuffer;
		}

		unsigned int get_element_count() const override
		{
			return 1;
		}

		template <typename T>
		void set(const T& data);

		virtual void set(const void* data, size_t size) = 0;

		virtual void bind(unsigned int id, Shader::ShaderType shaderType) = 0;
		virtual void unbind(unsigned int id, Shader::ShaderType shaderType) =0;
	};

	template <typename T>
	void ConstantBuffer::set(const T& data)
	{
		set(&data, sizeof(T));
	}
}
