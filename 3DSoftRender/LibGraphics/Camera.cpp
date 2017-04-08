#include "Camera.h"
#include "Math.h"
#include "Object.h"
using namespace Hikari;
ArcBall::ArcBall()
{
	Reset();
	m_vDownPt = Vector3f(0,0,0);
	m_vCurrentPt = Vector3f(0, 0, 0);
	m_Offset[0] = m_Offset[1] = 0;

	RECT rc;
	GetClientRect(GetForegroundWindow(), &rc);
	SetWindow(rc.right, rc.bottom);
}

void ArcBall::Reset()
{
	/*m_qDown.SetIdentity();
	m_qNow.SetIdentity();
	m_mRotation.setIdentity();
	m_mTranslation.setIdentity();
	m_mTranslationDelta.setIdentity();*/
	m_bDrag = FALSE;
	m_fRadiusTranslation = 1.0f;
	m_fRadius = 1.0f;
}
//
//AVector ArcBall::ScreenToVector(float fScreenX, float fScreeny)
//{
//	float x = -(fScreenX - m_Offset[0] - m_nWidth / 2) / (m_fRadius * m_nWidth / 2);
//	float y = (fScreeny - m_Offset[1] - m_nHeight / 2) / (m_fRadius * m_nHeight / 2);
//
//	float z = 0.0f;
//
//	float mag = x*x + y *y;
//	if (mag > 1.0f)
//	{
//		float scale = 1.0f / sqrtf(mag);
//		y *= scale;
//		x *= scale;
//	}
//	else
//		z = sqrtf(1.0 - mag);
//	return AVector(x, y, z);
//}

void Camera4DV1::FrameMove(float dt)
{
	//Translate(m_dir, dt * 10);
}
void Camera4DV1::SetViewParams(const APoint& pvEyePt,const APoint& pvLookatPt)
{
	BaseCamera::SetViewParams(pvEyePt, pvLookatPt);
}


void BaseCamera::Perspective(int size, float znear, float zfar, float angle, float aspect)
{
	
}

void BaseCamera::Division(APoint& point)
{
	point = APoint(point[0] / point[3], point[1] / point[3], point[2] / point[3]);
}
/*
void BaseCamera::Perspective(RenderList& rend_list)
{
	float top = m_near_clip_z * tan(m_fov / 2);
	float right = m_aspect_ratio * top;
	float left = -right;
	float bottom = -top;

	float XClip[][4] =
	{
		2 * m_near_clip_z / (right - left), 0, -(right + left) / (right - left), 0,
		0, 2 * m_near_clip_z / (top - bottom), -(top + bottom) / (top - bottom), 0,
		0, 0, m_near_clip_z / (m_far_clip_z - m_near_clip_z), -m_near_clip_z * m_far_clip_z / (m_far_clip_z - m_near_clip_z),
		0, 0, 1, 0
	};
	m_View = HMatrix(&XClip[0][0]);

	for (int i = 0; i < rend_list.num_polys; i++)
	{
		PolyF4DV1* curr_poly = rend_list.poly_ptrs[i];
		if (curr_poly == NULL)
			continue;
		for (int vertex = 0; vertex < 3; vertex++)
		{
			curr_poly->tvlist[vertex] = m_View * curr_poly->tvlist[vertex];
			Division(curr_poly->tvlist[vertex]);
		}
	}
}*/
//
void BaseCamera::RemoveBackface(Object* obj)
{
	//Object4DV1* temp = static_cast<Object4DV1*>(obj);
	//if (temp)
	//{
	//	/*if (temp->state & OBJECTDV1_STATE_CULLED)
	//	return;*/

	//	for (int poly = 0; poly < temp->num_polys; poly++)
	//	{
	//		Poly4DV1* curr = &temp->plist[poly];

	//		//check the state
	//		if (!(curr->state & POLY4DV1_STATE_ACTIVE) ||
	//			(curr->state & POLY4DV1_STATE_CLIPPED) ||

	//			(curr->state & POLY4DV1_STATE_BACKFACE))
	//			continue; // move onto next poly

	//		int index0 = curr->vert[0];
	//		int index1 = curr->vert[1];
	//		int index2 = curr->vert[2];

	//		AVector u, v, n;
	//		u = temp->vlist_trans[index1] - temp->vlist_trans[index0];
	//		v = temp->vlist_trans[index2] - temp->vlist_trans[index0];

	//		n = u.cross(v);

	//		AVector camDirection = temp->vlist_trans[index0] - m_pos;
	//		float degree = n * camDirection;

	//		if (degree < 0.0)
	//			curr->state |= POLY4DV1_STATE_BACKFACE;


	//	}
	//}
}
void BaseCamera::Perspective(Object* obj)
{
	float top = m_near_clip_z * tan(m_fov / 2 /180.0f * PI);
	float right = m_aspect_ratio * top;
	float left = -right;
	float bottom = -top;

	float XClip[][4] =
	{
		2 * m_near_clip_z / (right - left), 0, -(right + left) / (right - left), 0,
		0, 2 * m_near_clip_z / (top - bottom), -(top + bottom) / (top - bottom), 0,
		0, 0, m_near_clip_z / (m_far_clip_z - m_near_clip_z), -m_near_clip_z * m_far_clip_z / (m_far_clip_z - m_near_clip_z),
		0, 0, 1, 0
	};
	m_View = HMatrix(&XClip[0][0]);
	RemoveBackface(obj);

}

