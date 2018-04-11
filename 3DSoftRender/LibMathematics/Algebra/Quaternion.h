#pragma once
#include "MathematicsLib.h"
#include "Math\Algebra\Vector3.h"

namespace Hikari
{

	class Quaternation
	{
	private:
		float q;
		Vector3f qv;
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
			qv = Vector3f(0, 0, 0);
			w = 0;
			x = 0;
			y = 0;
			z = 0;
		}
		void Quat_Unit_Inverse();
		void Quat_Inverse();
		Quaternation AVector_To_Quat(Vector3f& vector);
		Quaternation Vector4D_To_Quat(Vector3f& vector);

	};
}