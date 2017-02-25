#include "ShaderParameters.h"
using namespace Hikari;

IMPLEMENT_DEFAULT_NAMES(Object, ShaderParameters);
IMPLEMENT_RTTI(Hikari, Object, ShaderParameters);
Hikari::ShaderParameters::ShaderParameters(Shader * shader)
	:mShader(shader)
{
	mNumConstants = mShader->GetNumConstants();
	if (mNumConstants > 0)
	{
		mConstants = new ShaderFloat*[mNumConstants];
		for (int i = 0; i < mNumConstants; ++i)
		{
			mConstants[i] = new ShaderFloat();
		}
	}
	else
		mNumConstants = 0;
}

Hikari::ShaderParameters::~ShaderParameters()
{
}

void Hikari::ShaderParameters::SetConstant(int handle, ShaderFloat* sfFloat)
{
	if (0 <= handle && handle <= mNumConstants)
	{
		mConstants[handle] = sfFloat;
	}
		
}

int Hikari::ShaderParameters::SetConstant(const std::string & name, ShaderFloat * sfloat)
{
	for (int i = 0; i < mNumConstants; ++i)
	{
		if (mShader->GetConstantName(i) == name)
		{
			mConstants[i] = sfloat;
			return i;
		}
	}
	return 0;
}

ShaderFloat * Hikari::ShaderParameters::GetConstant(int handle) const
{
	return mConstants[handle];
}

void Hikari::ShaderParameters::UpdateConstants(const Visual * visual, const Camera * camera)
{
	ShaderFloatPtr* constants = mConstants;
	for (int i = 0; i < mNumConstants; ++i, ++constants)
	{
		ShaderFloat* constant = *constants;
		constant->Update(visual, camera);
	}
}