CameraKeys BaseCamera::MapKey(UINT nKey)
{
	return CameraKeys();
}

void BaseCamera::UpdateMouseDelta()
{
}
void BaseCamera::UpdateVelocity(float fElapsedTime)
{
}
void BaseCamera::GetInput(bool bGetKeyboardInput, bool GetMouseInput, bool bGetGamepadInput, bool bResetCursorAfterMove)
{
}


CameraKeys Camera4DV1::MapKey(UINT nKey)
{
	return CameraKeys();
}
void Camera4DV1::SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane)
{
	BaseCamera::SetProjParams(fFOV, fAspect, fNearPlane, fFarPlane);
}
void Camera4DV1::Viewport(float xvmin, float xvmax, float yvmax, float yvmin)
{
	HMatrix viewport;
	float v[4][4];
	v[0][0] = (xvmax - xvmin) / 2;
	v[1][1] = (yvmax - yvmin) / 2;

}


LRESULT BaseCamera::HandleMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

void BaseCamera::FrameMove(float fElapsedTime)
{
}

void BaseCamera::Reset()
{
}

void BaseCamera::SetViewParams(const APoint& pvEyePt,const APoint& pvLookatPt)
{
	m_pos = pvEyePt;
	m_target = pvLookatPt;
	m_dir = m_target - m_pos;
	m_up = AVector::UP;
	m_right = m_dir.Cross(m_up);
	HMatrix temp(m_dir.X(), m_up.X(), m_right.X(), m_pos.X(),
		m_dir.Y(), m_up.Y(), m_right.Y(), m_pos.Y(),
		m_dir.Z(), m_up.Z(), m_right.Z(), m_pos.Z(),
		0.0f, 0.0f, 0.0f, 1.0f
	);
	m_View = temp.Inverse();
}

void BaseCamera::SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane)
{
	float top = fNearPlane * tan(fFOV / 2);
	float right = fAspect * top;
	float left = -right;
	float bottom = -top;

	m_Proj = HMatrix
	(
		2 * fNearPlane / (right - left), 0, -(right + left) / (right - left), 0,
		0, 2 * fNearPlane / (top - bottom), -(top + bottom) / (top - bottom), 0,
		0, 0, fFarPlane / (fFarPlane - fNearPlane), -fNearPlane*fFarPlane / (fFarPlane - fNearPlane),
		0, 0, 1, 0
	);
}

//void BaseCamera::LookAt(float Ex, float Ey, float Ez, float rx, float ry, float rz, float ux, float uy, float uz, float fx, float fy, float fz)
//{
//	m_pos = APoint(Ex, Ey, Ez);
//	m_up = AVector(ux, uy, uz);
//	m_right = AVector(rx, ry, rz);
//
//	float CAMERA_M[4][4];
//
//	CAMERA_M[0][0] = rx;
//	CAMERA_M[0][1] = ux;
//	CAMERA_M[0][2] = fx;
//	CAMERA_M[0][3] = Ex;
//
//	CAMERA_M[1][0] = ry;
//	CAMERA_M[1][1] = uy;
//	CAMERA_M[1][2] = fy;
//	CAMERA_M[1][3] = Ey;
//
//	CAMERA_M[2][0] = rz;
//	CAMERA_M[2][1] = uz;
//	CAMERA_M[2][2] = fz;
//	CAMERA_M[2][3] = Ez;
//
//	CAMERA_M[3][0] = 0.0f;
//	CAMERA_M[3][1] = 0.0f;
//	CAMERA_M[3][2] = 0.0f;
//	CAMERA_M[3][3] = 1;
//
//	//求出逆矩阵，然后与世界坐标的v相乘
//	m_View = HMatrix(&CAMERA_M[0][0]);
//	m_View.Inverse(m_View);
//}
//void BaseCamera::LookAt(APoint& point)
//{
//	m_dir = (point - m_pos).Normal();
//	m_right = m_up.cross(m_dir);
//	m_up = m_dir.cross(m_right);
//	float CAMERA_M[][4] =
//	{
//		m_right[0], m_up[0], m_dir[0], m_pos[0],
//		m_right[1], m_up[1], m_dir[1], m_pos[1],
//		m_right[2], m_up[2], m_dir[2], m_pos[2],
//		0.0f, 0.0f, 0.0f, 1.0f
//	};
//	m_View = HMatrix(&CAMERA_M[0][0]);
//	m_View.Inverse(m_View);
//}
Camera4DV1::Camera4DV1()
{
	/*m_pos = APoint(0.0f, 0.0f, 0.0);
	m_dir = AVector::FORWARD;
	m_up = AVector::UP;
	m_right = AVector::RIGHT;*/
}
Camera4DV1::Camera4DV1(APoint& point)
{
	/*m_pos = point;
	m_dir = AVector::FORWARD;
	m_up = AVector::UP;
	m_right = AVector::RIGHT;*/
}