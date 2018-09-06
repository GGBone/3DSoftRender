#include "GraphicsPCH.h"
#include "ShaderVMatrix.h"
using namespace Hikari;

VMatrixParam::VMatrixParam()
{
	mData = new float[16];
}

VMatrixParam::~VMatrixParam()
= default;

void VMatrixParam::SetMatrix(float* data)
{
	memcpy_s(mData, sizeof(float) * 16, data, sizeof(float) * 16);
}

void VMatrixParam::Update(const Visual* visual, const Camera* camera)
{
	//	HMatrix viewMatrix = ((BaseCamera*)camera)->GetViewMatrix();
	//const float* source = (const float*)viewMatrix;
	/*float* target = mData;
	for (int i = 0; i < 16; ++i)
	{
		*target++ = *source++;
	}*/
}
