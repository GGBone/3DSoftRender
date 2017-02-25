#include "PixelShader.h"
using namespace Hikari;

IMPLEMENT_DEFAULT_NAMES(Shader, PixelShader);
IMPLEMENT_RTTI(Hikari, Shader, PixelShader);
Hikari::PixelShader::PixelShader(const std::string& programName, int numInput, int numOutput, int numConstant, int numSampler, bool profileOwner)
	:Shader(programName,numInput,numOutput,numConstant,numSampler,profileOwner)
{
	mprogramName = programName;
}

std::string Hikari::PixelShader::GetProgramName() const
{
	return mprogramName;
}
