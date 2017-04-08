#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Shader.h"
#include "ShaderFloat.h"
#include "Camera.h"
namespace Hikari
{
	class Visual;
	class Camera4DV1;
	class ShaderFloat; 
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
		void UpdateConstants(const Visual * visual, const Camera4DV1 * camera);
	private:
		Shader* mShader;
		int mNumConstants;
		ShaderFloat** mConstants;
	};
	typedef ShaderParameters* ShaderParametersPtr;
}