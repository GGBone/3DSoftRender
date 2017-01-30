#pragma once

#include "Renderer.h"
#include "Core.h"
#include "Math.h"
//
//class ArcBall
//{
//public:
//	ArcBall();
//
//	void Reset();
//	void SetTranslationRadius(float fRadius)
//	{
//		m_fRadiusTranslation = fRadius;
//	}
//	void SetWindow(int nWidth, int nHeight, float fRadius = 0.9f)
//	{
//		m_nWidth = nWidth;
//		m_nHeight = nHeight;
//		m_fRadius = fRadius;
//	}
//
//	void SetOffset(int nx, int ny)
//	{
//		m_Offset[0] = nx;
//		m_Offset[1] = ny;
//	}
//protected:
//	Matrix4X4 m_mRotation;
//	Matrix4X4 m_mTranslation;
//	Matrix4X4 m_mTranslationDelta;
//
//	Vector2D m_Offset;
//	int m_nWidth;
//	int m_nHeight;
//	Vector2D m_vCenter;
//	float m_fRadius;
//	float m_fRadiusTranslation;
//
//	Quaternation m_qDown;
//	Quaternation m_qNow;
//	bool m_bDrag;
//	Point3D m_pLastMouse;
//	Vector3D m_vDownPt;
//	Vector3D m_vCurrentPt;
//	Vector3D ScreenToVector(float fScreenPtX, float fScreenPty);
//};
//
//enum CameraKeys
//{
//	CAM_SRAFE_LEFT =0,
//	CAM_STRAFE_RIGHT,
//	CAM_MOVE_FORWARD,
//	CAM_MOVE_BACKWARD,
//	CAM_MOVE_UP,
//	CAM_MOVE_DOWN,
//	CAM_MOVE_RESET,
//	CAM_CONTROLDOWN,
//	CAM_MAX_KEYS,
//	CAM_UNKNOWN = 0xFF
//};
//
//#define KEY_WAS_DOWN_MASK 0x80
//#define KEY_IS_DOWN_MASK 0x01
//
//#define MOUSE_LEFT_BUTTON 0x01
//#define MOUSE_MIDDLE_BUTTON 0x02
//#define MOUSE_RIGHT_BUTTON 0x04
//#define MOUSE_WHEEL 0x08
//
//class BaseCamera
//{
//public:
//	virtual LRESULT HandleMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
//	virtual void FrameMove(float fElapsedTime);
//
//	//Function to change camera matrices
//	virtual void Reset();
//	virtual void SetViewParams(Point3D* pvEyePt, Point3D* pvLookatPt);
//	virtual void SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane);
//
//	virtual void SetDragRect(RECT& rc)
//	{
//		
//	}
//	void LookAt(float Ex, float Ey, float Ez, float rx, float ry, float rz, float ux, float uy, float uz, float fx, float fy, float fz);
//	void LookAt(Point3D& point);
//	void RemoveBackface(Object* obj);
//	void Perspective(int size, float znear, float zfar, float angle, float aspect);
//	void Perspective(RenderList&);
//	void Perspective(Object*);
//private:
//	
//protected:
//	virtual CameraKeys MapKey(UINT nKey);
//	bool IsKeyDown(BYTE key)const
//	{
//		return ((key & KEY_IS_DOWN_MASK) == KEY_IS_DOWN_MASK);
//	}
//	bool WasKeyDown(BYTE key) const
//	{
//		return ((key & KEY_WAS_DOWN_MASK) == KEY_WAS_DOWN_MASK);
//	}
//	void ConstrainToBoundary(Vector3D& pv);
//	void UpdateMouseDelta();
//	void UpdateVelocity(float fElapsedTime);
//	void GetInput(bool bGetKeyboardInput, bool GetMouseInput, bool bGetGamepadInput, bool bResetCursorAfterMove);
//
//
//
//	Matrix4X4 m_View;
//	Matrix4X4 m_Proj;
//	Point3D m_pos;
//	Point3D m_target;
//	int m_KeysDown;
//	BYTE keyBoard[CAM_MAX_KEYS];
//	Vector3D m_KeyBoardDirection;
//	Point2D lastMousePosition;
//	bool m_MouseLButtonDown;
//	bool m_MouseMButtonDown;
//	bool m_MouseRButtonDown;
//
//	int m_CurrentButtonMask;
//	int m_MouseWheelDalta;
//	Vector2D m_MouseDelta;
//	float m_FramesToSmoothMouseDelta;
//
//	float m_CameraYawAngle;
//	float m_CameraPitchAngle;
//
//	RECT m_Dragrect;
//	Vector3D m_Velocity;
//	bool m_MovementDrag;
//	Vector3D m_VelocityDrag;
//	float fDragTimer;
//	float m_fTotalDragTimeToZero;
//
//	Vector2D m_vRotVelocity;
//
//	Vector3D m_dir;		//简单的欧拉角摄像机模型的角度或者观看方向
//	Vector3D m_up;
//	Vector3D m_right;
//
//	float m_view_dist;
//	float m_fov;
//	float m_near_clip_z;
//	float m_far_clip_z;
//
//	Plane3D rt_clip_plane;
//	Plane3D lt_clip_plane;
//	Plane3D tp_clip_plane;
//	Plane3D bt_clip_plane;
//
//	float m_vieport_width;
//	float m_viewport_height;
//	float m_viewport_center_x;
//	float m_viewport_center_y;
//	float m_aspect_ratio;
//
//	float m_RotationScaler;
//	float m_MoveScaler;
//
//	bool m_InvertPitch;//Invert y aix
//	bool m_EnableMovement;
//	bool m_EnableYRotation;
//
//	bool m_ClipToBoundary;
//
//	Vector3D m_vMinBoundary;
//	Vector3D m_vMaxBoundary;
//
//	bool m_ResetCursorAfterMove;
//
//	
//	void Division(Point4D& point);
//};
//
////--------------------------------------------------------------------------------------
//// Simple first person camera class that moves and rotates.
////       It allows yaw and pitch but not roll.  It uses WM_KEYDOWN and 
////       GetCursorPos() to respond to keyboard and mouse input and updates the 
////       view matrix based on input.  
////--------------------------------------------------------------------------------------
//class FirstPersonCamera : public BaseCamera
//{
//public:
//	FirstPersonCamera();
//	virtual void FrameMove(float fElpasedTimer);
//	void SetRotationButtons(bool left, bool middle, bool right,bool rotateWithoutButtonButton = false);
//
//	const Vector3D* GetUp()
//	{
//		return &m_up;
//	}
//	const Vector3D* GetRight()
//	{
//		return &m_right;
//	}
//	const Vector3D* GetForward()
//	{
//		return &m_dir;
//	}
//
//protected:
//	//Matrix4X4 worldCamera;	//world matrix of camera (inverse of the view matrix)
//	int m_nActiveButtonMask;
//	int m_bRotateWithoutButtonDown;
//
//};
//
////--------------------------------------------------------------------------------------
//// Simple model viewing camera class that rotates around the object.
////--------------------------------------------------------------------------------------
//
//class ModelViewCamera :public BaseCamera
//{
//
//};
//
//
//
//class Camera4DV1:public BaseCamera
//{
//private:
//	int state;
//	int attr;
//	
//	Matrix4X4 world2Camera;
//
//	Matrix4X4 mper;
//	Matrix4X4 mscr;
//public:
//	Camera4DV1();
//	Camera4DV1(Point3D& point);
//	~Camera4DV1() {}
//	CameraKeys MapKey(UINT nKey) override;
//	void SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane) override;
//	inline Vector3D Forward() { return m_dir; }
//	void Viewport(float xvmin, float xvmax, float yvmax, float yvmin);
//	void FrameMove(float dt) override;
//
//	void SetViewParams(Point3D * pvEyePt, Point3D * pvLookatPt) override;
//
//	
//};
