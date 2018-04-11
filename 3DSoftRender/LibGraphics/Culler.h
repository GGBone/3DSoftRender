#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\Camera.h"
#include "Graphics\Spatial.h"


namespace Hikari
{
	class Culler
	{
	public:
		Culler(const Camera* camera = 0);
		virtual~Culler();

		inline void SetCamera(const Camera* camera)
		{
			mCamera = camera;
		}
		inline const Camera* GetCamera()const
		{
			return mCamera;
		}
		void SetFrustum(const float* frustum);
		inline const float* GetFrustrum()const;
		
		virtual void Insert(Spatial* visible);

		enum {MAX_PLANE_QUANTITY = 32};
		inline int GetPlaneQuantity()const;
		

	protected:
		const Camera* mCamera;
		


	};
}