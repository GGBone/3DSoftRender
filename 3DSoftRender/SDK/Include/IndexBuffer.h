#pragma once
#include "GraphicsLib.h"
#include "Buffer.h"
namespace Hikari
{
	class IndexBuffer : public Buffer
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
		//DECLARE_STREAM(VertexBuffer);
	public:
		IndexBuffer(int numVertics, int vertexSize, Usage usage = BU_STATIC);
		virtual ~IndexBuffer();
		inline void* GetData()const
		{
			return mData;
		}
	};
}