#pragma once
#include "GraphicsLib.h"
#include "Object.h"
namespace Hikari
{
	class ShaderParameters : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	};
	typedef ShaderParameters* ShaderParametersPtr;
}