#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Test.h"
#include "APoint.h"
#include "Float2.h"
#include "AVector.h"
namespace Hikari
{
	class Light : public Object
	{
	public:
		enum class LightType : uint32_t
		{
			Point = 0,
			Spot = 1,
			Directional = 2
		};

		/**
		* Position for point and spot lights (World space).
		*/
		Test4   m_PositionWS;
		//--------------------------------------------------------------( 16 bytes )
		/**
		* Direction for spot and directional lights (World space).
		*/
		Test4   m_DirectionWS;
		//--------------------------------------------------------------( 16 bytes )
		/**
		* Position for point and spot lights (View space).
		*/
		Test4   m_PositionVS;
		//--------------------------------------------------------------( 16 bytes )
		/**
		* Direction for spot and directional lights (View space).
		*/
		Test4   m_DirectionVS;
		//--------------------------------------------------------------( 16 bytes )
		/**
		* Color of the light. Diffuse and specular colors are not separated.
		*/
		Test4   m_Color;
		//--------------------------------------------------------------( 16 bytes )
		/**
		* The half angle of the spotlight cone.
		*/
		float       m_SpotlightAngle;
		/**
		* The range of the light.
		*/
		float       m_Range;

		/**
		* The intensity of the light.
		*/
		float       m_Intensity;

		/**
		* Disable or enable the light.
		*/
		uint32_t    m_Enabled;
		//--------------------------------------------------------------(16 bytes )

		/**
		* True if the light is selected in the editor.
		*/
		uint32_t    m_Selected;
		/**
		* The type of the light.
		*/
		LightType   m_Type;

		Float2   m_Padding;
		//--------------------------------------------------------------(16 bytes )
		//--------------------------------------------------------------( 16 * 7 = 112 bytes )
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
		{}
	};
}