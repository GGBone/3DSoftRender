#pragma once
#include "GraphicsLib.h"
#include "VisualEffectInstance.h"
#include "ShaderVMatrix.h"
#include "ShaderMMatrix.h"
#include "ShaderPMatrix.h"
namespace Hikari
{
	class DefaultEffect:public VisualEffect
	{
	public:
		DefaultEffect();
		virtual ~DefaultEffect();

		VisualEffectInstance* CreateInstance() const;
	};
}