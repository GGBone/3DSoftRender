#pragma once
#include "Dx11RenderLIB.h"
#include "Dx11Renderer.h"
#include "VertexFormat.h"
#include "HPoint.h"
#include "Float2.h"
namespace Hikari
{
	class Renderer;

	class PdrVertexFormat
	{
	public:
		PdrVertexFormat(DirectRenderer* renderer, const VertexFormat* vFormat);
		~PdrVertexFormat();

		void Enable(DirectRenderer* renderer);
		void Disable(DirectRenderer* renderer);

	private:
		ID3D11InputLayout* mInputLayout;
	};
}