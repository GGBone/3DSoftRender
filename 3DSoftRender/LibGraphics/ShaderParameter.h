#pragma once
#include "Graphics\GraphicsLib.h"
#include "Core\Object.h"
namespace Hikari
{
	class Visual;
	class ConstantBuffer;
	class SamplerState;
	class StructuredBuffer;
	class Texture;
	class Buffer;
	class ShaderParameter : public Object
	{
		
	public:
		enum class Type
		{
			Invalid,
			Texture,
			Sampler,
			StructuredBuffer,
			ConstantBuffer,
			UnorderedBuffer,
			Buffer
		};
		enum class GPURW
		{
			Read = 1 << 0,
			Write = 1 <<1,
			ReadWrite = Read|Write
		};

		template <typename T>
		void Set(std::shared_ptr<T> value);

		template <typename T>
		std::shared_ptr<T> GetType() const;

		virtual Type GetType() const = 0;
		virtual GPURW GetRW()const { return GPURW::Read; };
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual bool IsValid() const;

		friend class Buffer;
	protected:
		virtual void SetConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer) = 0;
		virtual void SetTexture(std::shared_ptr<Texture> texture) = 0;
		virtual void SetSampler(std::shared_ptr<SamplerState> sampler) = 0;
		virtual void SetStructuredBuffer(std::shared_ptr<StructuredBuffer> rwBuffer) = 0;
		virtual void SetBuffer(std::shared_ptr<Buffer> rwBuffer) = 0;
	};

	template<>
	void ShaderParameter::Set<ConstantBuffer>(std::shared_ptr<ConstantBuffer> value);

	template<>
	void ShaderParameter::Set<Texture>(std::shared_ptr<Texture> value);

	template<>
	void ShaderParameter::Set<SamplerState>(std::shared_ptr<SamplerState> value);

	template<>
	void ShaderParameter::Set<StructuredBuffer>(std::shared_ptr<StructuredBuffer> value);

	template<>
	void ShaderParameter::Set<Buffer>(std::shared_ptr<Buffer> value);

	template<typename T>
	void ShaderParameter::Set(std::shared_ptr<T> value)
	{
		BOOST_STATIC_ASSERT_MSG(false, "This function must be specialized.");
	}
}