#pragma once

class Matrix3X3
{
public:
	float M[3][3];
public:
	Matrix3X3();

	Matrix3X3(float* m);

	Matrix3X3(const Matrix3X3& m);

	Matrix3X3& operator=(const Matrix3X3& m);
	Matrix3X3& operator=(float m[]);

	Matrix3X3 operator*(const Matrix3X3& m)const;

	void operator*(Point2D&) const;
	void operator*(Point3D&) const;

	void operator*(Vector2D&) const;
	void operator*(Vector3D&) const;

	inline float& operator[](int i)
	{

	}

	void Tranvers();
	void Reflection(Vector3D N);
	inline float det()
	{
		return M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] + M[0][2] * M[2][1] * M[1][0]
			- M[0][2] * M[1][1] * M[2][0] - M[0][1] * M[1][0] * M[2][2] - M[0][0] * M[2][1] * M[1][2];
	}
	inline void setIdentity()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				M[i][j] = (i == j);
			}
		}
	}
};