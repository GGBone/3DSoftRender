#include <GraphicsPCH.h>
#include <Camera.h>
using namespace Hikari;
HMatrix Perspective(float a,float r,float f,float n)
{
	HMatrix temp
	(	(1.0f / (r*tanf(a / 2.0f))), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / (tanf(a / 2.0f)), 0.0f, 0.0f,
				0.0f, 0.0f, f / (f - n), 1.0f,
				0.0f, 0.0f, -n*f / (f - n), 0.0f
	);
	return temp;
}
HMatrix Ortho(float l,float r,float b,float t,float n,float f)
{
	HMatrix temp
	(2.0f/(r - l), 0.0f, 0.0f, -(r+l)/(r-l),
		0.0f, 2.0f/(t-b),.0f, 0.0f,
		0.0f, 0.0f, 1.0f/(f-n), -n/(f-n),
		0.0f, 0.0f,  0.0f, 1.0f
	);
	return temp;
}
Camera::Camera()
	: m_Translate(0,0,0)
	, m_PivotDistance(0)
	, m_bViewDirty(true)
	, m_bViewProjectionInverseDirty(true)
{}

void Camera::SetViewport(const Viewport& viewport)
{
	m_Viewport = viewport;
}

const Viewport& Camera::GetViewport() const
{
	return m_Viewport;
}

void Camera::SetProjectionRH(float fovy, float aspect, float zNear, float zFar)
{
	m_fVFOV = fovy;
	m_fAspect = aspect;
	m_fNear = zNear;
	m_fFar = zFar;
	
	m_ProjectionMatrix = Perspective(m_fVFOV, m_fAspect, m_fNear, m_fFar);
	
	m_bViewProjectionInverseDirty = true;
}

void Camera::SetProjectionLH(float fovy, float aspect, float zNear, float zFar)
{
	HMatrix fix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 1.0f
	);

	m_fVFOV = fovy;
	m_fAspect = aspect;
	m_fNear = zNear;
	m_fFar = zFar;

	//    m_ProjectionMatrix = fix * glm::perspective( fovy, aspect, zNear, zFar ); // * fix;	
	m_ProjectionMatrix = fix * Perspective(fovy, aspect, zNear, zFar);
	m_bViewProjectionInverseDirty = true;
}

float Camera::GetNearClipPlane() const
{
	return m_fNear;
}

float Camera::GetFarClipPlane() const
{
	return m_fFar;
}

void Camera::SetOrthographic(float left, float right, float top, float bottom)
{
	m_ProjectionMatrix = Ortho(left, right, bottom, top,0.1f,1000.0f);
	m_bViewProjectionInverseDirty = true;
}

void Camera::AddPitch(float fPitch, Space space)
{
	switch (space)
	{
	//case Space::Local:
	//	m_Rotate = glm::angleAxis(glm::radians(fPitch), m_Rotate * Vector3f(1, 0, 0)) * m_Rotate;
	//	break;
	//case Space::World:
	//	m_Rotate = glm::angleAxis(glm::radians(fPitch), Vector3f(1, 0, 0)) * m_Rotate;
	}

	m_bViewDirty = true;
}

void Camera::AddYaw(float fYaw, Space space)
{
	switch (space)
	{
	//case Space::Local:
	//	m_Rotate = glm::angleAxis(glm::radians(fYaw), m_Rotate * Vector3f(0, 1, 0)) * m_Rotate;
	//	break;
	//case Space::World:
	//	m_Rotate = glm::angleAxis(glm::radians(fYaw), Vector3f(0, 1, 0)) * m_Rotate;
	//	break;
	}

	m_bViewDirty = true;
}

void Camera::AddRoll(float fRoll, Space space)
{
	switch (space)
	{
	/*case Space::Local:
		m_Rotate = glm::angleAxis(glm::radians(fRoll), m_Rotate * Vector3f(0, 0, 1)) * m_Rotate;
		break;
	case Space::World:
		m_Rotate = glm::angleAxis(glm::radians(fRoll), Vector3f(0, 0, 1)) * m_Rotate;
		break;*/
	}
	m_bViewDirty = true;
}

void Camera::SetEulerAngles(const Vector3f& eulerAngles)
{
	//m_Rotate = Float4(glm::radians(eulerAngles));
	//m_bViewDirty = true;
}

void Camera::AddRotation(const Float4& deltaRot)
{
/*	m_Rotate = m_Rotate * deltaRot;*/
	m_bViewDirty = true;
}

