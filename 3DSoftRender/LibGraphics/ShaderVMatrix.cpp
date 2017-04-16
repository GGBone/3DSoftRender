#include "ShaderVMatrix.h"
using namespace Hikari;
Hikari::VMatrixParam::VMatrixParam()
{
	mData = new float[16];
}

Hikari::VMatrixParam::~VMatrixParam()
{
}

void Hikari::VMatrixParam::SetMatrix(float * data)
{
	memcpy_s(mData, sizeof(float) * 16, data, sizeof(float) * 16);
}

void Hikari::VMatrixParam::Update(const Visual * visual, const Camera * camera)
{
//	HMatrix viewMatrix = ((BaseCamera*)camera)->GetViewMatrix();
	//const float* source = (const float*)viewMatrix;
	/*float* target = mData;
	for (int i = 0; i < 16; ++i)
	{
		*target++ = *source++;
	}*/
}