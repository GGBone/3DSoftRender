#pragma once
#include "Dx11RenderLIB.h"
#include "PixelShader.h"
#include "Object.h"
#include "Dx11Renderer.h"
namespace Hikari
{
	class PdrPixelShader : public Object
	{
	public:
		PdrPixelShader(DirectRenderer*, const PixelShader*);


		ID3DBlob* psBuffer;

		ID3D11PixelShader* mPShader;
	};
	typedef PdrPixelShader* PdrPixelShaderPtr;
}
