#pragma once
#include "Dx11RenderLIB.h"
#include "VertexBuffer.h"
#include "Dx11Renderer.h"
namespace Hikari
{
	class Renderer;
	class PdrVertexBuffer
	{
	public:
		PdrVertexBuffer(DirectRenderer* renderer, const VertexBuffer* vbuffer);
		~PdrVertexBuffer();
		void Enable(Renderer* renderer,unsigned int vertexSize,unsigned int streamIndex,unsigned int offset);
		void Disable(Renderer* render, unsigned int streamIndex);
		void* Lock(Buffer::Locking mode);
		void Unlock();
		ID3D11Buffer* const* GetVertexBuffer()const;
	private:
		ID3D11Buffer* mBuffer;
	};
}