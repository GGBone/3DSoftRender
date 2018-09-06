#include "GraphicsPCH.h"
#include "ShaderParameter.h"
#include "Resource/StructuredBuffer.h"
using namespace Hikari;

bool ShaderParameter::is_valid() const
{
	return false;
}

template <>
void ShaderParameter::set<ConstantBuffer>(std::shared_ptr<ConstantBuffer> value)
{
	SetConstantBuffer(value);
}

template <>
void ShaderParameter::set<Texture>(std::shared_ptr<Texture> value)
{
	SetTexture(value);
}

template <>
void ShaderParameter::set<SamplerState>(std::shared_ptr<SamplerState> value)
{
	SetSampler(value);
}

template <>
void ShaderParameter::set<StructuredBuffer>(std::shared_ptr<StructuredBuffer> value)
{
	SetStructuredBuffer(value);
}

template <>
void ShaderParameter::set<Buffer>(std::shared_ptr<Buffer> value)
{
	SetBuffer(value);
}


void ShaderParameter::SetConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer)
{
	m_constantBuffer = constantBuffer;
}

void ShaderParameter::SetTexture(std::shared_ptr<Texture> texture)
{
	m_texture = texture;
}

void ShaderParameter::SetSampler(std::shared_ptr<SamplerState> sampler)
{
	m_samplerState = sampler;
}

void ShaderParameter::SetStructuredBuffer(std::shared_ptr<StructuredBuffer> rwBuffer)
{
	if(m_shader_input_parameter_.m_gpuAccess < rwBuffer->m_shader_input_param_.m_gpuAccess)
	{
		rwBuffer->m_shader_input_param_.m_gpuAccess = m_shader_input_parameter_.m_gpuAccess;
	}
	m_structuredBuffer = rwBuffer;
}

void ShaderParameter::SetBuffer(std::shared_ptr<Buffer> byteBuffer)
{
	m_buffer = byteBuffer;
}
