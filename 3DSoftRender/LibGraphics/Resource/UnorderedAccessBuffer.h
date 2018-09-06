#pragma once
#include "GraphicsLib.h"
#include "BufferBase.h"

namespace Hikari
{
	class UnorderedAccessBuffer : public BufferBase
	{
	public:

		BufferType get_type() const override { return BufferType::UnorderedAccessBuffer; }

		unsigned int get_element_count() const override = 0;

		template <typename T>
		void set(const std::vector<T>& value);

		virtual void clear() = 0;

		virtual uint32_t get_stride() const = 0;


		// Bind the buffer for rendering.
		virtual bool bind(unsigned int id, Shader::ShaderType) = 0;
		// Unbind the buffer for rendering.
		virtual void unbind(unsigned int id, Shader::ShaderType) = 0;
	protected:
		virtual void set_data(void* data, size_t elementSize, size_t offset, size_t numElements) = 0;
	};

	template <typename T>
	void UnorderedAccessBuffer::set(const std::vector<T>& values)
	{
		set_data(static_cast<void*>(values.data()), sizeof(T), 0, values.size());
	}
}
