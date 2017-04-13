#pragma once
#include "GraphicsLib.h"
#include "VisualEffect.h"
#include "ShaderParameter.h"
namespace Hikari
{
	class ShaderParameter;
	class ShaderFloat;
	class VisualEffectInstance
	{
	public:
		VisualEffectInstance(const VisualEffect* effect, int techniqueIndex);
		~VisualEffectInstance();
		const VisualPass* GetPass(int pass) const;
		ShaderParameter * GetVertexShaderParam(int pass) const;
		ShaderParameter * GetPixelShaderParam(int pass) const;
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
		ShaderParameter** mVertexParameters;
		ShaderParameter** mPixelParameters;
	};
	typedef VisualEffectInstance* VisualEffectInstancePtr;
}