#pragma once
#include "MathematicsLIB.h"
#include "Tuple.h"
#include "Test.h"
namespace Hikari
{
	 class Float4 : public Tuple<4, float>
	{
	public:
		inline Float4();
		inline Float4(const float f0, const float f1, const float f2, const float f3);
		inline Float4(const Float4& tuple);
		inline Float4(const XMFLOAT4& float4);
		inline Float4& operator=(const Float4& tuple);
		inline Float4& operator=(const Test4& tuple)
		{
			mTuple[0] = tuple.X;
			mTuple[1] = tuple.Y;
			mTuple[2] = tuple.Z;
			mTuple[3] = tuple.W;
			return *this;
		}

	};
	inline Float4::Float4()
	{
		mTuple[0] = 0;
		mTuple[1] = 0;
		mTuple[2] = 0;
		mTuple[3] = 0;
	}
	//----------------------------------------------------------------------------
	inline Float4::Float4(float f0, float f1, float f2, float f3)
	{
		mTuple[0] = f0;
		mTuple[1] = f1;
		mTuple[2] = f2;
		mTuple[3] = f3;
	}
	//----------------------------------------------------------------------------
	inline Float4::Float4(const Float4& tuple)
	{
		mTuple[0] = tuple.mTuple[0];
		mTuple[1] = tuple.mTuple[1];
		mTuple[2] = tuple.mTuple[2];
		mTuple[3] = tuple.mTuple[3];
	}
	//----------------------------------------------------------------------------
	inline Float4& Float4::operator= (const Float4& tuple)
	{
		mTuple[0] = tuple.mTuple[0];
		mTuple[1] = tuple.mTuple[1];
		mTuple[2] = tuple.mTuple[2];
		mTuple[3] = tuple.mTuple[3];
		return *this;
	}
	//----------------------------------------------------------------------------
	inline Float4::Float4(const XMFLOAT4& float4)
	{
		mTuple[0] = float4.x;
		mTuple[1] = float4.y;
		mTuple[2] = float4.z;
		mTuple[3] = float4.w;
	}
}