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

		inline void SetCamera(const Camera* camera);
		inline const Camera* GetCamera()const;
		void SetFrustum(const float* frustum);
		inline const float* GetFrustrum()const;
		
		virtual void Insert(Spatial* visible);

		enum {MAX_PLANE_QUANTITY = 32};
		inline int GetPlaneQuantity()const;
		

	protected:
		const Camera4DV1* mCamera;
		


	};
}