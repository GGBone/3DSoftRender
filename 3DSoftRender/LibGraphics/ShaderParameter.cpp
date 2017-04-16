#include "ShaderParameter.h"
using namespace Hikari;
bool ShaderParameter::IsValid() const
{
	return false;
}

template<>
void ShaderParameter::Set<ConstantBuffer>(ConstantBuffer* value)
{
	SetConstantBuffer(value);
}

template<>
void ShaderParameter::Set<Texture>(Texture* value)
{
	SetTexture(value);
}

template<>
void ShaderParameter::Set<SamplerState>(SamplerState* value)
{
	SetSampler(value);
}

template<>
void ShaderParameter::Set<StructuredBuffer>(StructuredBuffer* value)
{
	SetStructuredBuffer(value);
}
