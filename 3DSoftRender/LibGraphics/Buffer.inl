#include "Buffer.h"
using namespace std;
inline int Hikari::Buffer::GetNumElements()const
{
	return mNumElements;
}

inline int Hikari::Buffer::GetElementSize() const
{
	return mElementSize;
}


inline void Hikari::Buffer::SetNumElements(int numElements)
{
	mNumElements = numElements;
}

inline int Hikari::Buffer::GetNumBytes() const
{
	return mNumBytes;
}

inline const void* Hikari::Buffer::GetData() const
{
	return mData;
}
inline void	Hikari::Buffer::SetData(void* Data)
{
	memcpy(mData, Data, 72);
}