#include "Graphics\GraphicsPCH.h"
#include "Graphics\Renderer.h"

using namespace Hikari;




template<>
std::shared_ptr<Buffer> Renderer::CreateIndexBuffer< std::vector<unsigned int> >(const std::vector<unsigned int>& data)
{
	return CreateUIntIndexBuffer(&(data[0]), (unsigned int)data.size());
}

template<>
std::shared_ptr<Buffer> Renderer::CreateVertexBuffer< std::vector<unsigned int> >(const std::vector<unsigned int>& data)
{
	return CreateUINTVertexBuffer(&data[0], (unsigned int)data.size(),sizeof(UINT));
}



void Hikari::Renderer::OnLoadingProgress(ProgressEventArgs & e)
{
	mLoadingProgress(e);
}
