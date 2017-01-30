#include "PixelShader.h"
using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, PixelShader);
IMPLEMENT_DEFAULT_NAMES(Object, PixelShader);
Hikari::PixelShader::PixelShader(const std::string & programName)
{
	mprogramName = programName;
}

std::string Hikari::PixelShader::GetProgramName() const
{
	return mprogramName;
}
