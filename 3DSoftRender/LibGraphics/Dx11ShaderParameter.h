#pragma once
#include "ShaderParameter.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "StructBuffer.h"
namespace Hikari
{
	class ShaderParameterDx : public ShaderParameter
	{
	public:
		ShaderParameterDx();
		ShaderParameterDx(const std::string& name, UINT slotID, Shader::ShaderType shaderType, Type parameterType);
		bool IsValid() const override;
		virtual Type GetType()const;
		virtual void Bind() override;
		virtual void UnBind() override;

	protected:
		virtual void SetConstantBuffer(ConstantBuffer* constantBuffer) override;
		virtual void SetTexture(Texture* texture) override;
		virtual void SetSampler(SamplerState* sampler) override;
		virtual void SetStructuredBuffer(StructuredBuffer* rwBuffer) override;
		virtual void SetRWBuffer(RWBuffer* rwBuffer) override;
	private:
		std::string mName;
		Texture* mTexture;
		SamplerState* mSamplerState;
		ConstantBuffer* mConstantBuffer;
		StructuredBuffer* mStructuredBuffer;
		RWBuffer* mRWBuffer;
		UINT m_uiSlot;
		Shader::ShaderType m_ShaderType;
		Type m_ParameterType;

	};
}