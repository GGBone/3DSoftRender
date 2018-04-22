#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\ShaderVMatrix.h"
#include "Graphics\ShaderMMatrix.h"
#include "Graphics\ShaderPMatrix.h"
#include "Loader\ConfigurationSetting.h"
namespace Hikari
{
	class RenderWindow;
	class LightEffect :public VisualEffect,public enable_shared_from_this<LightEffect>
	{
	public:
		
		LightEffect(std::shared_ptr<RenderWindow> rWindow,std::shared_ptr<Renderer> renderer, vector<std::shared_ptr<Scene>> scene,vector<shared_ptr<Scene>> transScene);
		virtual ~LightEffect();

		std::shared_ptr<VisualEffectInstance> CreateInstance() override;

	};
}