#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Shader.h"
#include "ShaderFloat.h"
namespace Hikari
{
	class ShaderParameters : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		ShaderParameters(Shader * shader);
		~ShaderParameters();

		void SetConstant(int handle, ShaderFloat* sfFloat);
		int SetConstant(const std::string & name, ShaderFloat * sfloat);
		ShaderFloat * GetConstant(int handle) const;
		void UpdateConstants(const Visual * visual, const Camera * camera);
	private:
		Shader* mShader;
		int mNumConstants;
		ShaderFloatPtr* mConstants;
	};
	typedef ShaderParameters* ShaderParametersPtr;
}