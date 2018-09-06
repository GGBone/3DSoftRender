#pragma once
#include "GraphicsLib.h"
#include "ShaderFloat.h"

namespace Hikari
{
	class MMatrixParam : public ShaderFloat
	{
	public:
		MMatrixParam();
		~MMatrixParam();
		void SetMatrix(float* data);
		void Update(const Visual* visual, const Camera* camera) override;
	};
}
