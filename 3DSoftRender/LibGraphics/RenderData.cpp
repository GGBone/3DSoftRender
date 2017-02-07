#pragma once
#include "GraphicsPCH.h"
#include "RenderData.h"
using namespace Hikari;
Hikari::RendererData::RendererData(int width, int height, HWND handle)
:
	mWidth(width),
	mHeight(height),
	mHwnd(handle)
{
}

RendererData::~RendererData()
{

}