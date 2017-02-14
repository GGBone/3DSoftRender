#include "HPoint.h"

inline const float& HPoint::operator[](int index) const
{
	return M[index];
}

inline float & Hikari::HPoint::operator[](int i)
{
	// TODO: insert return statement here
	return M[i];
}

inline Hikari::HPoint::operator const float*() const
{
	return M;
}

inline Hikari::HPoint::operator float*()
{
	return M;
}

inline float Hikari::HPoint::X() const
{
	return M[0];
}

inline float Hikari::HPoint::Y() const
{
	return M[1];
}

inline float Hikari::HPoint::Z() const
{
	return M[2];
}

inline float Hikari::HPoint::W() const
{
	return M[3];
}

inline float & Hikari::HPoint::X()
{
	// TODO: insert return statement here
	return M[0];
}

inline float & Hikari::HPoint::Y()
{
	// TODO: insert return statement here
	return M[1];
}

inline float & Hikari::HPoint::Z()
{
	// TODO: insert return statement here
	return M[2];
}

inline float & Hikari::HPoint::W()
{
	// TODO: insert return statement here
	return M[3];
}