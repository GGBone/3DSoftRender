#include "GraphicsPCH.h"
#include "Renderer.h"

using namespace Hikari;

void Hikari::Renderer::Initialize(int width, int height, Texture::TextureFormat colorFormat, Texture::TextureFormat depthStencilFormat, int numMultisamples)
{
	mWidth = width;
	mHeight = height;
	mColorFormat = colorFormat;
	mDepthStencilFormat = depthStencilFormat;
	mNumMultisamples = numMultisamples;


}

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


void Hikari::Renderer::Draw(const Visual * visual, const VisualEffectInstance* instance)
{
	//const VertexFormat* vFormat = visual->GetVertexFormat();
	//const VertexBuffer* vBuffer = visual->GetVertexBuffer();
	//const IndexBuffer* iBuffer = visual->GetIndexBuffer();
	//Enable(vBuffer);
	//Enable(iBuffer);

	//const int numPasses = instance->GetNumPasses();
	//for (int i = 0; i < numPasses; ++i)
	//{
	//	const VisualPass* pass = instance->GetPass(i);
	//	ShaderParameter* vParam = instance->GetVertexShaderParam(i);
	//	ShaderParameter* pParam = instance->GetPixelShaderParam(i);
	//	VertexShader* vShader = pass->GetVertexShader();
	//	PixelShader* pShader = pass->GetPixelShader();
	//	//ShaderParamter vParam
	//	vParam->UpdateConstants(visual, mCamera);
	//	pParam->UpdateConstants(visual, mCamera);

	//	//Enable shaders
	//	Enable(vShader, vParam);
	//	Enable(pShader, pParam);

	//	DrawPrimitive(visual);
	//}
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

