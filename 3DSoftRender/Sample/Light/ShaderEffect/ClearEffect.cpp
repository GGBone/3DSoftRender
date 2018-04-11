#include "Graphics\GraphicsPCH.h"
#include "ClearEffect.h"
#include "Graphics\Dx11RenderWindow.h"
#include "Graphics\VisualEffectInstance.h"
#include "OpaquePass.h"
#include "TransparentPass.h"

#include "Graphics\Scene.h"
#include "Graphics\RenderTarget.h"
#include "Graphics\PipelineState.h"
#include "Graphics\SamplerState.h"
#include "ClearRenderTargetPass.h"
#include "LightPass.h"
#include "Graphics\BlendState.h"
#include "Graphics\DepthStencilState.h"

using namespace Hikari;
Hikari::ClearEffect::ClearEffect(std::shared_ptr<RenderWindow> rWindow, std::shared_ptr<Renderer> renderer)
{
	std::shared_ptr<ClearRenderTargetPass> clearPass;
	clearPass = std::make_shared<ClearRenderTargetPass>(rWindow->GetRenderTarget(), ClearFlags::All, Float4(0.f, 0.0f, 0.0f, 0.0f));
	std::shared_ptr<VisualTechnique> mTechnique = std::make_shared<VisualTechnique>();

	mTechnique->AddPass(clearPass);
	InsertTechnique(mTechnique);

}

Hikari::ClearEffect::~ClearEffect()
{
}

std::shared_ptr<VisualEffectInstance> Hikari::ClearEffect::CreateInstance()
{
	std::shared_ptr<VisualEffectInstance> instance = std::make_shared<VisualEffectInstance>(shared_from_this(), 0);
	return instance;
}
