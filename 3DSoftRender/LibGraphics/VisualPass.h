#pragma once
#include "GraphicsLib.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Dx11RenderLIB.h"
namespace Hikari
{
	class VisualPass : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		VisualPass();
		~VisualPass();
		inline void SetVertexShader(VertexShader* vsShader);
		inline void SetPixelShader(PixelShader* vsShader);
		inline VertexShader* GetVertexShader() const;
		inline PixelShader* GetPixelShader() const;

	private:
		VertexShaderPtr mvShader;
		PixelShaderPtr mpShader;
	

	};
#include "VisualPass.inl"
	typedef VisualPass* VisualPassPtr;
}
