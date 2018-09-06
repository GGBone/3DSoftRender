#pragma once
#include "Object.h"
#include "Resource/CPUAccess.h"
#include <Shader/Shader.h>
#include <boost/static_assert.hpp>

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
		enum class ShaderInputType
		{
			Invalid,
			Texture,
			Sampler,
			StructuredBuffer,
			ConstantBuffer,
			UnorderedBuffer,
			Buffer
		};

		enum class BindFlags
		{
			Invalid,
		};

		enum class Dimension
		{
			Invalid,
			Buffer,
			TEXTURE1D,
			TEXTURE1DARRAY,
			TEXTURE2D,
			TEXTURE2DARRAY,
			TEXTURE3D
		};

		enum class ReturnType
		{
			Invalid,
		};

		enum class Format
		{
			UNKNOWN = 0,
			R32_SINT,
			//Will be expend
		};

		enum class AppendFlag
		{
			//Only UAV
			RAW = 0,
			APPEND,
			COUNTER
		};

		struct ShaderInputParameter
		{
			ShaderInputType m_parameterType;
			AppendFlag m_appendFlag;
			Format m_format;
			CPUAccess m_cpuAccess;
			GPUAccess m_gpuAccess;
			UINT m_uiBindPoint;
			UINT m_uiBindCount;
			BindFlags m_bindFlags;
			Dimension m_dimension;
			ReturnType m_retureType;
		};

	public:
		virtual ~ShaderParameter() = default;
		template <typename T>
		void set(std::shared_ptr<T> value);

		/*template <typename T>
		std::shared_ptr<T> get_type() const;*/

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual bool is_valid() const;

		ShaderInputParameter GetShaderInputParamenter() const { return m_shader_input_parameter_; }
		friend class BufferBase;
	protected:
		ShaderParameter() = default;
		virtual void SetConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer);
		virtual void SetTexture(std::shared_ptr<Texture> texture);
		virtual void SetSampler(std::shared_ptr<SamplerState> sampler);
		virtual void SetStructuredBuffer(std::shared_ptr<StructuredBuffer> rwBuffer);
		virtual void SetBuffer(std::shared_ptr<Buffer> rwBuffer);

	protected:
		ShaderInputParameter m_shader_input_parameter_;

		std::string m_sName{};

		std::shared_ptr<Texture> m_texture{};
		std::shared_ptr<SamplerState> m_samplerState{};
		std::shared_ptr<ConstantBuffer> m_constantBuffer{};
		std::shared_ptr<StructuredBuffer> m_structuredBuffer{};
		std::shared_ptr<Buffer> m_buffer{};

		UINT m_ui_slot_{};
		Shader::ShaderType m_shader_type_;
	};

	template <>
	void ShaderParameter::set<ConstantBuffer>(std::shared_ptr<ConstantBuffer> value);

	template <>
	void ShaderParameter::set<Texture>(std::shared_ptr<Texture> value);

	template <>
	void ShaderParameter::set<SamplerState>(std::shared_ptr<SamplerState> value);

	template <>
	void ShaderParameter::set<StructuredBuffer>(std::shared_ptr<StructuredBuffer> value);

	template <>
	void ShaderParameter::set<Buffer>(std::shared_ptr<Buffer> value);

	template <typename T>
	void ShaderParameter::set(std::shared_ptr<T> value)
	{
		BOOST_STATIC_ASSERT_MSG(false, "This function must be specialized.");
	}
}
