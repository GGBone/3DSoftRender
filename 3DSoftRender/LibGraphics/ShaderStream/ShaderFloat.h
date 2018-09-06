#pragma once
#include "GraphicsLib.h"
#include "Visual.h"
#include "Camera.h"

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
		virtual void Update(const Visual*, const Camera*);
		void SetRegister(int i, const float* data);
		static void SetRegisters(const float* data);
		static float* GetRegister(int i);

		float* GetData() const
		{
			return mData;
		}

	protected:
		int mNumElement;
		float* mData;
		bool mAllowUpdater;
	};

	typedef ShaderFloat* ShaderFloatPtr;
}
