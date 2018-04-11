#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\ShaderFloat.h"
namespace Hikari
{
	class MMatrixParam :public ShaderFloat
	{
	public:
		MMatrixParam();
		~MMatrixParam();
		void SetMatrix(float* data);
		virtual void Update(const Visual * visual, const Camera * camera) override;
	};
}
