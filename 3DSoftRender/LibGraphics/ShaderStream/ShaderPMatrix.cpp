#include "GraphicsPCH.h"
#include "ShaderPMatrix.h"
using namespace Hikari;

PMatrixParam::PMatrixParam()
{
	mData = new float[16];
}

PMatrixParam::~PMatrixParam()
= default;

void PMatrixParam::SetMatrix(float* data)
{
	memcpy_s(mData, sizeof(float) * 16, data, sizeof(float) * 16);
}

void PMatrixParam::Update(const Visual* visual, const Camera* camera)
{
	//	HMatrix viewMatrix = ((BaseCamera*)camera)->GetProjectMatrix();
	/*const float* source = (const float*)viewMatrix;
	float* target = mData;
	for (int i = 0; i < 16; ++i)
	{
		*target++ = *source++;
	}*/
}
