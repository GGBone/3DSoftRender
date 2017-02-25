#pragma once
#include "Dx11RenderLIB.h"
#include "PixelShader.h"
#include "Object.h"
#include "Dx11Renderer.h"
#include "Shader.h"
#include "ShaderParameters.h"
namespace Hikari
{
	class DirectRenderer;
	class PdrPixelShader
	{
	public:
		PdrPixelShader(DirectRenderer*, const PixelShader*);

		void Hikari::PdrPixelShader::Enable(DirectRenderer * renderer, const PixelShader * pShader, const ShaderParameters* param);
		ID3DBlob* psBuffer;
		ID3D11Buffer** mConstantBuffer;
		ID3D11PixelShader* mPShader;
	};
	typedef PdrPixelShader* PdrPixelShaderPtr;
}
