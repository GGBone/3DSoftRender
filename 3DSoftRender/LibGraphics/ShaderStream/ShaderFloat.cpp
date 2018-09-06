#include "GraphicsPCH.h"
#include "ShaderFloat.h"
using namespace Hikari;

ShaderFloat::ShaderFloat()
	: mNumElement(0),
	  mData(nullptr),
	  mAllowUpdater(false)
{
}

ShaderFloat::ShaderFloat(int numRegisters)
	: mNumElement(numRegisters),
	  mData(nullptr),
	  mAllowUpdater(false)
{
}

ShaderFloat::~ShaderFloat()
= default;

void ShaderFloat::SetNumRegisters(int numRegisters)
{
	mNumElement = numRegisters;
}

void ShaderFloat::Update(const Visual*, const Camera*)
{
}

void ShaderFloat::SetRegister(int i, const float* data)
{
	float* target = (mData + 4 * i);
	*target++ = *data++;
	*target++ = *data++;
	*target++ = *data++;
	*target = *data;
}

void ShaderFloat::SetRegisters(const float* data)
{
}

float* ShaderFloat::GetRegister(int i)
{
	return nullptr;
}
