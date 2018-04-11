#include "Graphics\GraphicsPCH.h"
#include "Graphics\RenderTarget.h"
#include "Graphics\Texture.h"

#include "ClearRenderTargetPass.h"
using namespace Hikari;
ClearRenderTargetPass::ClearRenderTargetPass(std::shared_ptr<RenderTarget> renderTarget, ClearFlags clearFlags, const Float4& color, float depth, uint8_t stencil)
	: m_RenderTarget(renderTarget)
	, m_ClearFlags(clearFlags)
	, m_ClearColor(color)
	, m_ClearDepth(depth)
	, m_ClearStencil(stencil)
	, m_Texture(nullptr)
{}

ClearRenderTargetPass::ClearRenderTargetPass(std::shared_ptr<Texture> texture, ClearFlags clearFlags, const Float4& color, float depth, uint8_t stencil)
	: m_Texture(texture)
	, m_ClearFlags(clearFlags)
	, m_ClearColor(color)
	, m_ClearDepth(depth)
	, m_ClearStencil(stencil)
	, m_RenderTarget(nullptr)
{}

ClearRenderTargetPass::~ClearRenderTargetPass()
{}


void ClearRenderTargetPass::Render(RenderEventArgs& e)
{
	//e.PipelineState = nullptr;
	if (m_RenderTarget)
	{
		m_RenderTarget->Clear(m_ClearFlags, m_ClearColor, m_ClearDepth, m_ClearStencil);
	}
	if (m_Texture)
	{
		m_Texture->Clear(m_ClearFlags, m_ClearColor, m_ClearDepth, m_ClearStencil);
	}
}
