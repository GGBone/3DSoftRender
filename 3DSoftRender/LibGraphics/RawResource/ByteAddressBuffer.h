#pragma once
#include "Buffer.h"

namespace Hikari
{
	class ByteAddressBuffer : public Buffer
	{
	public:
		virtual BufferType GetType() const
		{
			return BufferType::ByteAddressBuffer;
		}

		template <typename T>
		void Set(const T& data);

		virtual void Copy(std::shared_ptr<ByteAddressBuffer> other) = 0;

		virtual void Set(const void* data, size_t size) = 0;

	};

	template< typename T >
	void ByteAddressBuffer::Set(const T& data)
	{
		Set(&data, sizeof(T));
	}

}
