#pragma once
#include "GraphicsLIB.h"
#include "Object.h"
namespace Hikari
{
	class Buffer : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
		//DECLEAR_STREAM(Buffer);

	public:
		enum Usage
		{
			BU_STATIC,
			BU_DYNAMIC,
			BU_RENDERTARGET,
			BU_DEPTHSTENCIL,
			BU_TEXTURE,
			BU_QUANTITY
		};

		enum Locking
		{
			BL_READ_ONLY,
			BL_WRITE_ONLY,
			BL_READ_WRITE,
			BL_NEVER
		};
		Buffer(int numElements, int elementSize, Usage usage = BU_STATIC);
	public:
		virtual ~Buffer();

		inline int GetNumElements()const;
		inline int GetElementSize()const;
		inline Usage GetUsage() const;

		inline void SetNumElements(int numElements);

		inline int GetNumBytes()const;
		inline const void* GetData()const;
		inline void SetData(void* data);
	protected:
		int mNumElements;
		int mElementSize;
		Usage mUsage;
		int mNumBytes;
		void* mData;
		friend class WinSoftRenderer;
		friend class SoftRenderer;
	};
	typedef Buffer* BufferPtr;
#include "Buffer.inl"

}