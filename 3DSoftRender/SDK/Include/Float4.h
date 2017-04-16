#pragma once
#include "MathematicsLIB.h"
#include "Tuple.h"
namespace Hikari 
{
	class Float4 : public Tuple<4, float>
	{
	public:
		inline Float4();
		inline ~Float4();
		inline Float4(const float f0, const float f1, const float f2, const float f3);
		inline Float4(const Float4& tuple);

		inline Float4& operator=(const Float4& tuple);

		template <class Archive>
		void serialize(Archive& archive, const unsigned int version)
		{
			archive & BOOST_SERIALIZATION_NVP(mTuple[0]);
			archive & BOOST_SERIALIZATION_NVP(mTuple[1]);
			archive & BOOST_SERIALIZATION_NVP(mTuple[2]);
			archive & BOOST_SERIALIZATION_NVP(mTuple[3]);
		}
	};
#include "Float4.inl"
}