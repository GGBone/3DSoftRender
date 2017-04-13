#pragma once
// A Ray structure that can be used in raycasting renderers.
#include "AVector.h"
#include "APoint.h"
namespace Hikari
{
	class Material;

	class Ray
	{
	public:
		Ray();
		Ray(APoint origin, AVector direction);

		// Gets a point that is distance units along the ray.
		AVector GetPointOnRay(float distance) const;

		// The origin of the ray in 3D space.
		APoint m_Origin;
		// The normalized direction of the ray in 3D space.
		AVector m_Direction;

		// The material that was hit.
		Material* m_pMaterial;
	};
}