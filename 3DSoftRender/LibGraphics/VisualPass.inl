#include "VisualPass.h"

#pragma once

inline Hikari::VertexShader * Hikari::VisualPass::GetVertexShader() const
{
	return mvShader;
}

inline Hikari::PixelShader * Hikari::VisualPass::GetPixelShader() const
{
	return mpShader;
}

inline ID3D11InputLayout * Hikari::VisualPass::GetInputLayout() const
{
	return inputLayout;
}

inline void Hikari::VisualPass::SetInputLayout(ID3D11InputLayout * input)
{
	inputLayout = input;
}


inline void Hikari::VisualPass::SetVertexShader(VertexShader * vsShader)
{
	//memcpy(mvShader,vsShader,sizeof(VertexShader));
	mvShader = vsShader;
}

inline void Hikari::VisualPass::SetPixelShader(PixelShader * psShader)
{
	//memcpy(mpShader, psShader, sizeof(PixelShader));
	mpShader = psShader;
}
