#pragma once
#include "MathematicsLIB.h"
#include "Tuple.h"

namespace Hikari
{
	class Float1 : public Tuple<1, float>
	{
	public:
		Float1()
		{
			mTuple[0] = 0.0f;
			mTuple[1] = 0.0f;
		}

		~Float1() = default;

		Float1(float x, float y)
		{
			mTuple[0] = x;
			mTuple[1] = y;
		}

		Float1(const Float1& tuple)
		{
			mTuple[0] = tuple.mTuple[0];
		}

		Float1& operator=(const Float1& tuple)
		= default;
	};
}
