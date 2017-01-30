#include "Buffer.h"
inline int Hikari::Buffer::GetNumElements()const
{
	return mNumElements;
}

inline int Hikari::Buffer::GetElementSize() const
{
	return mElementSize;
}

inline Buffer::Usage Hikari::Buffer::GetUsage() const
{
	return mUsage;
}

inline void Hikari::Buffer::SetNumElements(int numElements)
{
	mNumElements = numElements;
}

inline int Hikari::Buffer::GetNumBytes() const
{
	return mNumBytes;
}

inline const char* Hikari::Buffer::GetData() const
{
	return mData;
}
inline void	Hikari::Buffer::SetData(void* Data)
{
	memcpy(mData, Data, 72);
}