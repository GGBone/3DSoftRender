#pragma once
#include "GraphicsLib.h"
#include "Object.h"

namespace Hikari
{
	class Visual;
	class ConstantBuffer;
	class SamplerState;
	class StructuredBuffer;
	class Texture;
	class RWBuffer;
	class ShaderParameter : public Object
	{
		
	public:
		enum class Type
		{
			Invalid,
			Texture,
			Sampler,
			Buffer,
			RWTexture,
			RWBuffer
		};

		template <typename T>
		void Set(T* value);

		template <typename T>
		T* GetType() const;

		virtual Type GetType() const = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual bool IsValid() const;

		friend class Buffer;
	protected:
		virtual void SetConstantBuffer(ConstantBuffer* constantBuffer) = 0;
		virtual void SetTexture(Texture* texture) = 0;
		virtual void SetSampler(SamplerState* sampler) = 0;
		virtual void SetStructuredBuffer(StructuredBuffer* rwBuffer) = 0;
		virtual void SetRWBuffer(RWBuffer* rwBuffer) = 0;
	};

	template<>
	void ShaderParameter::Set<ConstantBuffer>(ConstantBuffer* value);

	template<>
	void ShaderParameter::Set<Texture>(Texture* value);

	template<>
	void ShaderParameter::Set<SamplerState>(SamplerState* value);

	template<>
	void ShaderParameter::Set<StructuredBuffer>(StructuredBuffer* value);

	template<>
	void ShaderParameter::Set<RWBuffer>(RWBuffer* value);

	template<>
	void ShaderParameter::Set<ID3D11UnorderedAccessView>(ID3D11UnorderedAccessView* value);

	template<typename T>
	void ShaderParameter::Set(T* value)
	{
		//BOOST_STATIC_ASSERT_MSG(false, "This function must be specialized.");
	}
}