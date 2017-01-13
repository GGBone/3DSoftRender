#include "Camera.h"
#include "Math.h"
#include "Object.h"
ArcBall::ArcBall()
{
	Reset();
	m_vDownPt = Vector3D(0, 0, 0);
	m_vCurrentPt = Vector3D(0, 0, 0);
	m_Offset[0] = m_Offset[1] = 0;

	RECT rc;
	GetClientRect(GetForegroundWindow(), &rc);
	SetWindow(rc.right, rc.bottom);
}

void ArcBall::Reset()
{
	m_qDown.SetIdentity();
	m_qNow.SetIdentity();
	m_mRotation.setIdentity();
	m_mTranslation.setIdentity();
	m_mTranslationDelta.setIdentity();
	m_bDrag = FALSE;
	m_fRadiusTranslation = 1.0f;
	m_fRadius = 1.0f;
}
Vector3D ArcBall::ScreenToVector(float fScreenX, float fScreeny)
{
	float x = -(fScreenX - m_Offset[0] - m_nWidth / 2) / (m_fRadius * m_nWidth / 2);
	float y = (fScreeny - m_Offset[1] - m_nHeight / 2) / (m_fRadius * m_nHeight / 2);

	float z = 0.0f;

	float mag = x*x + y *y;
	if (mag > 1.0f)
	{
		float scale = 1.0f / sqrtf(mag);
		y *= scale;
		x *= scale;
	}
	else
		z = sqrtf(1.0 - mag);
	return Vector3D(x, y, z);
}

void Camera4DV1::FrameMove(float dt)
{
	Translate(m_dir, dt * 10);
}
void Camera4DV1::SetViewParams(Point3D* pvEyePt, Point3D* pvLookatPt)
{
	m_pos = *pvEyePt;
	m_target = *pvLookatPt;
}


void BaseCamera::Perspective(int size, float znear, float zfar, float angle, float aspect)
{
	float top = znear * tan(angle / 2);
	float right = aspect * top;
	float left = -right;
	float bottom = -top;

	float XClip[][4] =
	{
		2 * znear / (right - left), 0, -(right + left) / (right - left), 0,
		0, 2 * znear / (top - bottom), -(top + bottom) / (top - bottom), 0,
		0, 0, zfar / (zfar - znear), -znear*zfar / (zfar - znear),
		0, 0, 1, 0
	};
	Matrix4X4 m(&XClip[0][0]);
}

void BaseCamera::Division(Point4D& point)
{
	point = Point4D(point[0] / point[3], point[1] / point[3], point[2] / point[3], 1);
}
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
	m_View = Matrix4X4(&XClip[0][0]);

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
}

void BaseCamera::RemoveBackface(Object* obj)
{
	Object4DV1* temp = static_cast<Object4DV1*>(obj);
	if (temp)
	{
		/*if (temp->state & OBJECTDV1_STATE_CULLED)
		return;*/

		for (int poly = 0; poly < temp->num_polys; poly++)
		{
			Poly4DV1* curr = &temp->plist[poly];

			//check the state
			if (!(curr->state & POLY4DV1_STATE_ACTIVE) ||
				(curr->state & POLY4DV1_STATE_CLIPPED) ||

				(curr->state & POLY4DV1_STATE_BACKFACE))
				continue; // move onto next poly

			int index0 = curr->vert[0];
			int index1 = curr->vert[1];
			int index2 = curr->vert[2];

			Vector3D u, v, n;
			u = temp->vlist_trans[index1] - temp->vlist_trans[index0];
			v = temp->vlist_trans[index2] - temp->vlist_trans[index0];

			n = u.cross(v);

			Vector3D camDirection = temp->vlist_trans[index0] - m_pos;
			float degree = n * camDirection;

			if (degree < 0.0)
				curr->state |= POLY4DV1_STATE_BACKFACE;


		}
	}
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
	m_View = Matrix4X4(&XClip[0][0]);
	RemoveBackface(obj);
	Object4DV1* temp = static_cast<Object4DV1*>(obj);
	if (temp)
	{
		for (int vertex = 0; vertex < temp->num_vertices; vertex++)
		{
			temp->vlist_trans[vertex] = m_View * temp->vlist_trans[vertex];
			Division(temp->vlist_trans[vertex]);
		}

	}

}
CameraKeys BaseCamera::MapKey(UINT nKey)
{
	return CameraKeys();
}
void BaseCamera::ConstrainToBoundary(Vector3D & pv)
{
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
	m_fov = fFOV;
	m_aspect_ratio = fAspect;
	m_near_clip_z = fNearPlane;
	m_far_clip_z = fFarPlane;
}
void Camera4DV1::Viewport(float xvmin, float xvmax, float yvmax, float yvmin)
{
	Matrix4X4 viewport;
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

void BaseCamera::SetViewParams(Point3D * pvEyePt, Point3D * pvLookatPt)
{
}

void BaseCamera::SetProjParams(float fFOV, float fAspect, float fNearPlane, float fFarPlane)
{
}

void BaseCamera::LookAt(float Ex, float Ey, float Ez, float rx, float ry, float rz, float ux, float uy, float uz, float fx, float fy, float fz)
{
	m_pos = Point3D(Ex, Ey, Ez);
	m_up = Vector3D(ux, uy, uz);
	m_right = Vector3D(rx, ry, rz);

	float CAMERA_M[4][4];

	CAMERA_M[0][0] = rx;
	CAMERA_M[0][1] = ux;
	CAMERA_M[0][2] = fx;
	CAMERA_M[0][3] = Ex;

	CAMERA_M[1][0] = ry;
	CAMERA_M[1][1] = uy;
	CAMERA_M[1][2] = fy;
	CAMERA_M[1][3] = Ey;

	CAMERA_M[2][0] = rz;
	CAMERA_M[2][1] = uz;
	CAMERA_M[2][2] = fz;
	CAMERA_M[2][3] = Ez;

	CAMERA_M[3][0] = 0.0f;
	CAMERA_M[3][1] = 0.0f;
	CAMERA_M[3][2] = 0.0f;
	CAMERA_M[3][3] = 1;

	//求出逆矩阵，然后与世界坐标的v相乘
	m_View = Matrix4X4(&CAMERA_M[0][0]);
	m_View.Inverse(m_View);
}
void BaseCamera::LookAt(Point3D& point)
{
	m_dir = (point - m_pos).Normal();
	m_right = m_up.cross(m_dir);
	m_up = m_dir.cross(m_right);
	float CAMERA_M[][4] =
	{
		m_right[0], m_up[0], m_dir[0], m_pos[0],
		m_right[1], m_up[1], m_dir[1], m_pos[1],
		m_right[2], m_up[2], m_dir[2], m_pos[2],
		0.0f, 0.0f, 0.0f, 1.0f
	};
	m_View = Matrix4X4(&CAMERA_M[0][0]);
	m_View.Inverse(m_View);
}
Camera4DV1::Camera4DV1()
{
	m_pos = Point3D(0.0f, 0.0f, 0.0);
	m_dir = Vector3D::FORWARD;
	m_up = Vector3D::UP;
	m_right = Vector3D::RIGHT;
}
Camera4DV1::Camera4DV1(Point3D& point)
{
	m_pos = point;
	m_dir = Vector3D::FORWARD;
	m_up = Vector3D::UP;
	m_right = Vector3D::RIGHT;
}