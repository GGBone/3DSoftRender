#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Shader/Shader.h"
#include "Shader/ShaderParameter.h"

namespace Hikari
{
	class Float4;

	class SamplerState : public Object
	{
	public:
		enum MinFilter
		{
			MinNearest,
			MinLinear
		};

		enum MagFilter
		{
			MagNearest,
			MagLinear
		};

		enum MipFilter
		{
			MipNearest,
			MipLinear
		};

		enum WrapMode
		{
			Repeat,
			Mirror,
			Clamp,
			Border
		};

		enum CompareMode
		{
			Node,
			CompareRefToTexture
		};

		enum CompareFunc
		{
			Never,
			Less,
			Equal,
			LessEqual,
			Greater,
			NotEqual,
			GreaterEqual,
			Always
		};

		virtual void SetFilter(MinFilter minFilter, MagFilter magFilter, MipFilter mipFilter) = 0;
		virtual void GetFilter(MinFilter& minFilter, MagFilter& magFilter, MipFilter& mipFilter) const = 0;

		virtual void SetWrapMode(WrapMode u = Repeat, WrapMode v = Repeat, WrapMode w = Repeat) = 0;
		virtual void GetWrapMode(WrapMode& u, WrapMode& v, WrapMode& w) const = 0;

		virtual void SetCompareFunction(CompareFunc compareFunc) = 0;
		virtual CompareFunc GetCompareFunc() const = 0;

		virtual void SetLODBias(float lodBias) = 0;
		virtual float GetLODBias() const = 0;

		virtual void SetMinLOD(float minLOD) = 0;
		virtual float GetMinLOD() const = 0;

		virtual void SetMaxLOD(float maxLOD) = 0;
		virtual float GetMaxLOD() const = 0;

		virtual void SetBorderColor(const Float4& borderColor) = 0;
		virtual const Float4& GetBorderColor() const = 0;

		virtual void EnableAnisotropicFiltering(bool enabled) = 0;
		virtual bool IsAnisotropicFilteringEnabled() const = 0;

		virtual void SetMaxAnisotropy(uint8_t maxAnisotropy) = 0;
		virtual uint8_t GetMaxAnisotropy() const = 0;

		// Bind this sampler state to the ID for a specific shader type.
		virtual void bind(uint32_t ID, Shader::ShaderType shaderType) = 0;
		// Unbind the sampler state.
		virtual void unbind(uint32_t ID, Shader::ShaderType shaderType) = 0;
	};
}
