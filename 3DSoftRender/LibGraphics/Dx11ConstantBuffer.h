#pragma once
#include "GraphicsLib.h"
#include "Dx11Renderer.h"
#include "ConstantBuffer.h"

#include "Shader.h"
namespace Hikari
{
	class PdrConstantBuffer
	{
	public:
		PdrConstantBuffer(DirectRenderer* render, ConstantBuffer* constanBuffer);

		void Bind();
		void UnBind();

	private:
		ID3D11Buffer* mBuffer;
	};
}
