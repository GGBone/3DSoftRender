#pragma once
#include "Buffer.h"

namespace Hikari
{
	class ConstantBuffer : public Buffer
	{
	public:
		// The contents of a constant buffer can also be updated.
		template <typename T>
		void Set(const T& data);
		// Always returns BufferType::ConstantBuffer
		virtual BufferType GetType() const
		{
			return BufferType::ConstantBuffer;
		}
		// Constant buffers only have 1 element.
		virtual unsigned int GetElementCount() const
		{
			return 1;
		}

		// Copy the contents of a buffer to this one.
		// Buffers must be the same size.
		virtual void Copy(ConstantBuffer* other) = 0;

		// Implementations must provide this method.
		virtual void Set(const void* data, size_t size) = 0;

	};
	
	template< typename T >
	void ConstantBuffer::Set(const T& data)
	{
		Set(&data, sizeof(T));
	}

}
