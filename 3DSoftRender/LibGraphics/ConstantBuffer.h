#pragma once
#include "Buffer.h"

namespace Hikari
{
	class ConstantBuffer :public Buffer
	{
	public:
		ConstantBuffer(int numElements,int elementSize)
			:Buffer(numElements,elementSize)
		{

		}
		template <typename T>
		void Set(const T* data);
		
		virtual void Set(const void* data, size_t size) = 0;
	};
	template<typename T>
	inline void ConstantBuffer::Set(const T * data)
	{
		memcpy(mData, data, mNumBytes);
	}
	
}
