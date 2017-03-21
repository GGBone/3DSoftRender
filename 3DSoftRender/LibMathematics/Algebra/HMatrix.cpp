
#include "MathematicsLIB.h"
#include "HMatrix.h"
using namespace Hikari;

//const HMatrix HMatrix::ZERO(true);
//const HMatrix HMatrix::IDENTITY(false);

Hikari::HMatrix::HMatrix()
{
}

Hikari::HMatrix::HMatrix(float* m, bool rowMajor)
{
	M[0] = m[0];
	M[1] = m[1];
	M[2] = m[2];
	M[3] = m[3];
	M[4] = m[4];
	M[5] = m[5];
	M[6] = m[6];
	M[7] = m[7];
	M[8] = m[8];
	M[9] = m[9];
	M[10] = m[10];
	M[11] = m[11];
	M[12] = m[12];
	M[13] = m[13];
	M[14] = m[14];
	M[15] = m[15];
}

HMatrix::HMatrix(bool makeZero)
{
	if (makeZero)
	{
		MakeZero();
	}
	else
	{
		MakeIdentity();
	}
}
void HMatrix::MakeZero()
{

	M[0] = 0.0f;
	M[1] = 0.0f;
	M[2] = 0.0f;
	M[3] = 0.0f;
	M[4] = 0.0f;
	M[5] = 0.0f;
	M[6] = 0.0f;
	M[7] = 0.0f;
	M[8] = 0.0f;
	M[9] = 0.0f;
	M[10] = 0.0f;
	M[11] = 0.0f;
	M[12] = 0.0f;
	M[13] = 0.0f;
	M[14] = 0.0f;
	M[15] = 0.0f;
}
void HMatrix::MakeIdentity()
{
	M[0] = 1.0f;
	M[1] = 0.0f;
	M[2] = 0.0f;
	M[3] = 0.0f;
	M[4] = 0.0f;
	M[5] = 1.0f;
	M[6] = 0.0f;
	M[7] = 0.0f;
	M[8] = 0.0f;
	M[9] = 0.0f;
	M[10] = 1.0f;
	M[11] = 0.0f;
	M[12] = 0.0f;
	M[13] = 0.0f;
	M[14] = 0.0f;
	M[15] = 1.0f;
}
Hikari::HMatrix::HMatrix(const HMatrix & m)
{
	if (this == &m)
		return;
	memcpy_s(M, sizeof(M),m.M,sizeof(m.M));
}

Hikari::HMatrix::HMatrix(const Matrix3f & mat)
{
	/*memcpy(M, &mat.GetRow(0), sizeof(M) / 4);
	memcpy(M + 4, &mat.GetRow(1), sizeof(M) / 4);
	memcpy(M + 8, &mat.GetRow(2), sizeof(M) / 4);
	memcpy(M + 12, &AVector::ZERO, sizeof(M) / 4);*/
}

Hikari::HMatrix::HMatrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	M[0] = m00;
	M[1] = m01;
	M[2] = m02;
	M[3] = m03;
	M[4] = m10;
	M[5] = m11;
	M[6] = m12;
	M[7] = m13;
	M[8] = m20;
	M[9] = m21;
	M[10] = m22;
	M[11] = m23;
	M[12] = m30;
	M[13] = m31;
	M[14] = m32;
	M[15] = m33;
}

HMatrix & Hikari::HMatrix::operator=(const HMatrix & m)
{
	// TODO: insert return statement here
	memcpy_s(M, sizeof(M), m.M, sizeof(m.M));
	return *this;
}

HMatrix Hikari::HMatrix::operator*(const HMatrix & mat) const
{
	return HMatrix(
		M[0] * mat.M[0] +
		M[1] * mat.M[4] +
		M[2] * mat.M[8] +
		M[3] * mat.M[12],

		M[0] * mat.M[1] +
		M[1] * mat.M[5] +
		M[2] * mat.M[9] +
		M[3] * mat.M[13],

		M[0] * mat.M[2] +
		M[1] * mat.M[6] +
		M[2] * mat.M[10] +
		M[3] * mat.M[14],

		M[0] * mat.M[3] +
		M[1] * mat.M[7] +
		M[2] * mat.M[11] +
		M[3] * mat.M[15],

		M[4] * mat.M[0] +
		M[5] * mat.M[4] +
		M[6] * mat.M[8] +
		M[7] * mat.M[12],

		M[4] * mat.M[1] +
		M[5] * mat.M[5] +
		M[6] * mat.M[9] +
		M[7] * mat.M[13],

		M[4] * mat.M[2] +
		M[5] * mat.M[6] +
		M[6] * mat.M[10] +
		M[7] * mat.M[14],

		M[4] * mat.M[3] +
		M[5] * mat.M[7] +
		M[6] * mat.M[11] +
		M[7] * mat.M[15],

		M[8] * mat.M[0] +
		M[9] * mat.M[4] +
		M[10] * mat.M[8] +
		M[11] * mat.M[12],

		M[8] * mat.M[1] +
		M[9] * mat.M[5] +
		M[10] * mat.M[9] +
		M[11] * mat.M[13],

		M[8] * mat.M[2] +
		M[9] * mat.M[6] +
		M[10] * mat.M[10] +
		M[11] * mat.M[14],

		M[8] * mat.M[3] +
		M[9] * mat.M[7] +
		M[10] * mat.M[11] +
		M[11] * mat.M[15],

		M[12] * mat.M[0] +
		M[13] * mat.M[4] +
		M[14] * mat.M[8] +
		M[15] * mat.M[12],

		M[12] * mat.M[1] +
		M[13] * mat.M[5] +
		M[14] * mat.M[9] +
		M[15] * mat.M[13],

		M[12] * mat.M[2] +
		M[13] * mat.M[6] +
		M[14] * mat.M[10] +
		M[15] * mat.M[14],

		M[12] * mat.M[3] +
		M[13] * mat.M[7] +
		M[14] * mat.M[11] +
		M[15] * mat.M[15]);
}

