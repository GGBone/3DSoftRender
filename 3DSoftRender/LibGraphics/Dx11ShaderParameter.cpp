#include "GraphicsPCH.h"
#include "Dx11ShaderParameter.h"
#include "Dx11ConstantBuffer.h"
#include "Dx11StructureBuffer.h"
#include "Dx11SamplerState.h"
#include "RWBuffer.h"
using namespace Hikari;

Hikari::ShaderParameterDx::ShaderParameterDx()
	:m_uiSlot(UINT_MAX),
	m_ParameterType(Type::Invalid),
	mTexture(nullptr),
	mSamplerState(nullptr),
	mConstantBuffer(nullptr),
	mStructuredBuffer(nullptr)
{

}

Hikari::ShaderParameterDx::ShaderParameterDx(const std::string & name, UINT slotID, Shader::ShaderType shaderType, Type parameterType)
	:
	mName(name),
	m_uiSlot(slotID),
	m_ShaderType(shaderType),
	m_ParameterType(parameterType),
	mTexture(nullptr),
	mSamplerState(nullptr),
	mConstantBuffer(nullptr),
	mStructuredBuffer(nullptr),
	mRWBuffer(nullptr)
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

void Hikari::ShaderParameterDx::Bind()
{
	
	if(mConstantBuffer)
		mConstantBuffer->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
	if (mTexture)
		mTexture->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
	if(mSamplerState)
		mSamplerState->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
	if(mStructuredBuffer)
		mStructuredBuffer->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
	if (mRWBuffer)
		mRWBuffer->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
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
	if (mRWBuffer)
		mRWBuffer->Bind(m_uiSlot, m_ShaderType, m_ParameterType);
}

void Hikari::ShaderParameterDx::SetConstantBuffer(ConstantBuffer * constantBuffer)
{
	mConstantBuffer = constantBuffer;
}

void Hikari::ShaderParameterDx::SetTexture(Texture * texture)
{
	mTexture = texture;
}

void Hikari::ShaderParameterDx::SetSampler(SamplerState * sampler)
{
	mSamplerState = sampler;
}

void Hikari::ShaderParameterDx::SetStructuredBuffer(StructuredBuffer * rwBuffer)
{
	mStructuredBuffer = rwBuffer;
}

void Hikari::ShaderParameterDx::SetRWBuffer(RWBuffer * rwBuffer)
{
	mRWBuffer = rwBuffer;
}
