#pragma once
#include "GraphicsLib.h"
#include "Shader.h"
namespace Hikari
{
	class PixelShader :  public Shader
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		PixelShader(const std::string& programName,int numInput,int numOutput,int numConstant,int numSampler,bool profileOwner);
		std::string GetProgramName()const;
	private:
		std::string mprogramName;
	};
	typedef PixelShader* PixelShaderPtr;
}