APoint Hikari::HMatrix::operator*(const APoint & p) const
{
	return APoint(
		M[0] * p[0] +
		M[1] * p[1] +
		M[2] * p[2] +
		M[3],

		M[4] * p[0] +
		M[5] * p[1] +
		M[6] * p[2] +
		M[7],

		M[8] * p[0] +
		M[9] * p[1] +
		M[10] * p[2] +
		M[11]);
}

AVector Hikari::HMatrix::operator*(const AVector & p) const
{
	return AVector(
		p[0] * *this[0][0] + p[1] * *this[0][1] + p[2] * *this[0][2] + 1 * *this[3][0],
		p[0] * *this[1][0] + p[1] * *this[1][1] + p[2] * *this[1][2] + 1 * *this[3][1],
		p[0] * *this[2][0] + p[1] * *this[2][1] + p[2] * *this[2][2] + 1 * *this[3][2]);

}

HPoint Hikari::operator*(const HPoint &p, const HMatrix & mat)
{
	return HPoint(
		p[0] * mat[0][0] + p[1] * mat[1][0] + p[2] * mat[2][0] + p[3] * mat[3][0],
		p[0] * mat[0][1] + p[1] * mat[1][1] + p[2] * mat[2][1] + p[3] * mat[3][1],
		p[0] * mat[0][2] + p[1] * mat[1][2] + p[2] * mat[2][2] + p[3] * mat[3][2],
		p[0] * mat[0][3] + p[1] * mat[1][3] + p[2] * mat[2][3] + p[3] * mat[3][3]);
}

HMatrix Hikari::HMatrix::Inverse(const float epsilon) const
{
	float a0 = M[0] * M[5] - M[1] * M[4];
	float a1 = M[0] * M[6] - M[2] * M[4];
	float a2 = M[0] * M[7] - M[3] * M[4];
	float a3 = M[1] * M[6] - M[2] * M[5];
	float a4 = M[1] * M[7] - M[3] * M[5];
	float a5 = M[2] * M[7] - M[3] * M[6];
	float b0 = M[8] * M[13] - M[9] * M[12];
	float b1 = M[8] * M[14] - M[10] * M[12];
	float b2 = M[8] * M[15] - M[11] * M[12];
	float b3 = M[9] * M[14] - M[10] * M[13];
	float b4 = M[9] * M[15] - M[11] * M[13];
	float b5 = M[10] * M[15] - M[11] * M[14];

	float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	if (fabsf(det) <= epsilon)
	{
		//return ZERO;
	}

	HMatrix inverse;
	inverse.M[0] = +M[5] * b5 - M[6] * b4 + M[7] * b3;
	inverse.M[4] = -M[4] * b5 + M[6] * b2 - M[7] * b1;
	inverse.M[8] = +M[4] * b4 - M[5] * b2 + M[7] * b0;
	inverse.M[12] = -M[4] * b3 + M[5] * b1 - M[6] * b0;
	inverse.M[1] = -M[1] * b5 + M[2] * b4 - M[3] * b3;
	inverse.M[5] = +M[0] * b5 - M[2] * b2 + M[3] * b1;
	inverse.M[9] = -M[0] * b4 + M[1] * b2 - M[3] * b0;
	inverse.M[13] = +M[0] * b3 - M[1] * b1 + M[2] * b0;
	inverse.M[2] = +M[13] * a5 - M[14] * a4 + M[15] * a3;
	inverse.M[6] = -M[12] * a5 + M[14] * a2 - M[15] * a1;
	inverse.M[10] = +M[12] * a4 - M[13] * a2 + M[15] * a0;
	inverse.M[14] = -M[12] * a3 + M[13] * a1 - M[14] * a0;
	inverse.M[3] = -M[9] * a5 + M[10] * a4 - M[11] * a3;
	inverse.M[7] = +M[8] * a5 - M[10] * a2 + M[11] * a1;
	inverse.M[11] = -M[8] * a4 + M[9] * a2 - M[11] * a0;
	inverse.M[15] = +M[8] * a3 - M[9] * a1 + M[10] * a0;

	float invDet = 1.0f / det;
	inverse.M[0] *= invDet;
	inverse.M[1] *= invDet;
	inverse.M[2] *= invDet;
	inverse.M[3] *= invDet;
	inverse.M[4] *= invDet;
	inverse.M[5] *= invDet;
	inverse.M[6] *= invDet;
	inverse.M[7] *= invDet;
	inverse.M[8] *= invDet;
	inverse.M[9] *= invDet;
	inverse.M[10] *= invDet;
	inverse.M[11] *= invDet;
	inverse.M[12] *= invDet;
	inverse.M[13] *= invDet;
	inverse.M[14] *= invDet;
	inverse.M[15] *= invDet;

	return inverse;
}
