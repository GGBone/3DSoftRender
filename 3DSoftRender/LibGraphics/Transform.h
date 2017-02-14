#pragma once
#include "GraphicsLib.h"
#include "HMatrix.h"
#include "HMath.h"
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

		inline const HMatrix& GetRotate()const;
		inline const HMatrix& GetTranslate()const;
		inline const APoint& GetScale()const;
		static const Transform IDENTITY;
		inline static int GetStreamingsize();
	private:
		void UpdateMatrix();

		//Invert the 3x3 upper-left
		static void Invert3x3(const HMatrix& mat, HMatrix& invMat);

		HMatrix mHmatrix;
		mutable HMatrix mInvHMatrix;

		HMatrix Matrix;		//LocalMatrix
		APoint mTranslate;//Translate
		APoint mScale; // Scale
		bool mIsIdentity, mIsRSMatrix, mIsUniformScale;

		mutable bool InverseNeedsUpdate;
	};
}