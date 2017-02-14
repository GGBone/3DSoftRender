#include "MathematicsLIB.h"
#include "HMatrix.h"
using namespace Hikari;
Hikari::HMatrix::HMatrix()
{
}

Hikari::HMatrix::HMatrix(float* m)
{
	memcpy_s(M, sizeof(M), m, sizeof(M));
}

HMatrix & Hikari::HMatrix::operator=(const HMatrix & m)
{
	// TODO: insert return statement here
	memcpy_s(M, sizeof(M), m.M, sizeof(m.M));
	return *this;
}

HPoint Hikari::operator*(const HPoint &p, const HMatrix & mat)
{
	return HPoint(
		p[0] * mat[0][0] + p[1] * mat[1][0] + p[2] * mat[2][0] + p[3] * mat[3][0],
		p[0] * mat[0][1] + p[1] * mat[1][1] + p[2] * mat[2][1] + p[3] * mat[3][1],
		p[0] * mat[0][2] + p[1] * mat[1][2] + p[2] * mat[2][2] + p[3] * mat[3][2],
		p[0] * mat[0][3] + p[1] * mat[1][3] + p[2] * mat[2][3] + p[3] * mat[3][3]);
}