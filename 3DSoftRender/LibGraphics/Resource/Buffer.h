#pragma once
#include "BufferBase.h"
#include "Shader/Shader.h"

namespace Hikari
{
	class Buffer : public BufferBase
	{
	public:

		BufferType get_type() const override
		{
			return BufferType::Buffer;
		}

		virtual void copy_buffer_data() = 0;
		virtual void clear() = 0;
		template <typename T>
		void set(const std::vector<T>& value);

		virtual void* get_data() const = 0;

		// Bind the buffer for rendering.
		virtual bool bind(unsigned int id, Shader::ShaderType) = 0;
		// Unbind the buffer for rendering.
		virtual void unbind(unsigned int id, Shader::ShaderType) = 0;

	protected:
		virtual void set_data(const void* data, size_t element_size, size_t offset, size_t num_elements) = 0;
		void* m_data_ = nullptr;
	};


	template <typename T>
	void Buffer::set(const std::vector<T>& values)
	{
		set_data(static_cast<const void*>(values.data()), sizeof(T), 0, values.size());
	}
}
