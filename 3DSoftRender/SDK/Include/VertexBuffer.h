#pragma once
#include "GraphicsLib.h"
#include "Buffer.h"
namespace Hikari
{
	class VertexBuffer : public Buffer
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
		//DECLARE_STREAM(VertexBuffer);
	public:
		VertexBuffer(int numVertics,int vertexSize,Usage usage = BU_STATIC);
		virtual ~VertexBuffer();

		inline void* GetData()const;

	};
	typedef VertexBuffer* VertexBufferPtr;
#include "VertexBuffer.inl"
}