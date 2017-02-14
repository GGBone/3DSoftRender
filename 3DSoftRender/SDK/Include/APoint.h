#pragma once
#include "MathematicsLIB.h"
#include "AVector.h"
namespace Hikari
{
	//Affine Point
	class APoint :public HPoint
	{
	public:
		APoint();
		APoint(const APoint& pnt);
		APoint(float x, float y, float z);
		APoint(const Float3& tuple);
		APoint(const Vector3f& pnt);
		~APoint();


		inline operator const Float3& () const;
		inline operator Float3&();
		inline operator const Vector3f&() const;
		inline operator Vector3f&();

		//Assignment
		APoint& operator=(const APoint& pnt);

		AVector operator-(const APoint& pnt)const;

		APoint operator+(const AVector& vec)const;
		APoint operator-(const AVector& vec)const;

		APoint operator+(const APoint& vec)const;
		APoint operator*(float scalar)const;

		friend APoint operator* (float scalar, const APoint& pnt);

		float Dot(const AVector& vec)const;
		static const APoint ORIGIN;//(0,0,0,1)
	};
}