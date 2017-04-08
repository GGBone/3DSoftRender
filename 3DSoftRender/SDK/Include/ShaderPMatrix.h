#pragma once
#include "GraphicsLib.h"
#include "ShaderFloat.h"
namespace Hikari
{
	class PMatrixParam :public ShaderFloat
	{
	public:
		PMatrixParam();
		~PMatrixParam();
		void SetMatrix(float* data);
		virtual void Update(const Visual * visual, const Camera4DV1 * camera) override;
	};
}
