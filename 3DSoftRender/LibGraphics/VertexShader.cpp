#include "GraphicsPCH.h"
#include "VertexShader.h"
using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, VertexShader);
IMPLEMENT_DEFAULT_NAMES(Object, VertexShader);
Hikari::VertexShader::VertexShader(const std::string& programName, int numinput, int numOutput, int numConstant, int numSampler, bool owner)
	:Shader(programName,numinput,numOutput,numConstant,numSampler,owner)
{
	mprogramName = programName;
}

std::string Hikari::VertexShader::GetProgramName() const
{
	return mprogramName;
}
