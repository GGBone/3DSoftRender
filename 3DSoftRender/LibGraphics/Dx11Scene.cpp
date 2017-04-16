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
	return m_Renderer->CreateFloatVertexBuffer(data, count, stride);

}

Buffer * Hikari::SceneDX11::CreateUIntIndexBuffer(const unsigned int * data, unsigned int count) const
{
	return m_Renderer->CreateUIntIndexBuffer(data, count);

}

Mesh * Hikari::SceneDX11::CreateMesh() const
{
	return m_Renderer->CreateMesh();
}

Material * Hikari::SceneDX11::CreateMaterial() const
{
	return m_Renderer->CreateMaterial();

}

Texture * Hikari::SceneDX11::CreateTexture(const std::string & fileName) const
{
	return m_Renderer->CreateTexture(fileName);

}

Texture * Hikari::SceneDX11::CreateTexture2D(uint16_t width, uint16_t height)
{
	return m_Renderer->CreateTexture2D(width, height);

}

Texture * Hikari::SceneDX11::GetDefaultTexture()
{
	return m_Renderer->GetDefaultTexture();

}


