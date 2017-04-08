#include "MathematicsPCH.h"

#include "APoint.h"
using namespace Hikari;
const APoint APoint::ORIGIN = APoint(0, 0, 0);
APoint::APoint()
{
	M[0] = 0;
	M[1] = 0;
	M[2] = 0;
	M[3] = 1;
}

APoint::APoint(const APoint & pnt)
{
	if (pnt == *this)
		return;
	M[0] = pnt.M[0];
	M[1] = pnt.M[1];
	M[2] = pnt.M[2];
	M[3] = pnt.M[3];
}

APoint::APoint(float x, float y, float z)
{
	M[0] = x;
	M[1] = y;
	M[2] = z;
	M[3] = 1;
}

Hikari::APoint::APoint(const Float3 & tuple)
{
	M[0] = tuple[0];
	M[1] = tuple[1];
	M[2] = tuple[2];
	M[3] = 1;
}


APoint::~APoint()
{
}




APoint::operator const Vector3f&() const
{
}

Hikari::APoint::operator Vector3f&()
{
}

APoint & Hikari::APoint::operator=(const APoint & pnt)
{
	// TODO: 在此处插入 return 语句
	M[0] = pnt.M[0];
	M[1] = pnt.M[1];
	M[2] = pnt.M[2];
	M[3] = pnt.M[3];
	return *this;
}

APoint Hikari::APoint::operator+(const AVector & vec) const
{
	return APoint(M[0] + vec.X(), M[1] + vec.Y(), M[2] + vec.Z());
}

APoint Hikari::APoint::operator+(const APoint & vec) const
{
	return APoint(M[0] + vec.X(), M[1] + vec.Y(), M[2] + vec.Z());
}

APoint Hikari::APoint::operator*(float scale) const
{
	return APoint(M[0] * scale, M[1] * scale, M[2] * scale);
}

APoint Hikari::operator*(float scalar, const APoint & pnt)
{
	return pnt * scalar;
}
AVector Hikari::APoint::operator-(const APoint & pnt) const
{
	return AVector(M[0] - pnt.X(), M[1] - pnt.Y(), M[2] - pnt.Z());
}