#include "GraphicsPCH.h"
#define ENABLE_BOOST
#include "Dx11Scene.h"
#undef ENABLE_BOOST
#include "Dx11Renderer.h"

using namespace Hikari;

SceneDX11::SceneDX11(const std::shared_ptr<DirectRenderer>& render)
	: SceneBase()
{
	m_Renderer = render;
}

SceneDX11::~SceneDX11()
{
	m_Renderer.reset();
}

std::shared_ptr<VertexIndexBuffer> SceneDX11::CreateFloatVertexBuffer(const float* data, unsigned int count,
                                                                      unsigned int stride) const
{
	return m_Renderer->CreateFloatVertexBuffer(data, count, stride);
}

std::shared_ptr<VertexIndexBuffer> SceneDX11::CreateUIntIndexBuffer(const unsigned int* data, unsigned int count) const
{
	return m_Renderer->CreateUIntIndexBuffer(data, count);
}

std::shared_ptr<Mesh> SceneDX11::CreateMesh() const
{
	return m_Renderer->CreateMesh();
}

std::shared_ptr<Material> SceneDX11::CreateMaterial() const
{
	return m_Renderer->CreateMaterial();
}

std::shared_ptr<Texture> SceneDX11::CreateTexture(const std::wstring& fileName) const
{
	return m_Renderer->CreateTexture(fileName);
}

std::shared_ptr<Texture> SceneDX11::CreateTexture2D(uint16_t width, uint16_t height)
{
	return m_Renderer->CreateTexture2D(width, height);
}

std::shared_ptr<Texture> SceneDX11::GetDefaultTexture()
{
	return m_Renderer->GetDefaultTexture();
}