void Camera::TranslateX(float x, Space space)
{
	/*switch (space)
	{
	case Camera::Space::Local:
		m_Translate += m_Rotate * Vector3f(x, 0, 0);
		break;
	case Camera::Space::World:
		m_Translate += Vector3f(x, 0, 0);
		break;
	}
	m_bViewDirty = true;*/
}

void Camera::TranslateY(float y, Space space)
{
	//switch (space)
	//{
	//case Space::Local:
	//	m_Translate += m_Rotate * Vector3f(0, y, 0);
	//	break;
	//case Space::World:
	//	m_Translate += Vector3f(0, y, 0);
	//	break;
	//}

	//m_bViewDirty = true;
}

void Camera::TranslateZ(float z, Space space)
{
	/*switch (space)
	{
	case Space::Local:
		m_Translate += m_Rotate * Vector3f(0, 0, z);
		break;
	case Space::World:
		m_Translate += Vector3f(0, 0, z);
		break;
	}

	m_bViewDirty = true;*/
}

void Camera::SetTranslate(const Vector3f& translate)
{
	m_Translate = translate;
	m_bViewDirty = true;
}

void Camera::SetRotate(float pitch, float yaw, float roll)
{
	//SetRotate(Vector3f(pitch, yaw, roll));
}

void Camera::SetRotate(const Vector3f& rotate)
{
	//SetRotate(Float4(glm::radians(rotate)));
}

void Camera::SetRotate(const Float4& rot)
{
	m_Rotate = rot;
	m_bViewDirty = true;
}

void Camera::SetPivotDistance(float pivotDistance)
{
	// Make sure pivot distance is always positive.
	//m_PivotDistance = std::max(pivotDistance, 0.0f);
	m_bViewDirty = true;
}

float Camera::GetPivotDistance() const
{
	return m_PivotDistance;
}

Vector3f Camera::GetPivotPoint() const
{
	// The camera actually pivots around its "translation" point.
	return m_Translate;
}


Vector3f Camera::GetTranslation() const
{
	return m_Translate;
}


Vector3f Camera::GetEulerAngles() const
{
	//return glm::degrees(glm::eulerAngles(m_Rotate));
	return Vector3f();
}

void Camera::UpdateViewMatrix()
{
	/*if (m_bViewDirty)
	{
		HMatrix translateMatrix = glm::translate(m_Translate);
		HMatrix rotationMatrix = glm::toMat4(m_Rotate);
		HMatrix pivotMatrix = glm::translate(Vector3f(0, 0, m_PivotDistance));

		m_ViewMatrix = glm::inverse(translateMatrix * rotationMatrix * pivotMatrix);

		m_bViewProjectionInverseDirty = true;
		m_bViewDirty = false;
	}*/
}

void Camera::UpdateViewProjectionInverse()
{
	UpdateViewMatrix();

	//if (m_bViewProjectionInverseDirty)
	//{
	//	m_ViewProjectionInverse = glm::inverse(m_ProjectionMatrix * m_ViewMatrix);
	//	m_bViewProjectionInverseDirty = false;
	//}
}

void Camera::SetViewMatrix(const HMatrix& viewMatrix)
{
	// Inverse the view matrix to get the world matrix of the camera
	//HMatrix inverseView = glm::inverse(viewMatrix);

	//// Extract the translation
	//m_Translate = Vector3f(inverseView[3]);

	//// Extract the top-left 3x3 matrix to decompose the scale and rotation
	//glm::mat3 tmp = glm::mat3(inverseView);

	//// TODO: I don't know if any of the scales are negative.
	//// I have to figure out how can I reliably determine if any of the scales are negative?
	//float sx = glm::length(tmp[0]);
	//float sy = glm::length(tmp[1]);
	//float sz = glm::length(tmp[2]);

	//glm::mat3 invScale = glm::mat3(glm::scale(Vector3f(1.0f / sx, 1.0f / sy, 1.0f / sz)));
	//// This will remove the scale factor (if there is one) so we can extract
	//// the unit quaternion.
	//tmp = tmp * invScale;
	//m_Rotate = glm::toQuat(tmp);

	//// The view matrix needs to be rebuilt from the rotation and translation components.
	//m_bViewDirty = true;
}

HMatrix Camera::GetViewMatrix() const
{
	const_cast<Camera*>(this)->UpdateViewMatrix();
	return m_ViewMatrix;
}

