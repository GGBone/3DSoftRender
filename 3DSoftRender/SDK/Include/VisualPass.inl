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
