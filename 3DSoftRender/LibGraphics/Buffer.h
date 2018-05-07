#pragma once
#include "Graphics\GraphicsLib.h"
#include "BufferBase.h"
namespace Hikari
{
	class Buffer : public BufferBase
	{
	public:

		virtual BufferType GetType() const override
		{
			return BufferType::Buffer;
		}

		virtual unsigned int GetElementCount() const = 0;

		virtual void Copy(std::shared_ptr<Buffer> other) = 0;

		virtual void CopyBufferData() = 0;
		virtual void Clear() = 0;
		template<typename T>
		void Set(const std::vector<T>& value);

		virtual void* GetData() const = 0;
	protected:
		virtual void SetData(void* data, size_t elementSize, size_t offset, size_t numElements) = 0;
		void* m_data;
	};
	template<typename T>
	void Buffer::Set(const std::vector<T>& values)
	{
		SetData((void*)values.data(), sizeof(T), 0, values.size());
	}

}