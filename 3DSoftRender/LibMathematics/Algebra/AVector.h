#pragma once
#include "MathematicsLIB.h"
#include "Algebra/HPoint.h"
#include "Algebra/Vector3.h"

namespace Hikari
{
	//Affine Vector
	class APoint;
	class Float3;
	class Float4;

	class AVector : public HPoint
	{
	public:
		AVector();
		AVector(const AVector& vec);
		AVector(float x, float y, float z);
		AVector(const Float3& tuple);
		AVector(const Float4& tuple);

		AVector(const Vector3f& vec);
		~AVector();

		//Assignment
		AVector operator=(const AVector& vec);

		AVector operator-() const
		{
			return AVector(-M[0], -M[1], -M[2]);
		}

		AVector operator+(const APoint& vec) const;

		//operations
		AVector operator+(const AVector& vec) const;
		AVector operator-(const AVector& vec) const;
		AVector operator*(float scalar) const;
		AVector operator/(float scalar) const;

		friend AVector operator*(float scalar, const AVector& vec);

		//
		AVector operator+=(const AVector& vec);
		AVector operator-=(const AVector& vec);

		//Vector operations
		inline float Length() const;
		float SquaredLength() const;
		float Dot(const AVector& vec) const;
		inline float Normalize(float epsilon = 0.0000001f);
		AVector Cross(const AVector& vec) const;
		AVector UnitCross(const AVector& vec) const;

		static void Orthonormalize(AVector& vec0, AVector& vec1, AVector& vec2);
		static void Orthonormalize(AVector* vec);

		static void GenerateOrthonormalBasis(AVector& vec0, AVector& vec1,
		                                     AVector& vec2);

		static void GenerateComplementBasis(AVector& vec0, AVector& vec1,
		                                    const AVector& vec2);

		static const AVector ZERO;
		static const AVector UP;
		static const AVector RIGHT;
		static const AVector FORWARD;
	};

	inline float AVector::Normalize(const float epsilon)
	{
		float length = Length();
		if (length > epsilon)
		{
			float invLength = 1.0f / length;
			M[0] *= invLength;
			M[1] *= invLength;
			M[2] *= invLength;
		}
		else
		{
			length = 0.0f;
			M[0] = 0.0f;
			M[1] = .0f;
			M[2] = .0f;
		}
		return length;
	}

	inline float AVector::Length() const
	{
		float sqrtLength = M[0] * M[0] + M[1] * M[1] + M[2] * M[2];

		return sqrtf(sqrtLength);
	}
}
