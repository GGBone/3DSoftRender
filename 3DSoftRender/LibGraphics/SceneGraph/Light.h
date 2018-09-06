#pragma once
#include "Base/Float2.h"
#include "Base/Float4.h"

namespace Hikari
{
	class Light
	{
	public:
		enum class LightType : uint32_t
		{
			Point = 0,
			Spot = 1,
			Directional = 2
		};


		Float4 m_PositionWS;

		Float4 m_DirectionWS;

		Float4 m_PositionVS;

		Float4 m_DirectionVS;

		Float4 m_Color;

		float m_SpotlightAngle;

		float m_Range;

		float m_Intensity;


		uint32_t m_Enabled;

		uint32_t m_Selected;

		LightType m_Type;

		Float2 m_Padding;

		Light::Light()
			: m_PositionWS(0, 0, 0, 1)
			  , m_DirectionWS(0, 0, -1, 0)
			  , m_PositionVS(0, 0, 0, 1)
			  , m_DirectionVS(0, 0, 1, 0)
			  , m_Color(1, 1, 1, 1)
			  , m_SpotlightAngle(45.0f)
			  , m_Range(100.0f)
			  , m_Intensity(1.0f)
			  , m_Enabled(true)
			  , m_Selected(false)
			  , m_Type(LightType::Point)
		{
		}
	};
}
