#pragma once
#include "Graphics\ShaderParameter.h"
#include "Graphics\ConstantBuffer.h"
#include "Graphics\Shader.h"
#include "Graphics\StructBuffer.h"
#include "Graphics\RWBuffer.h"
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
		virtual void SetConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer) override;
		virtual void SetTexture(std::shared_ptr<Texture> texture) override;
		virtual void SetSampler(std::shared_ptr<SamplerState> sampler) override;
		virtual void SetStructuredBuffer(std::shared_ptr<StructuredBuffer> rwBuffer) override;
		virtual void SetRWBuffer(std::shared_ptr<RWBuffer> rwBuffer) override;
	private:
		std::string mName;
		std::shared_ptr<Texture> mTexture;
		std::shared_ptr<SamplerState> mSamplerState;
		std::shared_ptr<ConstantBuffer> mConstantBuffer;
		std::shared_ptr<StructuredBuffer> mStructuredBuffer;
		std::shared_ptr<RWBuffer> mRWBuffer;
		UINT m_uiSlot;
		Shader::ShaderType m_ShaderType;
		Type m_ParameterType;

	};
}