#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\Visual.h"
#include "Graphics\Camera.h"
namespace Hikari
{
	class Visual;
	class Camera;
	class ShaderFloat
	{
	protected:
		~ShaderFloat();
	public:
		ShaderFloat();
		ShaderFloat::ShaderFloat(int numRegisters);
		
		void SetNumRegisters(int numRegisters);
		virtual void Update(const Visual*, const Camera *);
		void SetRegister(int i, const float * data);
		void SetRegisters(const float * data);
		float* GetRegister(int i);
		inline float* GetData() const
		{
			return mData;
		}
	protected:
		int mNumElement;
		float*	mData;
		bool	mAllowUpdater;
	};
	typedef ShaderFloat* ShaderFloatPtr;
}