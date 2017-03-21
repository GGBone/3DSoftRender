#pragma once
#include "MathematicsLIB.h"
#include "Table.h"
#include "Vector3.h"
#include "HMath.h"
namespace Hikari
{
	template<typename Real>
	class Matrix3 : public Table<3, 3, Real>
	{
	public:
		Matrix3(bool Zero = true);

		Matrix3(const Matrix3& mat);

		Matrix3(Real m00, Real m01, Real m02,
			Real m10, Real m11, Real m12,
			Real m20, Real m21, Real m22);

		Matrix3(const Real entry[9], bool rowMajor = true);

		Matrix3(const Vector3<Real>& u, const Vector3<Real>& v,
			const Vector3<Real>& w, bool columns);

		Matrix3(const Vector3<Real>* v, bool columns);

		//diagonal matrix
		Matrix3(Real m00, Real m11, Real m22);

		Matrix3(const Vector3<Real>& axis, Real angle);

		Matrix3(const Vector3<Real>& u, const Vector3<Real>& v);


		Matrix3& operator=(const Matrix3& m);

		Matrix3& Zero();

		Matrix3& Identity();

		Matrix3& MakeDiagonal(Real m00, Real m11, Real m22);
		Matrix3& MakeRotation(const Vector3<Real>& axis, Real angle);
		Matrix3& MakeTensorProduct(const Vector3<Real>& u,
			const Vector3<Real>& v);

		Matrix3 operator*(Real scalar)const;
		Matrix3 operator-(const Matrix3& m)const;
		Matrix3 operator+(const Matrix3& m)const;
		Matrix3 operator/(Real scalar)const;
		Matrix3 operator-()const;

		Matrix3 operator+=(const Matrix3& m)const;
		Matrix3 operator-=(const Matrix3& m)const;
		Matrix3 operator/=(Real scalar)const;
		Matrix3 operator*=(Real scalar)const;

		Vector3<Real> operator* (const Vector3<Real>& vec)const;

		Real QForm(const Vector3<Real>& u, const Vector3<Real>& v);

		Matrix3 Transpose() const;

		Matrix3 operator*(const Matrix3& m)const;

		Matrix3 Inverse(const Real epsilon = (Real)0) const;
		Matrix3 Adjoint() const;
		Real Determinant() const;

		void ExtractAxisAngle(Vector3<Real>& axis, Real& angle) const;
		void Orthonormalize();
		void EigenDecomposition(Matrix3& rot, Matrix3& diag) const;

		void MakeEulerXYZ(Real xAngle, Real yAngle, Real zAngle);
		void MakeEulerXZY(Real xAngle, Real zAngle, Real yAngle);
		void MakeEulerYXZ(Real yAngle, Real xAngle, Real zAngle);
		void MakeEulerYZX(Real yAngle, Real zAngle, Real xAngle);
		void MakeEulerZXY(Real zAngle, Real xAngle, Real yAngle);
		void MakeEulerZYX(Real zAngle, Real yAngle, Real xAngle);
		void MakeEulerXYX(Real x0Angle, Real yAngle, Real x1Angle);
		void MakeEulerXZX(Real x0Angle, Real zAngle, Real x1Angle);
		void MakeEulerYXY(Real y0Angle, Real xAngle, Real y1Angle);
		void MakeEulerYZY(Real y0Angle, Real zAngle, Real y1Angle);
		void MakeEulerZXZ(Real z0Angle, Real xAngle, Real z1Angle);
		void MakeEulerZYZ(Real z0Angle, Real yAngle, Real z1Angle);

		inline float det()
		{
			return M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] + M[0][2] * M[2][1] * M[1][0]
				- M[0][2] * M[1][1] * M[2][0] - M[0][1] * M[1][0] * M[2][2] - M[0][0] * M[2][1] * M[1][2];
		}
		Matrix3& Slerp(Real t, const Matrix3& rot0, const Matrix3& rot1);
	protected:
		using Table<3, 3, Real>::mEntry;
	};

	template<typename Real>
	inline Matrix3<Real> operator*(Real scalar, const Matrix3<Real>&mat);

	template <typename Real>
	inline Vector3<Real> operator*(const Vector3<Real>& vec, const Matrix3<Real>& mat);
#include "Matrix3.inl"
}