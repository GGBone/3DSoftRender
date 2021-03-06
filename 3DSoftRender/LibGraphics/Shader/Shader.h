#pragma once
#include "Core.h"
#include "Object.h"
#include "Algebra/Vector3.h"

namespace Hikari
{
	class ShaderParameter;
	class ConstantBuffer;

	class Shader : public Object
	{
	public:
		enum ShaderType
		{
			UnKnownShaderType = 0,
			VertexShader,
			TessellationControlShader,
			TessellationEvaluationShader,
			GeometryShader,
			PixelShader,
			ComputeShader
		};

		typedef std::map<std::string, std::string> ShaderMacros;

		ShaderType mShaderType = UnKnownShaderType;
		virtual ShaderType GetType() const = 0;
		virtual void LoadShaderFromString(ShaderType type, const std::string& source, const std::string& sourceFileName,
		                                  const ShaderMacros& shaderMacros, const std::string& entryPoint,
		                                  const std::string& profile) = 0;

		virtual bool LoadShaderFromFile(ShaderType type, const std::string& fileName, const ShaderMacros& shaderMacros,
		                                const std::string& entryPoint, const std::string& profile) = 0;

		virtual ShaderParameter& GetShaderParameterByName(const std::string& name) const = 0;

		virtual ShaderParameter& operator[](const std::string& name) const
		{
			return GetShaderParameterByName(name);
		}

		virtual std::string GetLatestProfile(ShaderType type) = 0;

		virtual void Bind() = 0;

		virtual void UnBind() = 0;

		virtual void Dispatch(const Vector3UI& numGroups) = 0;

		friend class BufferBase;
	};
}
