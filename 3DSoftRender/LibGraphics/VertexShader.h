#pragma once
#include "GraphicsLib.h"
#include "Object.h"
namespace Hikari
{
	class VertexShader : public Object 
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		VertexShader(const std::string& programName);
		std::string GetProgramName()const;
	private:
		std::string mprogramName;
	};
	typedef VertexShader* VertexShaderPtr;
}