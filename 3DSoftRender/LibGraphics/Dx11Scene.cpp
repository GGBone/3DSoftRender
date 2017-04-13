#include "GraphicsPCH.h"
#include "Dx11Scene.h"

using namespace Hikari;
Hikari::SceneDX11::SceneDX11(DirectRenderer * render)
{
	m_Renderer = render;
	m_pDevice = render->mData->mDevice;
	m_pContext = render->mData->mImmediateContext;
}

Hikari::SceneDX11::~SceneDX11()
{
}

Buffer * Hikari::SceneDX11::CreateFloatVertexBuffer(const float * data, unsigned int count, unsigned int stride) const
{
	return ;
}

Buffer * Hikari::SceneDX11::CreateUIntIndexBuffer(const unsigned int * data, unsigned int count) const
{
	return nullptr;
}

Mesh * Hikari::SceneDX11::CreateMesh() const
{
	return nullptr;
}

Material * Hikari::SceneDX11::CreateMaterial() const
{
	return nullptr;
}

Texture * Hikari::SceneDX11::CreateTexture(const std::wstring & fileName) const
{
	return nullptr;
}

Texture * Hikari::SceneDX11::CreateTexture2D(uint16_t width, uint16_t height)
{
	return nullptr;
}

Texture * Hikari::SceneDX11::GetDefaultTexture()
{
	return nullptr;
}


