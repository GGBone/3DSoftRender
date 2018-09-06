#pragma once
#include "GraphicsLib.h"
#include "Algebra/Apoint.h"
#include "Algebra/AVector.h"

namespace Hikari
{
	class APoint;
	class AVector;
	class Material;

	class RaycastHit
	{
	public:
		// The point in 3D space where the ray hit the geometry.
		APoint point;
		// The surface normal where the ray hit the geometry.
		AVector normal;
		// The distance from the ray origin to the impact point.
		float distance;

		// A pointer to the material that was hit (if one was, NULL otherwise)
		Material* p_material;
	};
}
