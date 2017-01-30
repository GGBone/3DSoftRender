#include "GraphicsPCH.h"
#include "VertexShader.h"
using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, VertexShader);
IMPLEMENT_DEFAULT_NAMES(Object, VertexShader);
Hikari::VertexShader::VertexShader(const std::string & programName)
{
	mprogramName = programName;
}

std::string Hikari::VertexShader::GetProgramName() const
{
	return mprogramName;
}
