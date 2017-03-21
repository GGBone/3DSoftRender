template<typename Real>
inline Hikari::Matrix3<Real>::Matrix3(bool ISZero)
{
	if (ISZero)
	{
		Zero();
	}
	else
	{
		Identity();
	}
}

template<typename Real>
Hikari::Matrix3<Real>::Matrix3(const Matrix3 & mat)
{
	memcpy(mEntry, mat.mEntry, sizeof(mEntry));
}

template<typename Real>
Hikari::Matrix3<Real>::Matrix3(Real m00, Real m01, Real m02, Real m10, Real m11, Real m12, Real m20, Real m21, Real m22)
{
	mEntry[0] = m00;
	mEntry[1] = m01;
	mEntry[2] = m02;
	mEntry[3] = m10;
	mEntry[4] = m11;
	mEntry[5] = m12;
	mEntry[6] = m20;
	mEntry[7] = m21;
	mEntry[8] = m22;
}

template<typename Real>
Hikari::Matrix3<Real>::Matrix3(const Real entry[9], bool rowMajor)
{
	if (rowMajor)
	{
		mEntry[0] = entry[0];
		mEntry[1] = entry[1];
		mEntry[2] = entry[2];
		mEntry[3] = entry[3];
		mEntry[4] = entry[4];
		mEntry[5] = entry[5];
		mEntry[6] = entry[6];
		mEntry[7] = entry[7];
		mEntry[8] = entry[8];
	}
	else
	{
		mEntry[0] = entry[0];
		mEntry[3] = entry[1];
		mEntry[6] = entry[2];
		mEntry[1] = entry[3];
		mEntry[4] = entry[4];
		mEntry[7] = entry[5];
		mEntry[2] = entry[6];
		mEntry[5] = entry[7];
		mEntry[8] = entry[8];
	}
}

template<typename Real>
inline Hikari::Matrix3<Real>::Matrix3(const Vector3<Real>& u, const Vector3<Real>& v, const Vector3<Real>& w, bool columns)
{
}

template<typename Real>
inline Hikari::Matrix3<Real>::Matrix3(const Vector3<Real>* v, bool columns)
{
	if (columns)
	{

	}
	else
	{
		mEntry[0] = v[0][0];
		mEntry[1] = v[0][1];
		mEntry[2] = v[0][2];

		mEntry[3] = v[1][0];
		mEntry[4] = v[1][1];
		mEntry[5] = v[1][2];

		mEntry[6] = v[2][0];
		mEntry[7] = v[2][1];
		mEntry[8] = v[2][2];
	}
}

template<typename Real>
inline Hikari::Matrix3<Real>::Matrix3(Real m00, Real m11, Real m22)
{
}

template<typename Real>
Hikari::Matrix3<Real>::Matrix3(const Vector3<Real>& axis, Real angle)
{
	MakeRotation(axis, angle);
}

template<typename Real>
Hikari::Matrix3<Real>::Matrix3(const Vector3<Real>& u, const Vector3<Real>& v)
{
}

template<typename Real>
Matrix3<Real> & Hikari::Matrix3<Real>::operator=(const Matrix3 & m)
{
	// TODO: insert return statement here
	mEntry[0] = mat.mEntry[0];
	mEntry[1] = mat.mEntry[1];
	mEntry[2] = mat.mEntry[2];
	mEntry[3] = mat.mEntry[3];
	mEntry[4] = mat.mEntry[4];
	mEntry[5] = mat.mEntry[5];
	mEntry[6] = mat.mEntry[6];
	mEntry[7] = mat.mEntry[7];
	mEntry[8] = mat.mEntry[8];
	return *this;
}

template<typename Real>
Matrix3<Real>& Hikari::Matrix3<Real>::Zero()
{
	// TODO: insert return statement here
	mEntry[0] = (Real)0;
	mEntry[1] = (Real)0;
	mEntry[2] = (Real)0;
	mEntry[3] = (Real)0;
	mEntry[4] = (Real)0;
	mEntry[5] = (Real)0;
	mEntry[6] = (Real)0;
	mEntry[7] = (Real)0;
	mEntry[8] = (Real)0;
	return *this;
}

template<typename Real>
inline Matrix3<Real>& Matrix3<Real>::Identity()
{
	// TODO: insert return statement here
	mEntry[0] = (Real)1;
	mEntry[1] = (Real)0;
	mEntry[2] = (Real)0;
	mEntry[3] = (Real)0;
	mEntry[4] = (Real)1;
	mEntry[5] = (Real)0;
	mEntry[6] = (Real)0;
	mEntry[7] = (Real)0;
	mEntry[8] = (Real)1;
	return *this;
}

