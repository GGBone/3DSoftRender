#pragma once
#include "Camera.h"
#include "Spatial.h"


namespace Hikari
{
	class Culler
	{
	public:
		Culler(const Camera* camera = nullptr);
		virtual ~Culler();

		void SetCamera(const Camera* camera)
		{
			mCamera = camera;
		}

		const Camera* GetCamera() const
		{
			return mCamera;
		}

		static void SetFrustum(const float* frustum);
		static inline const float* GetFrustrum();

		virtual void Insert(Spatial* visible);

		enum { MAX_PLANE_QUANTITY = 32 };

		static inline int GetPlaneQuantity();


	protected:
		const Camera* mCamera{};
	};
}
