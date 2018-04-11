#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\ShaderVMatrix.h"
#include "Graphics\ShaderMMatrix.h"
#include "Graphics\ShaderPMatrix.h"
#include "Loader\ConfigurationSetting.h"
namespace Hikari
{
	class RenderWindow;
	class ClearEffect :public VisualEffect, public std::enable_shared_from_this<ClearEffect>
	{
	public:

		ClearEffect(std::shared_ptr<RenderWindow> rWindow, std::shared_ptr<Renderer> renderer);
		virtual ~ClearEffect();

		std::shared_ptr<VisualEffectInstance> CreateInstance() override;

	};
}