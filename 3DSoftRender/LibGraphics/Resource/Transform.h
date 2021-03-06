#pragma once
#include "Algebra/HMatrix.h"
#include "Algebra/AVector.h"

namespace Hikari
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void MakeIdentity();

		void MakeUnitScale();

		inline bool IsIdentity() const;
		inline bool IsRSMatrix() const;

		void SetRotate(const HMatrix& rotate);
		void SetMatrix(const HMatrix& matrix);
		void SetTranslate(const APoint& translate);
		void SetScale(const APoint& scale);
		void SetUniformScale(float scale);
		inline const HMatrix& GetRotate() const;
		inline const APoint& GetTranslate() const;
		inline const APoint& GetScale() const;

		bool IsUniformScale() const
		{
			return mIsRSMatrix && mIsUniformScale;
		}

		inline float GetUniformScale() const;
		static float GetNorm();
		inline APoint operator*(const APoint& point) const;
		inline AVector operator*(const AVector& vector) const;
		Transform operator*(const Transform& transform) const;
		inline const HMatrix& Matrix() const;
		const HMatrix& Inverse() const;
		const HMatrix& GetMatrix() const;
		static Transform InverseTransform();
		static const Transform IDENTITY;

		inline static int GetStreamingsize();
	private:
		void UpdateMatrix();

		//Invert the 3x3 upper-left
		static void Invert3x3(const HMatrix& mat, HMatrix& invMat);

		HMatrix mHMatrix;
		mutable HMatrix mInvHMatrix;

		HMatrix mMatrix; //LocalMatrix
		APoint mTranslate; //Translate
		APoint mScale; // Scale
		bool mIsIdentity, mIsRSMatrix, mIsUniformScale;

		mutable bool mInverseNeedsUpdate;
	};


	inline APoint Transform::operator*(const APoint& point) const
	{
		return mHMatrix * point;
	}

	AVector Transform::operator*(const AVector& vector) const
	{
		return mHMatrix * vector;
	}

	inline const HMatrix& Transform::Matrix() const
	{
		// TODO: 在此处插入 return 语句
		return mHMatrix;
	}
}
