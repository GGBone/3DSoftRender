#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\ShaderVMatrix.h"
#include "Graphics\ShaderMMatrix.h"
#include "Graphics\ShaderPMatrix.h"
#include "Loader\ConfigurationSetting.h"
namespace Hikari
{
	class RenderWindow;
	class LightEffect :public VisualEffect,public std::enable_shared_from_this<LightEffect>
	{
	public:
		
		LightEffect(std::shared_ptr<RenderWindow> rWindow,std::shared_ptr<Renderer> renderer,std::shared_ptr<Scene> scene, std::vector<Light>& light);
		virtual ~LightEffect();

		std::shared_ptr<VisualEffectInstance> CreateInstance() override;

	};
}