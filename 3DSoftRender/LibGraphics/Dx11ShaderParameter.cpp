#include "Graphics\GraphicsPCH.h"
#include "Graphics\Dx11ShaderParameter.h"
#include "Graphics\Dx11ConstantBuffer.h"
#include "Graphics\Dx11StructureBuffer.h"
#include "Graphics\Dx11SamplerState.h"
#include "Graphics\Buffer.h"
using namespace Hikari;

Hikari::ShaderParameterDx::ShaderParameterDx()
	:m_uiSlot(UINT_MAX),
	m_ParameterType(Type::Invalid),
	mTexture(nullptr),
	mSamplerState(nullptr),
	mConstantBuffer(nullptr),
	mStructuredBuffer(nullptr),
	mBuffer(nullptr),
	m_GpuAccess(GPURW::Read)
{

}

Hikari::ShaderParameterDx::ShaderParameterDx(const std::string & name, UINT slotID, Shader::ShaderType shaderType, Type parameterType,GPURW gpuAccess)
	:
	mName(name),
	m_uiSlot(slotID),
	m_ShaderType(shaderType),
	m_ParameterType(parameterType),
	m_GpuAccess(gpuAccess),
	mTexture(nullptr),
	mSamplerState(nullptr),
	mConstantBuffer(nullptr),
	mStructuredBuffer(nullptr),
	mBuffer(nullptr)
{
}

bool Hikari::ShaderParameterDx::IsValid() const
{
	return m_ParameterType != ShaderParameter::Type::Invalid;

}

ShaderParameter::Type Hikari::ShaderParameterDx::GetType() const
{
	return m_ParameterType;
}

ShaderParameter::GPURW Hikari::ShaderParameterDx::GetRW() const
{
	return m_GpuAccess;
}

void Hikari::ShaderParameterDx::Bind()
{
	
	if(mConstantBuffer)
		mConstantBuffer->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
	if (mTexture)
		mTexture->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
	if(mSamplerState)
		mSamplerState->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
	if(mStructuredBuffer)
		mStructuredBuffer->Bind(m_uiSlot, m_ShaderType, m_ParameterType,m_GpuAccess);
	if (mBuffer)
		mBuffer->Bind(m_uiSlot, m_ShaderType, m_ParameterType, m_GpuAccess);
}

void Hikari::ShaderParameterDx::UnBind()
{
	if (mConstantBuffer)
		mConstantBuffer->UnBind(m_uiSlot, m_ShaderType, m_ParameterType);
	if (mTexture)
		mTexture->UnBind(m_uiSlot, m_ShaderType, m_ParameterType);
	if (mSamplerState)
		mSamplerState->UnBind(m_uiSlot, m_ShaderType, m_ParameterType);
	if (mStructuredBuffer)
		mStructuredBuffer->UnBind(m_uiSlot, m_ShaderType, m_ParameterType);
	if (mBuffer)
		mBuffer->UnBind(m_uiSlot, m_ShaderType, m_ParameterType);
	mConstantBuffer = nullptr;
	mTexture = nullptr;
	mSamplerState = nullptr;
	mStructuredBuffer = nullptr;
	mBuffer = nullptr;
}

void Hikari::ShaderParameterDx::SetConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer)
{
	mConstantBuffer = constantBuffer;
}

void Hikari::ShaderParameterDx::SetTexture(std::shared_ptr<Texture> texture)
{
	mTexture = texture;
}

void Hikari::ShaderParameterDx::SetSampler(std::shared_ptr<SamplerState> sampler)
{
	mSamplerState = sampler;
}

void Hikari::ShaderParameterDx::SetStructuredBuffer(std::shared_ptr<StructuredBuffer> rwBuffer)
{
	mStructuredBuffer = rwBuffer;
}

void Hikari::ShaderParameterDx::SetBuffer(std::shared_ptr<Buffer> rwBuffer)
{
	mBuffer = rwBuffer;
}
