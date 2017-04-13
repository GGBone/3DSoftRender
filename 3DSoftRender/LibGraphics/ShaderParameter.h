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
	class ShaderParameter : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
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

		virtual bool IsValid() const
		{
			return false;
		}
		friend class Buffer;
	protected:
		virtual void SetConstantBuffer(ConstantBuffer* constantBuffer) = 0;
		virtual void SetTexture(Texture* texture) = 0;
		virtual void SetSampler(SamplerState* sampler) = 0;
		virtual void SetStructuredBuffer(StructuredBuffer* rwBuffer) = 0;
	};
	typedef ShaderParameter* ShaderParameterPtr;


}