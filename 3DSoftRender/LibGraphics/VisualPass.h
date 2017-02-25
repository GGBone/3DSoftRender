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
		//inline ID3D11InputLayout* GetInputLayout() const;
		//inline void SetInputLayout(ID3D11InputLayout*);
	private:
		VertexShaderPtr mvShader;
		PixelShaderPtr mpShader;
		//will be escapsel
		//ID3D11InputLayout* inputLayout;

	};
#include "VisualPass.inl"
	typedef VisualPass* VisualPassPtr;
}
