#pragma once
#include "MathematicsLIB.h"
#include "Algebra/APoint.h"
#include "Algebra/HPoint.h"
#include "Algebra/Matrix3.h"

namespace Hikari
{
	class HMatrix
	{
	private:
		float M[16];
	public:
		HMatrix();
		HMatrix(float* m, bool rowMajor = true);
		HMatrix(bool makeZero);
		HMatrix(const HMatrix& m);
		HMatrix(const Matrix3f& mat);

		const float* operator *()
		{
			return M;
		}

		HMatrix(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		HMatrix& operator=(const HMatrix& m);
		HMatrix& operator=(const XMFLOAT4X4& m);
		HMatrix operator*(const HMatrix& m) const;

		friend HPoint operator*(const HPoint&, const HMatrix& mat); //v*M
		APoint operator*(const APoint& p) const; //M*v

		AVector operator*(const AVector& p) const;

		// Compute a quadratic forms.
		float QForm(const HPoint& p0, const HPoint& p1) const; // p0^T*M*p1

		HMatrix TimesDiagonal(const APoint& diag) const;
		// set the transformation to a reflection matrix through a specified
		// plane.  The plane has an 'origin' point and a unit-length 'normal'.
		void MakeReflection(const APoint& origin, const AVector& normal);

		const float* operator[](int row) const
		{
			return &M[row * 4];
		}

		float* operator[](int row)
		{
			return &M[row * 4];
		}

		HMatrix Inverse(float epsilon = 0.0f) const; //// M^{-1}
		float Determinant() const;
		HMatrix Transpose() const;
		HMatrix Adjoint() const;
		void Orthonormalize(); // applies to 3x3 upper-left block of M
		//求出代数余子试
		static float MStar(const HMatrix& m, int a, int b)
		{
			HMatrix temp;
			for (int i = 0, k = i; i < 3; i++, k++)
			{
				for (int j = 0, p = j; j < 3; j++, p++)
				{
					temp.M[i * 4 + j] = m.M[k * 4 + p];
					if (a == k)
						temp.M[i * 4 + j] = m.M[(++k) * 4 + p];
					if (b == p)
						temp.M[i * 4 + j] = m.M[k * 4 + (++p)];
				}
			}
			float det = temp.Determinant();
			return det;
		}

		HMatrix& Tranvers();
		void MakeZero();
		void MakeIdentity();
		static const HMatrix ZERO;
		static const HMatrix IDENTITY;
	};
}
