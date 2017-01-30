#pragma once

class Vector3D
{
private:
	float M[3];
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	float operator*(const Vector3D&);
	Vector3D operator*(float c)const;
	friend Vector3D operator*(float c, Vector3D v);
	Vector3D cross(const Vector3D&);

	Vector3D(const Vector3D& v);
	Vector3D& operator = (Vector3D&);

	Vector3D& operator = (const Vector4D&);

	Vector3D operator+(const Vector3D& v)const;
	Vector3D operator-(Vector3D& v)const;
	float& operator[](int i)
	{
		return M[i];
	}

	Vector3D Normal()
	{
		float mod = sqrt(M[0] * M[0] + M[1] * M[1] + M[2] * M[2]);
		if (mod != 0)
			return Vector3D(M[0] / mod, M[1] / mod, M[2] / mod);
		return Vector3D(0.0f, 0.0f, 0.0f);
	}
	bool operator==(float a)
	{
		if (abs(a - M[0]) < 0.0001f)
		{
			return true;
		}
		return false;
	}
	static Vector3D Normal(Vector3D& v);
	friend class Matrix3X3;
	friend class Matrix4X4;
	static Vector3D UP;
	static Vector3D RIGHT;
	static Vector3D FORWARD;
};