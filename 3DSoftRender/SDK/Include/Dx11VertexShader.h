#pragma once
#include "Dx11RenderLIB.h"
#include "VertexShader.h"
#include "Object.h"
#include "Dx11Renderer.h"
namespace Hikari
{
	class DirectRenderer;
	class PdrVertexShader : public Object
	{
	public:
		PdrVertexShader(DirectRenderer*, const VertexShader*);

		ID3DBlob* vsBuffer;
		ID3D11Buffer** mConstantBuffer;
		void Enable(DirectRenderer* renderer, const VertexShader* vshader, const ShaderParameters* param);
		ID3D11VertexShader* mVShader;
	};
	typedef PdrVertexShader* PdrVertexShaderPtr;
}