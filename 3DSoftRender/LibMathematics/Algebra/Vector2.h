#pragma once
#include "MathematicsLIB.h"
#include "Tuple.h"
namespace Hikari
{
	template <typename Real>
	class Vector2 :public Tuple<2, Real>
	{
	public:
		Vector2(Real x, Real y);
		Vector2();
		Vector2(const Tuple<2, Real>& tuple);
		Vector2(const Vector2& vec);
		Real GetX()const;
		Real GetY()const;
		Real& GetX();
		Real& GetY();
	protected:
		using Tuple<2, Real>::mTuple;
	};
	//#include "Vector2.inl"
	template<typename Real>
	Hikari::Vector2<Real>::Vector2(Real x, Real y)
	{
		mTuble[0] = x;
		mTuple[1] = y;
	}
	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
}