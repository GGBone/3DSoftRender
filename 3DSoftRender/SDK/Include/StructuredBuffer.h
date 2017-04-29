#pragma once
#include "GraphicsLib.h"
#include "Buffer.h"
namespace Hikari
{
	class StructuredBuffer : public Buffer
	{
	public:

		virtual BufferType GetType() const = 0;
		
		virtual unsigned int GetElementCount() const = 0;

		virtual void Copy(StructuredBuffer* other) = 0;

		template<typename T>
		void Set(const std::vector<T>& value);

		virtual void Clear() = 0;

		virtual UINT GetStride()const = 0;
	protected:
		virtual void SetData(void* data, size_t elementSize, size_t offset, size_t numElements) = 0;

	};
	template<typename T>
	void StructuredBuffer::Set(const std::vector<T>& values)
	{
		SetData((void*)values.data(), sizeof(T), 0, values.size());
	}

}