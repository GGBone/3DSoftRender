#pragma once
#include "GraphicsLib.h"
#include "VisualEffectInstance.h"
#include "ShaderVMatrix.h"
#include "ShaderMMatrix.h"
#include "ShaderPMatrix.h"
#include "Dx11Renderer.h"
namespace Hikari
{
	class DefaultEffect:public VisualEffect
	{
	public:
		DefaultEffect(DirectRenderer* renderer);
		virtual ~DefaultEffect();

		VisualEffectInstance* CreateInstance() const;
	};
}