template<typename Real>
inline Vector3<Real>::Vector3()
{
}
template<typename Real>
inline Vector3<Real>::Vector3(const Vector3 & vec)
{
	mTuple[0] = vec.mTuple[0];
	mTuple[1] = vec.mTuple[1];
	mTuple[2] = vec.mTuple[2];
}
template<typename Real>
inline Vector3<Real>::Vector3(const Tuple<3, Real>& tuple)
{
	mTuple[0] = tuple.mTuple[0];
	mTuple[1] = tuple.mTuple[1];
	mTuple[2] = tuple.mTuple[2];
}
template<typename Real>
inline Vector3<Real>::Vector3(Real x, Real y, Real z)
{
	mTuple[0] = x;
	mTuple[1] = y;
	mTuple[2] = z;
}
template<typename Real>
inline Vector3<Real> & Vector3<Real>::operator=(const Vector3 & vec)
{
	// TODO: 在此处插入 return 语句
	mTuple[0] = vec.mTuple[0];
	mTuple[1] = vec.mTuple[1];
	mTuple[2] = vec.mTuple[2];
	return *this;
}
template<typename Real>
inline Vector3<Real> & Vector3<Real>::operator=(const Tuple<3, Real>& tuple)
{
	// TODO: 在此处插入 return 语句
	mTuple[0] = tuple.mTuple[0];
	mTuple[1] = tuple.mTuple[1];
	mTuple[2] = tuple.mTuple[2];
	return *this;
}
template<typename Real>
inline Real Vector3<Real>::X() const
{
	return mTuple[0];
}
template<typename Real>
inline Real& Vector3<Real>::X()
{
	// TODO: 在此处插入 return 语句
	return mTuple[0];
}
template<typename Real>
inline Real Vector3<Real>::Y() const
{
	return mTuple[1];
}
template<typename Real>
inline Real & Vector3<Real>::Y()
{
	// TODO: 在此处插入 return 语句
	return mTuple[0];
}
template<typename Real>
inline Real Vector3<Real>::Z() const
{
	return mTuple[2];
}
template<typename Real>
inline Real & Vector3<Real>::Z()
{
	// TODO: 在此处插入 return 语句
	return mTuple[2];
}