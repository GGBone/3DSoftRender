#include <GraphicsPCH.h>
#include <Renderer/Renderer.h>

using namespace Hikari;

template <>
std::shared_ptr<VertexIndexBuffer> Renderer::CreateIndexBuffer<std::vector<unsigned int>>(
	const std::vector<unsigned int>& data)
{
	return CreateUIntIndexBuffer(&(data[0]), static_cast<unsigned int>(data.size()));
}

template <>
std::shared_ptr<VertexIndexBuffer> Renderer::CreateVertexBuffer<std::vector<unsigned int>>(
	const std::vector<unsigned int>& data)
{
	return CreateUINTVertexBuffer(&data[0], static_cast<unsigned int>(data.size()), sizeof(UINT));
}


void Renderer::OnLoadingProgress(ProgressEventArgs& e)
{
	mLoadingProgress(e);
}
