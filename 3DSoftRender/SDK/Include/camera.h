#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "HMatrix.h"
#include "Renderer.h"
#include "Core.h"
#include "HMath.h"

namespace Hikari
{

	class ArcBall
	{
	public:
		ArcBall();

		void Reset();
		void SetTranslationRadius(float fRadius)
		{
			m_fRadiusTranslation = fRadius;
		}
		void SetWindow(int nWidth, int nHeight, float fRadius = 0.9f)
		{
			m_nWidth = nWidth;
			m_nHeight = nHeight;
			m_fRadius = fRadius;
		}

		void SetOffset(int nx, int ny)
		{
			m_Offset[0] = (float)nx;
			m_Offset[1] = (float)ny;
		}
	protected:
		HMatrix m_mRotation;
		HMatrix m_mTranslation;
		HMatrix m_mTranslationDelta;

		Vector3f m_Offset;
		int m_nWidth;
		int m_nHeight;
		Vector3f m_vCenter;
		float m_fRadius;
		float m_fRadiusTranslation;

	/*	Quaternation m_qDown;
		Quaternation m_qNow;*/
		bool m_bDrag;
		APoint m_pLastMouse;
		Vector3f m_vDownPt;
		Vector3f m_vCurrentPt;
		Vector3f ScreenToVector(float fScreenPtX, float fScreenPty);
	};

	enum CameraKeys
	{
		CAM_SRAFE_LEFT = 0,
		CAM_STRAFE_RIGHT,
		CAM_MOVE_FORWARD,
		CAM_MOVE_BACKWARD,
		CAM_MOVE_UP,
		CAM_MOVE_DOWN,
		CAM_MOVE_RESET,
		CAM_CONTROLDOWN,
		CAM_MAX_KEYS,
		CAM_UNKNOWN = 0xFF
	};

#define KEY_WAS_DOWN_MASK 0x80
#define KEY_IS_DOWN_MASK 0x01

#define MOUSE_LEFT_BUTTON 0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON 0x04
#define MOUSE_WHEEL 0x08

	class BaseCamera
	{
	public:
		virtual LRESULT HandleMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
		virtual void FrameMove(float fElapsedTime);

		//Function to change camera matrices
		virtual void Reset();
		virtual void SetViewParams(const APoint& pvEyePt,const APoint& pvLookatPt);
		virtual void SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane);

		virtual void SetDragRect(RECT& rc)
		{

		}
		void LookAt(float Ex, float Ey, float Ez, float rx, float ry, float rz, float ux, float uy, float uz, float fx, float fy, float fz);
		void LookAt(APoint& point);
		void RemoveBackface(Object* obj);
		void Perspective(int size, float znear, float zfar, float angle, float aspect);
		
		void Perspective(Object*);
		inline HMatrix GetViewMatrix()
		{
			return m_View;
		}
		inline HMatrix GetProjectMatrix()
		{
			return m_Proj;
		}
	protected:
		virtual CameraKeys MapKey(UINT nKey);
		bool IsKeyDown(BYTE key)const
		{
			return ((key & KEY_IS_DOWN_MASK) == KEY_IS_DOWN_MASK);
		}
		bool WasKeyDown(BYTE key) const
		{
			return ((key & KEY_WAS_DOWN_MASK) == KEY_WAS_DOWN_MASK);
		}
		void ConstrainToBoundary(Vector3f& pv);
		void UpdateMouseDelta();
		void UpdateVelocity(float fElapsedTime);
		void GetInput(bool bGetKeyboardInput, bool GetMouseInput, bool bGetGamepadInput, bool bResetCursorAfterMove);



		HMatrix m_View;
		HMatrix m_Proj;
		APoint m_pos;
		APoint m_target;
		int m_KeysDown;
		BYTE keyBoard[CAM_MAX_KEYS];
		AVector m_KeyBoardDirection;
		AVector lastMousePosition;
		bool m_MouseLButtonDown;
		bool m_MouseMButtonDown;
		bool m_MouseRButtonDown;

		int m_CurrentButtonMask;
		int m_MouseWheelDalta;
		AVector m_MouseDelta;
		float m_FramesToSmoothMouseDelta;

		float m_CameraYawAngle;
		float m_CameraPitchAngle;

		RECT m_Dragrect;
		Vector3f m_Velocity;
		bool m_MovementDrag;
		Vector3f m_VelocityDrag;
		float fDragTimer;
		float m_fTotalDragTimeToZero;

		Vector3f m_vRotVelocity;

		AVector m_dir;		//简单的欧拉角摄像机模型的角度或者观看方向
		AVector m_up;
		AVector m_right;

		float m_view_dist;
		float m_fov;
		float m_near_clip_z;
		float m_far_clip_z;

		float m_vieport_width;
		float m_viewport_height;
		float m_viewport_center_x;
		float m_viewport_center_y;
		float m_aspect_ratio;

		float m_RotationScaler;
		float m_MoveScaler;

		bool m_InvertPitch;//Invert y aix
		bool m_EnableMovement;
		bool m_EnableYRotation;

		bool m_ClipToBoundary;

		AVector m_vMinBoundary;
		AVector m_vMaxBoundary;

		bool m_ResetCursorAfterMove;


		void Division(APoint& point);
	};

	//--------------------------------------------------------------------------------------
	// Simple first person camera class that moves and rotates.
	//       It allows yaw and pitch but not roll.  It uses WM_KEYDOWN and 
	//       GetCursorPos() to respond to keyboard and mouse input and updates the 
	//       view matrix based on input.  
	//--------------------------------------------------------------------------------------
	class FirstPersonCamera : public BaseCamera
	{
	public:
		FirstPersonCamera();
		virtual void FrameMove(float fElpasedTimer);
		void SetRotationButtons(bool left, bool middle, bool right, bool rotateWithoutButtonButton = false);

		const AVector* GetUp()
		{
			return &m_up;
		}
		const AVector* GetRight()
		{
			return &m_right;
		}
		const AVector* GetForward()
		{
			return &m_dir;
		}

	protected:
		//HMatrix worldCamera;	//world matrix of camera (inverse of the view matrix)
		int m_nActiveButtonMask;
		int m_bRotateWithoutButtonDown;

	};

	//--------------------------------------------------------------------------------------
	// Simple model viewing camera class that rotates around the object.
	//--------------------------------------------------------------------------------------

	class ModelViewCamera :public BaseCamera
	{

	};



	class Camera :public BaseCamera
	{
	private:
		int state;
		int attr;

		HMatrix world2Camera;

		HMatrix mper;
		HMatrix mscr;
	public:
		Camera();
		Camera(APoint& point);
		~Camera() {}
		CameraKeys MapKey(UINT nKey) override;
		void SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane) override;
		inline AVector Forward() { return m_dir; }
		void Viewport(float xvmin, float xvmax, float yvmax, float yvmin);
		void FrameMove(float dt) override;

		void SetViewParams(const APoint& pvEyePt,const APoint& pvLookatPt) override;


	};

}