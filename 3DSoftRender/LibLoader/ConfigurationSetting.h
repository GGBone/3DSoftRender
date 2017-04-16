#pragma once
#include "GraphicsLib.h"
#include <Light.h>
#include "Test.h"
class Test3;
class Test4;
	enum class LightGeneration
	{
		Uniform,    // Lights are placed uniform distance from eachother.
		Random,     // Lights are randomly placed within the bounds.
	};
	
	class ConfigurationSettings
	{
	public:
		ConfigurationSettings();

		uint16_t    WindowWidth;
		uint16_t    WindowHeight;
		bool        FullScreen;

		std::string SceneFileName;
		float       SceneScaleFactor;

		Test3   CameraPosition;
		Test4   CameraRotation;
		float       CameraPivotDistance;

		// For different scenes, different camera speeds may be required.
		float       NormalCameraSpeed;
		float       FastCameraSpeed;

		// Light
		std::vector<Hikari::Light> Lights;

		// Light generation properties.
		LightGeneration LightGenerationMethod;
		Test3       LightsMinBounds;
		Test3       LightsMaxBounds;
		float           MinSpotAngle;
		float           MaxSpotAngle;
		float           MinRange;
		float           MaxRange;
		bool            GeneratePointLights;
		bool            GenerateSpotLights;
		bool            GenerateDirectionalLights;

		bool Load(const std::wstring& fileName);
		// Reload configuration settings from previously loaded file.
		bool Reload();
		bool Save(const std::wstring& fileName = L"");

	
		bool        UpgradeConfigFile;
	protected:

	private:
		//friend class boost::serialization::access;
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		std::wstring m_Filename;

	};
	template<class Archive>
	void ConfigurationSettings::serialize(Archive& ar, const unsigned int version)
	{
		UpgradeConfigFile = boost::serialization::version<ConfigurationSettings>::value != version;

		ar & BOOST_SERIALIZATION_NVP(WindowWidth);
		ar & BOOST_SERIALIZATION_NVP(WindowHeight);
		ar & BOOST_SERIALIZATION_NVP(FullScreen);
		ar & BOOST_SERIALIZATION_NVP(SceneFileName);
		ar & BOOST_SERIALIZATION_NVP(SceneScaleFactor);
		if (version > 0)
		{
			ar & BOOST_SERIALIZATION_NVP(CameraPosition);
			ar & BOOST_SERIALIZATION_NVP(CameraRotation);
		}
		if (version > 1)
		{
			ar & BOOST_SERIALIZATION_NVP(NormalCameraSpeed);
			ar & BOOST_SERIALIZATION_NVP(FastCameraSpeed);
		}
		if (version > 2)
		{
			ar & BOOST_SERIALIZATION_NVP(CameraPivotDistance);
		}
		if (version > 3)
		{
			ar & BOOST_SERIALIZATION_NVP(Lights);
		}
		if (version > 4)
		{
			// Light generation properties.
			ar & BOOST_SERIALIZATION_NVP(LightsMinBounds);
			ar & BOOST_SERIALIZATION_NVP(LightsMaxBounds);
			ar & BOOST_SERIALIZATION_NVP(MinSpotAngle);
			ar & BOOST_SERIALIZATION_NVP(MaxSpotAngle);
			ar & BOOST_SERIALIZATION_NVP(MinRange);
			ar & BOOST_SERIALIZATION_NVP(MaxRange);
			ar & BOOST_SERIALIZATION_NVP(GeneratePointLights);
			ar & BOOST_SERIALIZATION_NVP(GenerateSpotLights);
			ar & BOOST_SERIALIZATION_NVP(GenerateDirectionalLights);
		}
		if (version > 5)
		{
			ar & BOOST_SERIALIZATION_NVP(LightGenerationMethod);
		}
	}
	
	
	BOOST_CLASS_VERSION(ConfigurationSettings, 6);


	namespace boost
	{
		namespace serialization
		{
			template<class Archive>
			void serialize(Archive& ar, Test3& d,const unsigned int version)
			{
				float X, Y, Z;
				ar & BOOST_SERIALIZATION_NVP(X);
				ar & BOOST_SERIALIZATION_NVP(Y);
				ar & BOOST_SERIALIZATION_NVP(Z);
				d.X = X;
				d.Y = Y;
				d.Z = Z;
			}

			template<class Archive>
			void serialize(Archive& ar, Test4& d, const unsigned int version)
			{
				float X, Y, Z,W;
				ar & BOOST_SERIALIZATION_NVP(X);
				ar & BOOST_SERIALIZATION_NVP(Y);
				ar & BOOST_SERIALIZATION_NVP(Z);
				ar & BOOST_SERIALIZATION_NVP(W);
				d.X = X;
				d.Y = Y;
				d.Z = Z;
				d.W = W;
			}

			template<class Archive>
			void serialize(Archive& archive,Hikari::Light& light, const unsigned int version)
			{
				Test4 Position, Direction, Color;
				float SpotlightAngle, Range,
					Intensity, Enabled;
				Light::LightType Type;
				archive & BOOST_SERIALIZATION_NVP(Position);
				archive & BOOST_SERIALIZATION_NVP(Direction);
				archive & BOOST_SERIALIZATION_NVP(Color);
				archive & BOOST_SERIALIZATION_NVP(SpotlightAngle);
				archive & BOOST_SERIALIZATION_NVP(Range);
				archive & BOOST_SERIALIZATION_NVP(Intensity);
				archive & BOOST_SERIALIZATION_NVP(Enabled);
				archive & BOOST_SERIALIZATION_NVP(Type);

				light.m_PositionWS = Position;
				light.m_DirectionWS = Direction;
				light.m_Color = Color;
				light.m_Range = Range;
				light.m_Intensity = Intensity;
				light.m_Enabled = Enabled;
				light.m_Type = Type;
				light.m_SpotlightAngle = SpotlightAngle;
			}

		}
	};