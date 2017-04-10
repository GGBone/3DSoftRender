#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Float4.h"
#include "Vector2.h"
#include "APoint.h"

namespace Hikari
{
	class Light : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		enum Type
		{
			LT_AMBIENT,
			LT_DIRECTION,
			LT_POINT,
			LT_SPOT,
			LT_QUANTITY
		};

		Light(Type etype = LT_AMBIENT)
			:Ambient(Float4(0.0f, 0.0f, .0f, 1.0f)),
			Diffuse(Float4(.0f, 0.f, 0.f, 1.0f)),
			Specular(Float4(0.0f, .0f, .0f, 1.0f)),
			Constant(1.0f),
			Linear(.0f),
			Quadratic(0.0f),
			Intensity(1.0f),
			Angle(PI),
			CosAngle(-1.0f),
			SinAngle(0.0f),
			Exponent(1.0f),
			PositionWS(APoint::ORIGIN),
			DVectorWS(-AVector::FORWARD),
			UVectorWS(AVector::UP),
			RVectorWS(AVector::RIGHT),

			PositionVS(APoint::ORIGIN),
			DVectorVS(-AVector::FORWARD),
			mType(etype)
		{
			
		}
		virtual ~Light() {}

		inline void SetType(Type type)
		{
			mType = type;
		}
		inline Type GetType()const
		{
			return mType;
		}
		Float4 Ambient;
		Float4 Diffuse;
		Float4 Specular;

		float Constant;
		float Linear;
		float Quadratic;
		float Intensity;

		float Angle;
		float CosAngle;
		float SinAngle;
		float Exponent;
		float Range;

		uint32_t m_Enable;

		uint32_t m_Selected;

		Vector2f m_Padding;
		void SetAngle(float angle)
		{
			Angle = angle;
			CosAngle = cosf(angle);
			SinAngle = sinf(angle);
		}
		
		//Position for point and spot lights(world)
		APoint PositionWS;

		//Direction for spot and directional light(world)
		AVector DVectorWS;
		AVector UVectorWS;
		AVector RVectorWS;

		//Position View Space
		APoint PositionVS;

		AVector DVectorVS;

	

		void SetDirection(const AVector& direction)
		{
			DVectorWS = direction;
			AVector::GenerateOrthonormalBasis(UVectorWS, RVectorWS, DVectorWS);
		}
	protected:
		Type mType;
	};
}