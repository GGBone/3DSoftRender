#pragma once
#include "Dx11RenderLIB.h"
#include "HPoint.h"
#include "Float2.h"
#include "Dx11VertexShader.h"
#include "Dx11Renderer.h"
namespace Hikari
{
	struct BasicFormat
	{
		HPoint Pos;
		HPoint Normal;
		Float2 Tex;
	};
	struct InputLayoutDesc
	{
		static const D3D11_INPUT_ELEMENT_DESC Pos[1];
		static const D3D11_INPUT_ELEMENT_DESC BasicFormat[3];
		static const D3D11_INPUT_ELEMENT_DESC TestFormat[3];

		static const D3D11_INPUT_ELEMENT_DESC UltraFormat[3];

	};
	class DirectRenderer;
	class PdrVertexFormat;
	class PdrVertexShader;
	class InputLayout
	{
	public:
		InputLayout(DirectRenderer* renderer,const PdrVertexShader* vShader,const PdrVertexFormat* vFormat);
		~InputLayout();
		inline ID3D11InputLayout* GetInputLayout() const
		{
			return mInputLayout;
		}
	private:
		ID3D11InputLayout* mInputLayout;
	};
}