#pragma once

class Matrix4X4
{
private:
	float M[4][4];
public:
	Matrix4X4();
	Matrix4X4(float* m);

	Matrix4X4(const Matrix4X4& m);

	Matrix4X4& operator=(const Matrix4X4& m);
	Matrix4X4& operator=(const Matrix3X3& m);

	Matrix4X4 operator*(const Matrix4X4& m)const;

	Point4D operator*(Point3D&) const;
	Point4D operator*(Point4D&) const;

	void operator*(Vector3D&) const;
	void operator*(Vector4D&) const;

	float& operator[](int i)
	{
		return M[i][i];
	}
	Matrix4X4 Inverse(Matrix4X4& matrix)const;


	//求出代数余子试
	inline float MStar(const Matrix4X4& m, int a, int b)const
	{
		Matrix3X3 temp;
		for (int i = 0, k = i; i < 3; i++, k++)
		{
			for (int j = 0, p = j; j < 3; j++, p++)
			{
				temp.M[i][j] = m.M[k][p];
				if (a == k)
					temp.M[i][j] = m.M[++k][p];
				if (b == p)
					temp.M[i][j] = m.M[k][++p];

			}
		}
		float det = temp.det();
		return det;
	}
	Matrix4X4& Tranvers();

	inline void setIdentity()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				M[i][j] = (i == j);
			}
		}
	}
};