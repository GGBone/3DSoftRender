#pragma once
#include "GraphicsLib.h"
#include "Buffer.h"
namespace Hikari
{
	class RWBuffer : public Buffer
	{
	public:

		virtual BufferType GetType() const override
		{
			return BufferType::RWBuffers;
		}

		virtual unsigned int GetElementCount() const = 0;

		virtual void Copy(RWBuffer* other) = 0;

		virtual void Clear() = 0;
		template<typename T>
		void Set(const std::vector<T>& value);

		virtual void* GetData() const = 0;
	protected:
		virtual void SetData(void* data, size_t elementSize, size_t offset, size_t numElements) = 0;
		void* m_data;
	};
	template<typename T>
	void RWBuffer::Set(const std::vector<T>& values)
	{
		SetData((void*)values.data(), sizeof(T), 0, values.size());
	}

}