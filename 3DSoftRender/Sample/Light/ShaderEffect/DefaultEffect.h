#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\VisualEffectInstance.h"
#include "Graphics\ShaderVMatrix.h"
#include "Graphics\ShaderMMatrix.h"
#include "Graphics\ShaderPMatrix.h"
#include "Graphics\Dx11Renderer.h"
namespace Hikari
{
	class DefaultEffect:public VisualEffect
	{
	public:
		DefaultEffect(DirectRenderer* renderer);
		virtual ~DefaultEffect();

		std::shared_ptr<VisualEffectInstance> CreateInstance() override;
	};
}