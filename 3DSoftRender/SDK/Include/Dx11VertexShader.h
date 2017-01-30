#pragma once
#include "Dx11RenderLIB.h"
#include "VertexShader.h"
#include "Object.h"
#include "Renderer.h"
namespace Hikari
{
	class PdrVertexShader : public Object
	{
	public:
		PdrVertexShader(Renderer*,const VertexShader*);

		ID3DBlob* vsBuffer;

		ID3D11VertexShader* mVShader;
	};
	typedef PdrVertexShader* PdrVertexShaderPtr;
}
