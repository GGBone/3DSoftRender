#pragma once
#include "GraphicsLib.h"
#include "VisualEffectInstance.h"
#include "ShaderVMatrix.h"
#include "ShaderMMatrix.h"
#include "ShaderPMatrix.h"
#include "Dx11Shader.h"
#include "ConfigurationSetting.h"
namespace Hikari
{
	class LightEffect :public VisualEffect
	{
	public:
		
		LightEffect(DirectRenderer* renderer,Scene* scene, std::vector<Light>& light);
		virtual ~LightEffect();
		VisualEffectInstance* CreateInstance() const;
	};
}