void Camera::SetProjectionMatrix(const HMatrix& projectionMatrix)
{
	// TODO: Decompose the projection matrix?
	m_ProjectionMatrix = projectionMatrix;
	m_bViewProjectionInverseDirty = true;
}

HMatrix Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

HMatrix Camera::GetViewProjectionInverseMatrix() const
{
	const_cast<Camera*>(this)->UpdateViewProjectionInverse();
	return m_ViewProjectionInverse;
}
/*

Ray Camera::ScreenPointToRay(const Fl& screenPoint) const
{
	//HMatrix clipToWorld = GetViewProjectionInverseMatrix();
	//Float4 clipPoint = Float4(screenPoint, 1, 1);
	//clipPoint.x = (screenPoint.x - m_Viewport.X) / m_Viewport.Width;
	//clipPoint.y = 1.0f - (screenPoint.y - m_Viewport.Y) / m_Viewport.Height;
	//clipPoint = clipPoint * 2.0f - 1.0f;

	//Vector3f p0 = m_Translate;
	//Float4 worldSpace = clipToWorld * clipPoint;
	//Vector3f p1 = Vector3f(worldSpace / worldSpace.w); // glm::unProject( Vector3f( screenPoint, 0), m_ViewMatrix, m_ProjectionMatrix, Float4( m_Viewport.X, m_Viewport.Y, m_Viewport.Width, m_Viewport.Height ) );

	//return Ray(p0, glm::normalize(p1 - p0));
}

Vector3f Camera::ProjectOntoUnitSphere(glm::ivec2 screenPos)
{
	// Map the screen coordinates so that (0, 0) is the center of the viewport.
	screenPos -= glm::vec2(m_Viewport.Width, m_Viewport.Height) * 0.5f;

	float x, y, z;
	// The radius of the unit sphere is 1/2 of the shortest dimension of the viewport.
	float radius = glm::min(m_Viewport.Width, m_Viewport.Height) * 0.5f;

	// Now normalize the screen coordinates into the range [-1 .. 1].
	x = screenPos.x / radius;
	// The y-coordinate has to be inverted so that +1 is the top of the unit sphere
	// and -1 is the bottom of the unit sphere.
	y = -(screenPos.y / radius);

	float length_sqr = (x * x) + (y * y);

	// If the screen point is mapped outside of the unit sphere
	if (length_sqr > 1.0f)
	{
		float invLength = glm::inversesqrt(length_sqr);

		// Return the normalized point that is closest to the outside of the unit sphere.
		x *= invLength;
		y *= invLength;
		z = 0.0f;
	}
	else
	{
		// The point is on the inside of the unit sphere.
		z = glm::sqrt(1.0f - length_sqr);
		// If we are "inside" the unit sphere, then 
		// invert the z component.
		// In a right-handed coordinate system, the "+z" axis of the unit
		// sphere points towards the viewer. If we are in the Unit sphere, we
		// want to project the point to the inside of the sphere and in this case
		// the z-axis we want to project on points away from the viewer (-z).
		if (m_PivotDistance <= 0.0f)
		{
			z = -z;
		}
	}

	return Vector3f(x, y, z);
}

void Camera::OnMousePressed(MouseButtonEventArgs& e)
{
	m_PreviousPoint = ProjectOntoUnitSphere(glm::ivec2(e.X, e.Y));
}

void Camera::OnMouseMoved(MouseMotionEventArgs& e)
{
	Vector3f currentPoint = ProjectOntoUnitSphere(glm::ivec2(e.X, e.Y));

	AddRotation(Float4(currentPoint, m_PreviousPoint));

	//// Compute the axis of rotation.
	//Vector3f axis = glm::cross( currentPoint, m_PreviousPoint );

	//float length_sqr = glm::length2( axis );

	//// If the rotation axis is too short, don't rotate.
	//if ( length_sqr > 0.0f )
	//{
	//    // Normalize the axis of rotation
	//    //axis *= glm::inversesqrt( length_sqr );

	//    // The dot product between the two vectors gives the angle of rotation.
	//    float dotProduct = glm::dot( m_PreviousPoint, currentPoint );
	//    if ( dotProduct <= 1 && dotProduct >= -1 )
	//    {
	//        // Add the resulting rotation to our current rotation
	//        Float4 deltaRotate = glm::angleAxis( glm::acos( dotProduct ), glm::normalize(axis) );
	//        AddRotation( deltaRotate );
	//    }
	//}

	m_PreviousPoint = currentPoint;
}
*/