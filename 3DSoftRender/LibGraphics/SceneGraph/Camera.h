#pragma once
#include "Resource/Ray.h"
#include "Algebra/hmatrix.h"
#include "Algebra/Vector2.h"
#define ENABLE_BOOST
#include "Event.h"
#undef ENABLE_BOOST

namespace Hikari
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		// Get/set world camera position.
		XMVECTOR GetPositionXM() const;
		XMFLOAT3 GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const XMFLOAT3& v);
		void set_rotation(float x, float y, float z);
		void set_pivotDistance(float dis);
		// Get camera basis vectors.
		XMVECTOR GetRightXM() const;
		XMFLOAT3 GetRight() const;
		XMVECTOR GetUpXM() const;
		XMFLOAT3 GetUp() const;
		XMVECTOR GetLookXM() const;
		XMFLOAT3 GetLook() const;

		// Get frustum properties.
		float GetNearZ() const;
		float GetFarZ() const;
		float GetAspect() const;
		float GetFovY() const;
		float GetFovX() const;

		// Get near and far plane dimensions in view space coordinates.
		float GetNearWindowWidth() const;
		float GetNearWindowHeight() const;
		float GetFarWindowWidth() const;
		float GetFarWindowHeight() const;

		// set perspective frustum.
		void set_project_rh(float fovY, float aspect, float zn, float zf);
		void set_project_lh(float fovY, float aspect, float zn, float zf);

		//set orthographic projection using screen space coord
		void set_ortho_graphic(float width, float height, float m_fNear, float m_fFar);

		// Define camera space via LookAt parameters.
		void LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
		void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);

		// Get View/Proj matrices.
		XMMATRIX View() const;
		XMMATRIX Proj() const;
		XMMATRIX ViewProj() const;

		// Strafe/Walk the camera a distance d.
		void Strafe(float d);
		void Walk(float d);

		// Rotate the camera.
		void Pitch(float angle);
		void RotateY(float angle);
		void Roll(float angle);
		// After modifying camera position/orientation, call to rebuild the view matrix.
		void UpdateViewMatrix();

		//Converts a ray from screen space to world space
		Ray ScreenPointToRay(const Vector2f& screenPoint) const;

		static XMVECTOR ProjectOntoUnitSphere(const Vector2f& screenPos);
		void OnMousePressed(MouseButtonEventArgs& e);
		void OnMouseMoved(MouseMotionEventArgs& e);
		static void OnMouseReleased(MouseButtonEventArgs& e);

		static void OnArcRotate(MouseMotionEventArgs& e);
	private:

		// Camera coordinate system with coordinates relative to world space.
		XMFLOAT3 mPosition;
		XMFLOAT3 mRight;
		XMFLOAT3 mUp;
		XMFLOAT3 mLook;

		// Cache frustum properties.
		float mNearZ;
		float mFarZ;
		float mAspect;
		float mFovY;
		float mNearWindowHeight;
		float mFarWindowHeight;

		// Cache View/Proj matrices.
		XMFLOAT4X4 mView;
		XMFLOAT4X4 mProj;

		//Last 
		Vector2I lastPosition;
	};
}
