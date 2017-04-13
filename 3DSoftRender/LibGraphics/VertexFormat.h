#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "SoftRendererLIB.h"

namespace Hikari
{
	class VertexFormat :public Object
	{
		DECLARE_RTTI;

		DECLARE_NAMES;
	public:
		enum
		{
			AM_MAX_ATTRIBUTES = 16,
			AM_MAX_TOORD_UNITS = 8,
			AM_MAX_COLOR_UNITS = 2
		};
		enum AttributeType
		{
			AT_NONE,
			AT_FLOAT1,
			AT_FLOAT2,
			AT_FLOAT3,
			AT_FLOAT4,
			AT_QUANTITY
		};
		enum AttributeUsage
		{
			AU_NONE,
			AU_POSITION,
			AU_NORMAL,
			AU_TANGENT,
			AU_BINORMAL,
			AU_TEXCOORD,
			AU_COLOR,
			AU_QUANTITY
		};
		VertexFormat(int numAttributes);
		virtual ~VertexFormat();

		static VertexFormat* Create(int numAttributes, ...);

		void SetAttribute(int attribute,unsigned int streamIndex,unsigned int offset,AttributeType, AttributeUsage,unsigned int usageIndex);
		
		void SetStride(int stride);
		
		inline int GetNumAttributes()const;
		inline unsigned int GetStreamIndex(int attribute);
		inline unsigned int GetOffset(int attribute) const;
		inline AttributeType GetAttributeType(int attribute) const;
		inline AttributeUsage GetAttributeUsage(int attribute)const;
		inline unsigned int GetUsageIndex(int attribute)const;

		void GetAttribute(int attribute, unsigned int& streamIndex,
			unsigned int& offset, AttributeType& type, AttributeUsage& usage,
			unsigned int& usageIndex) const;

		inline int GetStride()const;
		int GetIndex(AttributeUsage usage, unsigned int usageIndex = 0)const;
		
		inline static int GetComponentSize(AttributeType type);
		inline static int GetNumComponents(AttributeType type);
		inline static int GetTypeSize(AttributeType type);

	protected:
		class Element
		{
		public:
			unsigned int StreamIndex;
			unsigned int Offset;
			AttributeType Type;
			AttributeUsage Usage;
			unsigned int UsageIndex;
		};
		int mNumAttributes;
		Element mElements[AM_MAX_ATTRIBUTES];
		int mStride;

		static int msComponent[AT_QUANTITY];
		static int msNumComponents[AT_QUANTITY];
		static int msTypeSize[AT_QUANTITY];
	};
	typedef VertexFormat* VertexFormatPtr;

	inline int Hikari::VertexFormat::GetNumAttributes() const
	{
		return mNumAttributes;
	}

	inline unsigned int Hikari::VertexFormat::GetStreamIndex(int attribute)
	{
		return mElements[attribute].StreamIndex;
	}

	inline unsigned int Hikari::VertexFormat::GetOffset(int attribute) const
	{
		return mElements[attribute].Offset;
	}

	inline VertexFormat::AttributeType Hikari::VertexFormat::GetAttributeType(int attribute) const
	{
		return mElements[attribute].Type;
	}

	inline VertexFormat::AttributeUsage Hikari::VertexFormat::GetAttributeUsage(int attribute) const
	{
		return mElements[attribute].Usage;
	}

	inline unsigned int Hikari::VertexFormat::GetUsageIndex(int attribute) const
	{
		return mElements[attribute].UsageIndex;
	}


	inline int Hikari::VertexFormat::GetComponentSize(AttributeType type)
	{
		return msComponent[type];
	}

	inline int Hikari::VertexFormat::GetNumComponents(AttributeType type)
	{
		return msNumComponents[type];
	}

	inline int Hikari::VertexFormat::GetTypeSize(AttributeType type)
	{
		return msTypeSize[type];
	}


	inline int Hikari::VertexFormat::GetStride() const
	{
		return mStride;
	}
}