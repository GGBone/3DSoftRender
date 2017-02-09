#pragma once
#include "GraphicsLib.h"

#include "SoftRenderer.h"
#include "VertexBuffer.h"

namespace Hikari
{
	class SoftVertexBuffer
	{
	public:
		SoftVertexBuffer(SoftRenderer* renderer, const VertexBuffer* vbuffer);
		~SoftVertexBuffer();
		void Enable(SoftRenderer* renderer, unsigned int index, unsigned int offset);
		void Disable(SoftRenderer * renderer, unsigned int index);
		void* Lock(Buffer::Locking mode);
		void UnLock();

		Buffer* const* GetVertexBuffer()const;
	private:
		Buffer* mBuffer;
	};
}