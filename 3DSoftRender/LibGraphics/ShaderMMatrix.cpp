#include "ShaderMMatrix.h"
using namespace Hikari;
Hikari::MMatrixParam::MMatrixParam()
{
	mData = new float[16];
}

Hikari::MMatrixParam::~MMatrixParam()
{
}

void Hikari::MMatrixParam::SetMatrix(float * data)
{
	memcpy_s(mData, sizeof(float) * 16, data, sizeof(float) * 16);
}

void Hikari::MMatrixParam::Update(const Visual * visual, const Camera4DV1 * camera)
{
	HMatrix Matrix = visual->worldTransform.Matrix();
	const float* source = (const float*)Matrix;
	float* target = mData;
	for (int i = 0; i < 16; ++i)
	{
		*target++ = *source++;
	}
}