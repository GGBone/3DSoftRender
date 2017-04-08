#include "Culler.h"

Hikari::Culler::Culler(const Camera4DV1 * camera)
{
}

Hikari::Culler::~Culler()
{
}

void Hikari::Culler::SetFrustum(const float * frustum)
{
}

inline const float * Hikari::Culler::GetFrustrum() const
{
	return nullptr;
}

void Hikari::Culler::Insert(Spatial * visible)
{
}

inline int Hikari::Culler::GetPlaneQuantity() const
{
	return 0;
}
