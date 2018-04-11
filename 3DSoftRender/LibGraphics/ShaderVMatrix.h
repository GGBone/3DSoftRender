#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\ShaderFloat.h"
namespace Hikari
{
	class VMatrixParam:public ShaderFloat
	{
	public:
		VMatrixParam();
		~VMatrixParam();
		void SetMatrix(float* data);
		virtual void Update(const Visual * visual, const Camera * camera) override;
	};
}
