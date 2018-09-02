#include "ClearEffect.h"

#include "ClearRenderTargetPass.h"
#include "Renderer/RenderWindow.h"
#include "SceneGraph/VisualEffectInstance.h"


using namespace Hikari;

ClearEffect::ClearEffect(std::shared_ptr<RenderWindow> rWindow, std::shared_ptr<Renderer> renderer)
{
	std::shared_ptr<ClearRenderTargetPass> clearPass;
	clearPass = std::make_shared<ClearRenderTargetPass>(rWindow->GetRenderTarget(), ClearFlags::All,
	                                                    Float4(0.f, 0.0f, 0.0f, 0.0f));
	std::shared_ptr<VisualTechnique> mTechnique = std::make_shared<VisualTechnique>();

	mTechnique->AddPass(clearPass);
	InsertTechnique(mTechnique);
}

ClearEffect::~ClearEffect()
= default;

std::shared_ptr<VisualEffectInstance> ClearEffect::CreateInstance()
{
	std::shared_ptr<VisualEffectInstance> instance = std::make_shared<VisualEffectInstance>(shared_from_this(), 0);
	return instance;
}
