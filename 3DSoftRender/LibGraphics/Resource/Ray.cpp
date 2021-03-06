#include <GraphicsPCH.h>
#include "Ray.h"

using namespace Hikari;

Ray::Ray()
= default;

Ray::Ray(APoint origin, AVector direction)
	: m_Origin(origin)
	  , m_Direction(direction)
{
}

AVector Ray::GetPointOnRay(float distance) const
{
	return (m_Direction * distance) + m_Origin;
}
