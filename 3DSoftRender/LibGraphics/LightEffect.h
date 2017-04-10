#pragma once
#include "GraphicsLib.h"
#include "VisualEffectInstance.h"
#include "ShaderVMatrix.h"
#include "ShaderMMatrix.h"
#include "ShaderPMatrix.h"
namespace Hikari
{
	class LightEffect :public VisualEffect
	{
	public:
		LightEffect();
		virtual ~LightEffect();

		VisualEffectInstance* CreateInstance() const;
	};
}