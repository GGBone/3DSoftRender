#pragma once
#include "MathematicsLIB.h"

namespace Hikari
{
	class HPoint
	{
	protected:
		float M[4];
	public:
		HPoint();
		HPoint(float x, float y, float z, float w);
		HPoint(const HPoint& v);
		~HPoint();

		inline const float& operator[](int index) const;
		inline float& operator[](int i);
		inline operator const float*() const;
		inline operator float*();

		inline float X() const;
		inline float Y() const;
		inline float Z() const;
		inline float W() const;

		inline float& X();
		inline float& Y();
		inline float& Z();
		inline float& W();

		HPoint& operator=(const HPoint&);

		bool operator==(const HPoint& pnt) const;
		bool operator!=(const HPoint& pnt) const;
		bool operator<(const HPoint& pnt) const;
		bool operator<=(const HPoint& pnt) const;
		bool operator>(const HPoint& pnt) const;
		bool operator>=(const HPoint& pnt) const;
	};

#include "HPoint.inl"
}
