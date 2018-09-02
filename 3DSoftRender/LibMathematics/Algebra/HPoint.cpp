#include "MathematicsPCH.h"
#include "HPoint.h"
using namespace Hikari;

HPoint::HPoint()
{
}

HPoint::HPoint(float x, float y, float z, float w)
{
	M[0] = x;
	M[1] = y;
	M[2] = z;
	M[3] = w;
}

HPoint::HPoint(const HPoint& v)
{
	M[0] = v.X();
	M[1] = v.Y();
	M[2] = v.Z();
	M[3] = v.W();
}

HPoint::~HPoint()
{
}

HPoint& HPoint::operator=(const HPoint& point)
{
	// TODO: insert return statement here
	M[0] = point.X();
	M[1] = point.Y();
	M[2] = point.Z();
	M[3] = point.W();
	return *this;
}

bool HPoint::operator==(const HPoint& pnt) const
{
	return (X() == pnt.X() && Y() == pnt.Y() && Z() == pnt.Z() && W() == pnt.W());
}
