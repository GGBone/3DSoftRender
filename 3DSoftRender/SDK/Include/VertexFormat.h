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
			AU_QUANTITY
		};
		VertexFormat();
		virtual ~VertexFormat();

		void SetAttribute(AttributeType, AttributeUsage);
		static VertexFormat* Create(AttributeType at, AttributeUsage au);
	private:
		AttributeType Type;
		AttributeUsage Usage;
	};
}