#include "GraphicsPCH.h"
#include "ShaderMMatrix.h"
using namespace Hikari;

MMatrixParam::MMatrixParam()
{
	mData = new float[16];
}

MMatrixParam::~MMatrixParam()
= default;

void MMatrixParam::SetMatrix(float* data)
{
	memcpy_s(mData, sizeof(float) * 16, data, sizeof(float) * 16);
}

void MMatrixParam::Update(const Visual* visual, const Camera* camera)
{
	HMatrix Matrix = visual->worldTransform.Matrix();
	/*const float* source = (const float*)Matrix;
	float* target = mData;
	for (int i = 0; i < 16; ++i)
	{
		*target++ = *source++;
	}*/
}
