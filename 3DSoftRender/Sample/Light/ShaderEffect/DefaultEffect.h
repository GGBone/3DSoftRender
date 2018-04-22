#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\VisualEffectInstance.h"
#include "Graphics\ShaderVMatrix.h"
#include "Graphics\ShaderMMatrix.h"
#include "Graphics\ShaderPMatrix.h"
#include "Graphics\Dx11Renderer.h"
namespace Hikari
{
	class Scene;
	class DefaultEffect:public VisualEffect,public enable_shared_from_this<DefaultEffect>
	{
	public:
		DefaultEffect(shared_ptr<Renderer> renderer,shared_ptr<Scene> scene);
		virtual ~DefaultEffect();

		std::shared_ptr<VisualEffectInstance> CreateInstance() override;
	};
}