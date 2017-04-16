#pragma once
#define NOMINMAX
#include "Object.h"
#include "Ray.h"
#include "RasterizerState.h"
#include "HMatrix.h"
#include "Float4.h"
namespace Hikari
{
	class Float4;
	class Float2;
	class HMatrix;
	class Camera : public Object
	{
	public:
		typedef Object base;

		enum class Space
		{
			Local,
			World
		};

		Camera();
		virtual ~Camera() {};

		// TODO: Viewports belong in the rasterizer state.. not the camera.
		// Set view port parameters
		void SetViewport(const Viewport& viewport);
		const Viewport& GetViewport() const;

		// Set projection parameters
		void SetProjectionRH(float fovy, float aspect, float zNear, float zFar);
		void SetProjectionLH(float fovy, float aspect, float zNear, float zFar);

		float GetNearClipPlane() const;
		float GetFarClipPlane() const;

		// Set an orthographic projection using screen space coordinates.
		void SetOrthographic(float left, float right, float top, float bottom);

		// Add this pitch (rotation about the X-axis) in degrees
		// to the current camera's pitch 
		void AddPitch(float fPitch, Space space = Space::Local);
		// Add this yaw (rotation about the Y-axis) in degrees
		// to the current camera's yaw
		void AddYaw(float fYaw, Space space = Space::Local);
		// Add this roll (rotation about the Z-axis) in degrees 
		// to the current camera's roll
		void AddRoll(float fRoll, Space space = Space::Local);

		// Set Euler angles (in degrees)
		void SetEulerAngles(const Vector3f& eulerAngles);

		// Add rotation to the current rotation (always in local space)
		void AddRotation(const Float4& rot);

		// Translate the the camera's X-axis
		void TranslateX(float x, Space space = Space::Local);
		// Translate the camera's Y-axis
		void TranslateY(float y, Space space = Space::Local);
		// Translate the camera's Z-axis
		void TranslateZ(float z, Space space = Space::Local);

		// Set the current translation of the camera, replacing the current translation.
		void SetTranslate(const Vector3f& translate);
		// Set the current rotation from Euler angles in degrees, replacing the current rotation.
		void SetRotate(float pitch, float yaw, float roll);
		// Set the current rotation from Euler angles in degrees, replacing the current rotation.
		void SetRotate(const Vector3f& rotate);
		void SetRotate(const Float4& rot);

		// If the pivot distance > 0 then the camera will rotate around a pivot point
		// that is pivotDistance along the lookAt vector of the camera.
		void SetPivotDistance(float pivotDistance);
		float GetPivotDistance() const;

		// Get the camera's pivot point in world space
		Vector3f GetPivotPoint() const;

		Vector3f GetTranslation() const;
		Vector3f GetRotation() const;

		// Get the current rotation of the camera in Euler angles (degrees)
		Vector3f GetEulerAngles() const;

		// Directly set the view matrix
		void        SetViewMatrix(const HMatrix& viewMatrix);
		HMatrix   GetViewMatrix() const;

		// Directly set the projection matrix
		void        SetProjectionMatrix(const HMatrix& projectionMatrix);
		HMatrix   GetProjectionMatrix() const;

		// Get the view projection inverse matrix (useful for picking)
		HMatrix	GetViewProjectionInverseMatrix() const;

		// Converts a screen point to a ray in world space.
		Ray			ScreenPointToRay(const Float2& screenPoint) const;

		// For arcball camera, call this function with client-space coordinates
		// when the mouse is clicked on the screen.
		/*void OnMousePressed(MouseButtonEventArgs& e);
		void OnMouseMoved(MouseMotionEventArgs& e);*/

	protected:

		Vector3f ProjectOntoUnitSphere(Float2& screenPos);

		virtual void UpdateViewMatrix();
		virtual void UpdateViewProjectionInverse();

		// View port parameters
		Viewport    m_Viewport;

		// Projection parameters
		float       m_fVFOV;
		float       m_fAspect;
		float       m_fNear;
		float       m_fFar;

		// World space parameters
		Vector3f   m_Translate;
		Float4   m_Rotate;

		// Used for arcball camera
		Float4   m_PreviousPoint;
		float       m_PivotDistance;

		// View matrix
		HMatrix   m_ViewMatrix;
		// Projection matrix.
		HMatrix   m_ProjectionMatrix;

		HMatrix	m_ViewProjectionInverse;

		// True if the view matrix needs to be updated.
		bool        m_bViewDirty;
		// True if the view projection inverse matrix needs to be updated.
		bool		m_bViewProjectionInverseDirty;

	private:

	};
}