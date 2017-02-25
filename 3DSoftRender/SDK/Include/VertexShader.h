#pragma once
#include "GraphicsLib.h"
#include "Shader.h"
namespace Hikari
{
	class VertexShader : public Shader 
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		VertexShader(const std::string& programName,int numinput,int numOutput,int numConstant,int numSampler,bool owner);
		std::string GetProgramName()const;
	private:
		std::string mprogramName;
	};
	typedef VertexShader* VertexShaderPtr;
}