#pragma once
#include "GraphicsLIB.h"
#include "Object.h"
#include "Transform.h"

namespace Hikari
{
	class Culler;
	class Spatial : public Object
	{
	protected:
		Spatial();
	public:
		virtual ~Spatial();

		Transform localTransform;
		Transform worldTransform;

		Transform inverseTransform;
		bool worldTransfromIsCurrent;

		enum CullingMode
		{

			//Determine Visibility static by comparing the world bounding volume
			//to culling planes
			CULL_DYNAMIC,

			CULL_ALWAYS,

			CULL_NEVER
		};
		CullingMode Culling;

		void Update(double applicationTime = 65535.0, bool initiator = true);

		inline Spatial* GetParent();

	protected:
		virtual void UpdateWorldData(double applicationTime);
		virtual void UpdateWorldBound() = 0;
		void ProgateBoundToRoot();

	public:
		void OnGetVisibleSet(Culler& culler, bool noCull);

		virtual void GetVisibleSet(Culler& culler, bool noCull) = 0;

	};

	typedef Spatial* SpatialPtr;

}