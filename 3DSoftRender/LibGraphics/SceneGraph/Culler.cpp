#include "GraphicsPCH.h"
#include "Culler.h"

Hikari::Culler::Culler(const Camera* camera)
{
}

Hikari::Culler::~Culler()
= default;

void Hikari::Culler::SetFrustum(const float* frustum)
{
}

inline const float* Hikari::Culler::GetFrustrum()
{
	return nullptr;
}

void Hikari::Culler::Insert(Spatial* visible)
{
}

inline int Hikari::Culler::GetPlaneQuantity()
{
	return 0;
}
