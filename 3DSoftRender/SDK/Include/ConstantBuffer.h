#pragma once
#include "Buffer.h"

namespace Hikari
{
	class ConstantBuffer : public Buffer
	{
	public:
		

		virtual BufferType GetType() const
		{
			return BufferType::ConstantBuffer;
		}

		virtual unsigned int GetElementCount() const
		{
			return 1;
		}
	
		template <typename T>
		void Set(const T& data);

		virtual void Copy(ConstantBuffer* other) = 0;

		virtual void Set(const void* data, size_t size) = 0;

	};
	
	template< typename T >
	void ConstantBuffer::Set(const T& data)
	{
		Set(&data, sizeof(T));
	}

}
