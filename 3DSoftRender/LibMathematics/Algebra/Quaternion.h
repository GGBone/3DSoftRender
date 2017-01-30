#pragma once
class Quaternation
{
private:
	float q;
	Vector3D qv;
	float w, x, y, z;
public:
	Quaternation operator+(Quaternation& q1);
	Quaternation operator-(Quaternation& q1);
	Quaternation operator*(Quaternation& q1);
	Quaternation conjugate(Quaternation& q1);
	void Normalize(Quaternation& q);
	void Normalize();
	void SetIdentity()
	{
		q = 0.0f;
		qv = Vector3D(0, 0, 0);
		w = 0;
		x = 0;
		y = 0;
		z = 0;
	}
	void Quat_Unit_Inverse();
	void Quat_Inverse();
	Quaternation Vector3D_To_Quat(Vector3D& vector);
	Quaternation Vector4D_To_Quat(Vector4D& vector);

};