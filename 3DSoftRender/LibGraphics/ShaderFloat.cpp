#include "Graphics\GraphicsPCH.h"
#include "ShaderFloat.h"
using namespace Hikari;
Hikari::ShaderFloat::ShaderFloat()
	:mNumElement(0),
	mData(nullptr),
	mAllowUpdater(false)
{
}
Hikari::ShaderFloat::ShaderFloat(int numRegisters)
	: mNumElement(numRegisters),
	mData(nullptr),
	mAllowUpdater(false)
{
}
Hikari::ShaderFloat::~ShaderFloat()
{
}
void Hikari::ShaderFloat::SetNumRegisters(int numRegisters)
{
	mNumElement = numRegisters;
}

void Hikari::ShaderFloat::Update(const Visual*, const Camera *)
{

}

void Hikari::ShaderFloat::SetRegister(int i, const float * data)
{
	float* target = (mData + 4 * i);
	*target++ = *data++;
	*target++ = *data++;
	*target++ = *data++;
	*target = *data;
}

void Hikari::ShaderFloat::SetRegisters(const float * data)
{
}

float* Hikari::ShaderFloat::GetRegister(int i)
{
	return NULL;
}

