#pragma once
#include "GraphicsLib.h"
#include "Camera.h"
#include "Spatial.h"


namespace Hikari
{
	class Culler
	{
	public:
		Culler(const Camera4DV1* camera = 0);
		virtual~Culler();

		inline void SetCamera(const Camera4DV1* camera)
		{
			mCamera = camera;
		}
		inline const Camera4DV1* GetCamera()const
		{
			return mCamera;
		}
		void SetFrustum(const float* frustum);
		inline const float* GetFrustrum()const;
		
		virtual void Insert(Spatial* visible);

		enum {MAX_PLANE_QUANTITY = 32};
		inline int GetPlaneQuantity()const;
		

	protected:
		const Camera4DV1* mCamera;
		


	};
}