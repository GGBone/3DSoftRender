#pragma once
#include "GraphicsLib.h"
#include "Object.h"
namespace Hikari
{
	class PixelShader : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		PixelShader(const std::string& programName);
		std::string GetProgramName()const;
	private:
		std::string mprogramName;
	};
	typedef PixelShader* PixelShaderPtr;
}