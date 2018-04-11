#pragma once

namespace boost
{
	namespace serialization
	{
		template<class Archive>
		void serialize(Archive& ar, Hikari::Float3& d, const unsigned int version)
		{
			/*float X, Y, Z;
			ar & BOOST_SERIALIZATION_NVP(X);
			ar & BOOST_SERIALIZATION_NVP(Y);
			ar & BOOST_SERIALIZATION_NVP(Z);
			d.X = X;
			d.Y = Y;
			d.Z = Z;*/
			ar & make_nvp("X", d[0]);
			ar & make_nvp("Y", d[1]);
			ar & make_nvp("Z", d[2]);

		}
		template<class Archive>
		void serialize(Archive& ar, Hikari::Float4& d, const unsigned int version)
		{
			ar & make_nvp("X", d[0]);
			ar & make_nvp("Y", d[1]);
			ar & make_nvp("Z", d[2]);
			ar & make_nvp("W", d[3]);
		}
		template<class Archive>
		void serialize(Archive& ar, Hikari::APoint& d, const unsigned int version)
		{

			ar & make_nvp("X", d[0]);
			ar & make_nvp("Y", d[1]);
			ar & make_nvp("Z", d[2]);
		}

		template<class Archive>
		void serialize(Archive& ar, Hikari::AVector& d, const unsigned int version)
		{
			ar & make_nvp("X", d[0]);
			ar & make_nvp("Y", d[1]);
			ar & make_nvp("Z", d[2]);
			ar & make_nvp("W", d[3]);

		}
		template<class Archive>
		void serialize(Archive& ar, Hikari::Light& light, const unsigned int version)
		{
			ar & make_nvp("Position", light.m_PositionWS);
			ar & make_nvp("Direction", light.m_DirectionWS);
			ar & make_nvp("Color", light.m_Color);
			ar & make_nvp("SpotlightAngle", light.m_SpotlightAngle);
			ar & make_nvp("Range", light.m_Range);
			if (version > 0)
			{
				ar & make_nvp("Intensity", light.m_Intensity);
				ar & make_nvp("Enabled", light.m_Enabled);
			}
			ar & make_nvp("Type", light.m_Type);
		}

	}
};