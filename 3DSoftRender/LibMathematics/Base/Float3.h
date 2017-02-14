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
	};
#include "Float3.inl"
}