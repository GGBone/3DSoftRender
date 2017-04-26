#pragma once
#include "GraphicsLib.h"
#include "Apoint.h"
#include "AVector.h"
namespace Hikari
{
	class APoint;
	class AVector;
	class Material;
	class RaycastHit
	{
	public:
		// The point in 3D space where the ray hit the geometry.
		APoint Point;
		// The surface normal where the ray hit the geometry.
		AVector Normal;
		// The distance from the ray origin to the impact point.
		float Distance;

		// A pointer to the material that was hit (if one was, NULL otherwise)
		Material* pMaterial;

	};
}
