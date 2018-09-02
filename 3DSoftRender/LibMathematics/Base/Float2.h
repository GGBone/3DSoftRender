#pragma once
#include "MathematicsLIB.h"
#include "Tuple.h"

namespace Hikari
{
	class Float2 : public Tuple<2, float>
	{
	public:
		Float2()
		{
			mTuple[0] = 0.0f;
			mTuple[1] = 0.0f;
		}

		~Float2()
		{
		}

		Float2(float x, float y)
		{
			mTuple[0] = x;
			mTuple[1] = y;
		}

		Float2(const Float2& tuple)
		{
			mTuple[0] = tuple.mTuple[0];
			mTuple[1] = tuple.mTuple[1];
		}

		Float2& operator=(const Float2& tuple)
		{
			mTuple[0] = tuple.mTuple[0];
			mTuple[1] = tuple.mTuple[1];
			return *this;
		}
	};
}
