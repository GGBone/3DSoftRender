#pragma once
#include "Math\MathematicsLIB.h"
#include "Math\Algebra\HMath.h"
#include "Core\Tuple.h"
namespace Hikari
{
	template <typename Real>
	class Vector3 : public Tuple<3, Real>
	{
	public:
		//Construction
		Vector3();
		Vector3(const Vector3& vec);
		Vector3(const Tuple<3, Real>& tuple);
		Vector3(Real x, Real y, Real z);
		//Assignment
		Vector3& operator = (const Vector3& vec);
		Vector3& operator = (const Tuple<3, Real>& tuple);
		//Getter

		inline Real X()const;
		inline Real& X();

		inline Real Y()const;
		inline Real& Y();

		inline Real Z()const;
		inline Real& Z();

		//operations
		inline Vector3 operator+(const Vector3& v)const;
		inline Vector3 operator-(const Vector3& v)const;
		inline Vector3 operator*(Real scalar)const;
		inline Vector3 operator/(Real scalar)const;
		inline Vector3 operator- ()const;

		//Vector operation
		inline Real Length()const;
		inline Real SquaredLength()const;
		inline Real Dot(const Vector3& vec)const;
		inline Real Normalize(const Real epsion = 0.0000001f);

		static void ComputeExtremes(int numVectors, const Vector3* vectors,
			Vector3& vmin, Vector3& vmax);

		Vector3 Cross(const Vector3& vec)const;
		Vector3 UnitCross(const Vector3& vec) const;

		//To-Be Document
		static void Orthonormalize(Vector3& u, Vector3& v, Vector3& w);
		static void Orthonormalize(Vector3* v);

		static void GenerateOrthonormalBasis(Vector3& u, Vector3& v, Vector3& w);

		static void GenerateComplelentBasis(Vector3& u, Vector3& v, const Vector3& w);

		bool GetBarycentrics(const Vector3& v0, const Vector3& v1, const Vector3 v2,
			const Vector3& v3, Real bary[4], const Real epsion = (Real)0) const;

		struct Information
		{
			int mDimension;
			Real mMin[3], mMax[3];
			Real mMaxRange;

			Vector3 mOrigin;
			Vector3 mDirection[3];
			int mExtreme[4];
			bool mExtremeCCW;
		};

		static void GetInformation(int numPoints, const Vector3* points, Real epsilon, Information& info);

		Vector3 Normal()
		{
			float mod = sqrt(M[0] * M[0] + M[1] * M[1] + M[2] * M[2]);
			if (mod != 0)
				return Vector3(M[0] / mod, M[1] / mod, M[2] / mod);
			return Vector3(0.0f, 0.0f, 0.0f);
		}

		static Vector3 UP;
		static Vector3 RIGHT;
		static Vector3 FORWARD;

		template <class Archive>
		void serialize(Archive& archive, const unsigned int version)
		{
			archive & BOOST_SERIALIZATION_NVP(m_day);
			archive & BOOST_SERIALIZATION_NVP(m_month);
			archive & BOOST_SERIALIZATION_NVP(m_year);
		}

	protected:
		using Tuple<3, Real>::mTuple;
	};

	template <typename Real>
	inline Vector3<Real> operator* (Real scalar, const Vector3<Real>& vec);

	//debuging output
	template <typename Real>
	std::ostream& operator<< (std::ostream& outFile, const Vector3<Real>& vec);

#include "Vector3.inl"
	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<int> Vector3I;
	typedef Vector3<unsigned int> Vector3UI;

	
}