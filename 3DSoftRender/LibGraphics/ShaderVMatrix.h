#pragma once
#include "GraphicsLib.h"
#include "ShaderFloat.h"
namespace Hikari
{
	class VMatrixParam:public ShaderFloat
	{
	public:
		VMatrixParam();
		~VMatrixParam();
		void SetMatrix(float* data);
		virtual void Update(const Visual * visual, const Camera4DV1 * camera) override;
	};
}
