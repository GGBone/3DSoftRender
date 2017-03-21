#include "MathematicsPCH.h"
#include "AVector.h"
using namespace Hikari;
const AVector AVector::ZERO = AVector(0, 0, 0);
const AVector AVector::UP = AVector(0, 1, 0);
const AVector AVector::RIGHT = AVector(1, 0, 0);
const AVector AVector::FORWARD = AVector(0, 0, 1);
Hikari::AVector::AVector()
{

}

Hikari::AVector::AVector(const AVector & vec)
{
	M[0] = vec.M[0];
	M[1] = vec.M[1];
	M[2] = vec.M[2];
	M[3] = vec.M[3];
}

Hikari::AVector::AVector(float x, float y, float z)
{
	M[0] = x;
	M[1] = y;
	M[2] = z;
	M[3] = 0;
}

Hikari::AVector::AVector(const Float3 & tuple)
{
	M[0] = tuple[0];
	M[1] = tuple[1];
	M[2] = tuple[2];
	M[3] = 0;
}

Hikari::AVector::AVector(const Vector3f & vec)
{
	M[0] = vec[0];
	M[1] = vec[1];
	M[2] = vec[2];
	M[3] = 0;
}

Hikari::AVector::~AVector()
{
}

AVector& Hikari::AVector::operator=(const AVector & vec)
{
	// TODO: insert return statement here
	M[0] = vec[0];
	M[1] = vec[1];
	M[2] = vec[2];
	M[3] = 0;
	return *this;
}

AVector Hikari::AVector::Cross(const AVector & vec) const
{
	return AVector
	(
		M[1] * vec.M[2] - M[2] * vec.M[1],
		M[2] * vec.M[0] - M[0] * vec.M[2],
		M[0] * vec.M[1] - M[1] * vec.M[0]
	);
}