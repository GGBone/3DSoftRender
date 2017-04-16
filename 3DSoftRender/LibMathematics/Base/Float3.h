#pragma once
#include "MathematicsLIB.h"
#include "Tuple.h"
namespace Hikari
{
	class Float3 :public Tuple<3, float>
	{
	public:
		inline Float3();
		inline ~Float3();
		inline Float3(float f0, float f1, float f2);
		inline Float3(const Float3& tuple);

		inline Float3& operator=(const Float3& tuple);

		template <class Archive>
		void serialize(Archive& archive, const unsigned int version)
		{
			archive & BOOST_SERIALIZATION_NVP(mTuple);

		}

	};
	inline Hikari::Float3::Float3()
	{
		mTuple[0] = 0.0f;
		mTuple[1] = 0.0f;
		mTuple[2] = 0.0f;
	}
	inline Hikari::Float3::~Float3()
	{
	}

	inline Hikari::Float3::Float3(float f0, float f1, float f2)
	{
		mTuple[0] = f0;
		mTuple[1] = f1;
		mTuple[2] = f2;
	}

	inline Hikari::Float3::Float3(const Float3 & tuple)
	{
		mTuple[0] = tuple.mTuple[0];
		mTuple[1] = tuple.mTuple[1];
		mTuple[2] = tuple.mTuple[2];
	}

	inline Float3 & Hikari::Float3::operator=(const Float3 & tuple)
	{
		// TODO: 在此处插入 return 语句
		mTuple[0] = tuple.mTuple[0];
		mTuple[1] = tuple.mTuple[1];
		mTuple[2] = tuple.mTuple[2];
		return *this;
	}

}