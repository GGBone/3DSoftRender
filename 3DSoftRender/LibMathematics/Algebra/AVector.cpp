#include "MathematicsPCH.h"
#include "Algebra/AVector.h"
#include "Algebra/APoint.h"
#include "Base/Float3.h"
#include "Base/Float4.h"
using namespace Hikari;
const AVector AVector::ZERO = AVector(0, 0, 0);
const AVector AVector::UP = AVector(0, 1, 0);
const AVector AVector::RIGHT = AVector(1, 0, 0);
const AVector AVector::FORWARD = AVector(0, 0, 1);
AVector::AVector()
= default;

AVector::AVector(const AVector& vec)
{
	M[0] = vec.M[0];
	M[1] = vec.M[1];
	M[2] = vec.M[2];
	M[3] = vec.M[3];
}

AVector::AVector(float x, float y, float z)
{
	M[0] = x;
	M[1] = y;
	M[2] = z;
	M[3] = 0;
}

AVector::AVector(const Float3& tuple)
{
	M[0] = tuple[0];
	M[1] = tuple[1];
	M[2] = tuple[2];
	M[3] = 0;
}

AVector::AVector(const Float4& tuple)
{
	M[0] = tuple[0];
	M[1] = tuple[1];
	M[2] = tuple[2];
	M[3] = 0;
}


AVector::AVector(const Vector3f& vec)
{
	M[0] = vec[0];
	M[1] = vec[1];
	M[2] = vec[2];
	M[3] = 0;
}

AVector::~AVector()
= default;

AVector AVector::operator=(const AVector& vec)
{
	// TODO: insert return statement here
	M[0] = vec[0];
	M[1] = vec[1];
	M[2] = vec[2];
	M[3] = 0;
	return *this;
}


AVector AVector::Cross(const AVector& vec) const
{
	return AVector
	(
		M[1] * vec.M[2] - M[2] * vec.M[1],
		M[2] * vec.M[0] - M[0] * vec.M[2],
		M[0] * vec.M[1] - M[1] * vec.M[0]
	);
}

void AVector::GenerateOrthonormalBasis(AVector& vec0, AVector& vec1, AVector& vec2)
{
	vec2.Normalize();
	GenerateComplementBasis(vec0, vec1, vec2);
}

void AVector::GenerateComplementBasis(AVector& vec0, AVector& vec1, const AVector& vec2)
{
	int invLength;

	if (fabsf(vec2.M[0]) >= fabsf(vec2.M[1]))
	{
		// vec2.x or vec2.z is the largest magnitude component, swap them
		invLength = 1.0f / sqrtf(vec2.M[0] * vec2.M[0] +
			vec2.M[2] * vec2.M[2]);
		vec0.M[0] = -vec2.M[2] * invLength;
		vec0.M[1] = 0.0f;
		vec0.M[2] = +vec2.M[0] * invLength;
		vec1.M[0] = vec2.M[1] * vec0.M[2];
		vec1.M[1] = vec2.M[2] * vec0.M[0] -
			vec2.M[0] * vec0.M[2];
		vec1.M[2] = -vec2.M[1] * vec0.M[0];
	}
	else
	{
		// vec2.y or vec2.z is the largest magnitude component, swap them
		invLength = 1.0f / sqrtf(vec2.M[1] * vec2.M[1] +
			vec2.M[2] * vec2.M[2]);
		vec0.M[0] = 0.0f;
		vec0.M[1] = +vec2.M[2] * invLength;
		vec0.M[2] = -vec2.M[1] * invLength;
		vec1.M[0] = vec2.M[1] * vec0.M[2] -
			vec2.M[2] * vec0.M[1];
		vec1.M[1] = -vec2.M[0] * vec0.M[2];
		vec1.M[2] = vec2.M[0] * vec0.M[1];
	}
}

AVector AVector::operator+=(const AVector& vec)
{
	return AVector
	(
		M[0] += vec.M[0],
		M[1] += vec.M[1],
		M[2] += vec.M[2]
	);
}

AVector AVector::operator-=(const AVector& vec)
{
	return AVector();
}

AVector AVector::operator+(const APoint& vec) const
{
	return AVector(M[0] + vec.X(), M[1] + vec.Y(), M[2] + vec.Z());
}

AVector AVector::operator+(const AVector& vec) const
{
	return AVector();
}

AVector AVector::operator-(const AVector& vec) const
{
	return AVector();
}

AVector AVector::operator*(float scalar) const
{
	return AVector(M[0] * scalar, M[1] * scalar, M[2] * scalar);
}

AVector AVector::operator/(float scalar) const
{
	return AVector();
}

float AVector::Dot(const AVector& vec) const
{
	return M[0] * vec.M[0] + M[1] * vec.M[1] + M[2] * vec.M[2];
}
