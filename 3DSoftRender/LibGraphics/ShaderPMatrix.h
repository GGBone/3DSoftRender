#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\ShaderFloat.h"
namespace Hikari
{
	class PMatrixParam :public ShaderFloat
	{
	public:
		PMatrixParam();
		~PMatrixParam();
		void SetMatrix(float* data);
		virtual void Update(const Visual * visual, const Camera * camera) override;
	};
}