template<typename Real>
Matrix3<Real> & Hikari::Matrix3<Real>::MakeDiagonal(Real m00, Real m11, Real m22)
{
	// TODO: insert return statement here
	return *this;
}

template<typename Real>
Matrix3<Real> & Matrix3<Real>::MakeRotation(const Vector3<Real>& axis, Real angle)
{
	// TODO: insert return statement here
	Real cs = Math<Real>::Cos(angle);
	Real sn = Math<Real>::Sin(angle);
	Real oneMinusCos = ((Real)1) - cs;
	Real x2 = axis[0] * axis[0];
	Real y2 = axis[1] * axis[1];
	Real z2 = axis[2] * axis[2];
	Real xym = axis[0] * axis[1] * oneMinusCos;
	Real xzm = axis[0] * axis[2] * oneMinusCos;
	Real yzm = axis[1] * axis[2] * oneMinusCos;
	Real xSin = axis[0] * sn;
	Real ySin = axis[1] * sn;
	Real zSin = axis[2] * sn;

	mEntry[0] = x2*oneMinusCos + cs;
	mEntry[1] = xym - zSin;
	mEntry[2] = xzm + ySin;
	mEntry[3] = xym + zSin;
	mEntry[4] = y2*oneMinusCos + cs;
	mEntry[5] = yzm - xSin;
	mEntry[6] = xzm - ySin;
	mEntry[7] = yzm + xSin;
	mEntry[8] = z2*oneMinusCos + cs;
	return *this;
}

template<typename Real>
Matrix3<Real>& Matrix3<Real>::MakeTensorProduct(const Vector3<Real>& u, const Vector3<Real>& v)
{
	// TODO: insert return statement here
	return *this;
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator*(Real scalar) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator-(const Matrix3 & m) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator+(const Matrix3 & m) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator/(Real scalar) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator-() const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator+=(const Matrix3 & m) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator-=(const Matrix3 & m) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator/=(Real scalar) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator*=(Real scalar) const
{
	return Matrix3();
}

template<typename Real>
Vector3<Real> Hikari::Matrix3<Real>::operator*(const Vector3<Real>& vec) const
{
	return Vector3<Real>();
}

template<typename Real>
Real Hikari::Matrix3<Real>::QForm(const Vector3<Real>& u, const Vector3<Real>& v)
{
	return Real();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::Transpose() const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::operator*(const Matrix3 & m) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::Inverse(const Real epsilon) const
{
	return Matrix3();
}

template<typename Real>
Matrix3<Real> Hikari::Matrix3<Real>::Adjoint() const
{
	return Matrix3();
}

template<typename Real>
Real Hikari::Matrix3<Real>::Determinant() const
{
	return Real();
}

template<typename Real>
void Hikari::Matrix3<Real>::ExtractAxisAngle(Vector3<Real>& axis, Real & angle) const
{
}

template<typename Real>
void Hikari::Matrix3<Real>::Orthonormalize()
{
}

template<typename Real>
void Hikari::Matrix3<Real>::EigenDecomposition(Matrix3 & rot, Matrix3 & diag) const
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerXYZ(Real xAngle, Real yAngle, Real zAngle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerXZY(Real xAngle, Real zAngle, Real yAngle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerYXZ(Real yAngle, Real xAngle, Real zAngle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerYZX(Real yAngle, Real zAngle, Real xAngle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerZXY(Real zAngle, Real xAngle, Real yAngle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerZYX(Real zAngle, Real yAngle, Real xAngle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerXYX(Real x0Angle, Real yAngle, Real x1Angle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerXZX(Real x0Angle, Real zAngle, Real x1Angle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerYXY(Real y0Angle, Real xAngle, Real y1Angle)
{
}

template<typename Real>
void Hikari::Matrix3<Real>::MakeEulerYZY(Real y0Angle, Real zAngle, Real y1Angle)
{
}

template<typename Real>
inline void Hikari::Matrix3<Real>::MakeEulerZXZ(Real z0Angle, Real xAngle, Real z1Angle)
{
}

template<typename Real>
inline void Hikari::Matrix3<Real>::MakeEulerZYZ(Real z0Angle, Real yAngle, Real z1Angle)
{
}

template<typename Real>
Matrix3<Real> & Hikari::Matrix3<Real>::Slerp(Real t, const Matrix3 & rot0, const Matrix3 & rot1)
{
	// TODO: insert return statement here
	return *this;
}

typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;
template<typename Real>
Matrix3<Real> operator*(Real scalar, const Matrix3<Real>& mat)
{
	return Matrix3<Real>();
}
template<typename Real>
Vector3<Real> operator*(const Vector3<Real>& vec, const Matrix3<Real>& mat)
{
	return Vector3<Real>();
}
