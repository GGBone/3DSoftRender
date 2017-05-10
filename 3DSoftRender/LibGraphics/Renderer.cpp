#include "GraphicsPCH.h"
#include "Renderer.h"

using namespace Hikari;


void Hikari::Renderer::Terminate()
{
}

inline int Hikari::Renderer::GetWidth() const
{
	return mWidth;
}

inline int Hikari::Renderer::GetHeight() const
{
	return mHeight;
}


inline int Hikari::Renderer::GetNumMultisamples() const
{
	return mNumMultisamples;
}


void Hikari::Renderer::Draw(const Visual * visual, VisualEffect* effect)
{

	DrawPrimitive(visual, effect);
}
Hikari::Renderer::Renderer(RendererData* data)
{
	mData = data;
	mWidth = data->mWidth;
	mHeight = data->mHeight;
}


inline const HMatrix & Hikari::Renderer::GetViewMatrix() const
{
	// TODO: 在此处插入 return 语句
}

inline const HMatrix & Hikari::Renderer::GetProjectionMatrix() const
{
	// TODO: 在此处插入 return 语句
}

inline const HMatrix & Hikari::Renderer::GetPostProjectionMatrix() const
{
	// TODO: 在此处插入 return 语句
}

bool Hikari::Renderer::GetPickRay(int x, int y, APoint & origin, AVector & direction) const
{
	return false;
}

inline void Renderer::SetClearColor(const Float4 & color)
{
	mClearColor = color;
}

inline const Float4 & Hikari::Renderer::GetClearColor() const
{
	// TODO: 在此处插入 return 语句
}



template<>
Buffer* Renderer::CreateIndexBuffer< std::vector<unsigned int> >(const std::vector<unsigned int>& data)
{
	return CreateUIntIndexBuffer(&(data[0]), (unsigned int)data.size());
}

template<>
Buffer* Renderer::CreateVertexBuffer< std::vector<unsigned int> >(const std::vector<unsigned int>& data)
{
	return CreateUINTVertexBuffer(&data[0], (unsigned int)data.size(),sizeof(UINT));
}