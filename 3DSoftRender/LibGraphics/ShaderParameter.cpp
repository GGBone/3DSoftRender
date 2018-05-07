#include "Graphics\GraphicsPCH.h"
#include "Graphics\ShaderParameter.h"
using namespace Hikari;
bool ShaderParameter::IsValid() const
{
	return false;
}

template<>
void ShaderParameter::Set<ConstantBuffer>(std::shared_ptr<ConstantBuffer> value)
{
	SetConstantBuffer(value);
}

template<>
void ShaderParameter::Set<Texture>(std::shared_ptr<Texture> value)
{
	SetTexture(value);
}

template<>
void ShaderParameter::Set<SamplerState>(std::shared_ptr<SamplerState> value)
{
	SetSampler(value);
}

template<>
void ShaderParameter::Set<StructuredBuffer>(std::shared_ptr<StructuredBuffer> value)
{
	SetStructuredBuffer(value);
}

template<>
void ShaderParameter::Set<Buffer>(std::shared_ptr<Buffer> value)
{
	SetBuffer(value);
}