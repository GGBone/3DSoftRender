#pragma once
#include "GraphicsLib.h"
#include "VisualEffect.h"
#include "ShaderParameters.h"
namespace Hikari
{
	class ShaderParameters;
	class ShaderFloat;
	class VisualEffectInstance
	{
	public:
		VisualEffectInstance(const VisualEffect* effect, int techniqueIndex);
		~VisualEffectInstance();
		const VisualPass* GetPass(int pass) const;
		ShaderParameters * GetVertexShaderParam(int pass) const;
		ShaderParameters * GetPixelShaderParam(int pass) const;
		int SetVertexConstant(int pass, const std::string & name, ShaderFloat * sfloat);
		int SetPixelConstant(int pass, const std::string & name, ShaderFloat * sfloat);
		void SetVertexConstant(int pass, int handle, ShaderFloat * sfloat);
		void SetPixelConstant(int pass, int handle, ShaderFloat * sfloat);
		inline int	GetNumPasses()const
		{
			return mNumPasses;
		}
	private:
		VisualEffect* mEffect;
		int mTechniqueIndex;
		int mNumPasses;
		ShaderParameters** mVertexParameters;
		ShaderParameters** mPixelParameters;
	};
	typedef VisualEffectInstance* VisualEffectInstancePtr;
}