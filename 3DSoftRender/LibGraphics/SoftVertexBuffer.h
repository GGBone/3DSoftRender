#pragma once
#include "GraphicsLib.h"

#include "SoftRenderer.h"

namespace Hikari
{
	class SoftVertexBuffer
	{
	public:
		SoftVertexBuffer(SoftRenderer* renderer, const Buffer* vbuffer);
		~SoftVertexBuffer();
		void Enable(SoftRenderer* renderer, unsigned int index, unsigned int offset);
		void Disable(SoftRenderer * renderer, unsigned int index);

		Buffer* const* GetVertexBuffer()const;
	private:
		Buffer* mBuffer;
	};
}