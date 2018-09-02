inline const float& HPoint::operator[](int index) const
{
	return M[index];
}

inline float& HPoint::operator[](int i)
{
	// TODO: insert return statement here
	return M[i];
}

inline HPoint::operator const float*() const
{
	return M;
}

inline HPoint::operator float*()
{
	return M;
}

inline float HPoint::X() const
{
	return M[0];
}

inline float HPoint::Y() const
{
	return M[1];
}

inline float HPoint::Z() const
{
	return M[2];
}

inline float HPoint::W() const
{
	return M[3];
}

inline float& HPoint::X()
{
	// TODO: insert return statement here
	return M[0];
}

inline float& HPoint::Y()
{
	// TODO: insert return statement here
	return M[1];
}

inline float& HPoint::Z()
{
	// TODO: insert return statement here
	return M[2];
}

inline float& HPoint::W()
{
	// TODO: insert return statement here
	return M[3];
}
