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
		virtual void Update(const Visual * visual, const Camera * camera) override;
	};
}
