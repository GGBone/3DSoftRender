#pragma once
#include "Core.h"
#include "SceneGraph/Light.h"
#include "Base/Float3.h"
#include "Algebra/Apoint.h"
#include "Algebra/AVector.h"
enum class LightGeneration
{
	Uniform,
	// Lights are placed uniform distance from eachother.
	Random,
	// Lights are randomly placed within the bounds.
};

class ConfigurationSettings
{
public:
	ConfigurationSettings();

	uint16_t WindowWidth;
	uint16_t WindowHeight;
	bool FullScreen;

	std::string SceneFileName;
	float SceneScaleFactor;

	Hikari::APoint CameraPosition;
	Hikari::AVector CameraRotation;
	float CameraPivotDistance;

	// For different scenes, different camera speeds may be required.
	float NormalCameraSpeed;
	float FastCameraSpeed;

	// Light
	std::vector<Hikari::Light> Lights;

	// Light generation properties.
	LightGeneration LightGenerationMethod;
	Hikari::Float3 LightsMinBounds;
	Hikari::Float3 LightsMaxBounds;
	//Spot Light
	float MinSpotAngle;
	float MaxSpotAngle;
	float MinRange;
	float MaxRange;
	bool GeneratePointLights;
	bool GenerateSpotLights;
	bool GenerateDirectionalLights;

	bool Load(const std::wstring& fileName);
	// Reload configuration settings from previously loaded file.
	bool Reload();
	bool Save(const std::wstring& fileName = L"");


	bool UpgradeConfigFile;
protected:

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, unsigned int version);

	std::wstring m_Filename;
};

template <class Archive>
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
