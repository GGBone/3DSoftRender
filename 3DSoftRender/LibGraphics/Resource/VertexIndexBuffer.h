#pragma once
#include "BufferBase.h"

namespace Hikari
{
	class VertexIndexBuffer : public BufferBase
	{
	public:
		BufferType get_type() const override
		{
			return BufferType::VertexIndexBuffer;
		}

		virtual unsigned int GetElementCount() const
		{
			return 1;
		}

		template <typename T>
		void set(const T& data);

		virtual void set(const void* data, size_t size) = 0;

		virtual void bind(unsigned int id) = 0;
		virtual void unbind(unsigned int id) = 0;
	};

	template <typename T>
	void VertexIndexBuffer::set(const T& data)
	{
		set(&data, sizeof(T));
	}
}
