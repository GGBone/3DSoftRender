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

}