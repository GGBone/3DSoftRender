#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Float4.h"
#include "Float2.h"

#include "Texture.h"

namespace Hikari
{
	class Material : public Object
	{
		DECLARE_NAMES;
		DECLARE_RTTI;

	public:
		enum TextureType
		{
			Ambient = 0,
			Emissive,
			Diffuse,
			Specular,
			SpecularPower,
			Normal,
			Bump,
			Opacity
		};

		Material();
		virtual ~Material();

		void SetTexture(TextureType ID, Texture& texture);

		_declspec(align(16)) struct MaterialProperties
		{
			Float4 GlobalAmbient;

			Float4 Emissive;
			Float4 Ambient;
			Float4 Diffuse;
			Float4 Specular;
			Float4 Reflectance;

			float Opacity;
			float SpecularPower;

			//Transparent
			float IndexOfRefraction;
			uint32_t HasAmbientTexture;

			uint32_t HasEmissiveTexture;
			uint32_t HasDiffuseTexture;
			uint32_t HasSpecularTexture;
			uint32_t HasSpecularPowerTexture;

			uint32_t HasNormalTexture;
			uint32_t HasBumpTexture;
			uint32_t HasOpacityTexture;
			uint32_t BumpIntensity;

			float SpecularScale;
			float AlphaThreshold;

			Float2 m_Padding;
		};
	
		MaterialProperties* Properties;

	};
}