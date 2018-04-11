#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11Scene.h"

using namespace Hikari;
Hikari::SceneDX11::SceneDX11(std::shared_ptr<DirectRenderer> render)
{
	m_Renderer = render;
	m_pDevice = render->GetDevice();
	m_pContext = render->GetDeviceContext();
}

Hikari::SceneDX11::~SceneDX11()
{
	
}

std::shared_ptr<Buffer> Hikari::SceneDX11::CreateFloatVertexBuffer(const float * data, unsigned int count, unsigned int stride) const
{
	return m_Renderer->CreateFloatVertexBuffer(data, count, stride);

}

std::shared_ptr<Buffer> Hikari::SceneDX11::CreateUIntIndexBuffer(const unsigned int * data, unsigned int count) const
{
	return m_Renderer->CreateUIntIndexBuffer(data, count);

}

std::shared_ptr<Mesh> Hikari::SceneDX11::CreateMesh() const
{
	return m_Renderer->CreateMesh();
}

std::shared_ptr<Material> Hikari::SceneDX11::CreateMaterial() const
{
	return m_Renderer->CreateMaterial();

}

std::shared_ptr<Texture> Hikari::SceneDX11::CreateTexture(const std::wstring & fileName) const
{
	return m_Renderer->CreateTexture(fileName);

}

std::shared_ptr<Texture> Hikari::SceneDX11::CreateTexture2D(uint16_t width, uint16_t height)
{
	return m_Renderer->CreateTexture2D(width, height);

}

std::shared_ptr<Texture> Hikari::SceneDX11::GetDefaultTexture()
{
	return m_Renderer->GetDefaultTexture();

}


