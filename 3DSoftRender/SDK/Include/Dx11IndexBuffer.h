#pragma once
#include "GraphicsLib.h"
#include "IndexBuffer.h"
#include "Dx11Renderer.h"
namespace Hikari
{
	class PdrIndexBuffer
	{
	public:
		Hikari::PdrIndexBuffer::PdrIndexBuffer(DirectRenderer * renderer, const IndexBuffer * ibuffer);
		Hikari::PdrIndexBuffer::~PdrIndexBuffer();
		void Hikari::PdrIndexBuffer::Enable(DirectRenderer * renderer, unsigned int vertexSize, unsigned int streamIndex, unsigned int offset);
		ID3D11Buffer* const * Hikari::PdrIndexBuffer::GetIndexBuffer() const;
	private:
		ID3D11Buffer* mbuffer;
	};
}