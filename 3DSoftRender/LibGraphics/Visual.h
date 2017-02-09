#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "VertexBuffer.h"
#include "VisualPass.h"
#include "VertexFormat.h"
namespace Hikari
{
	class Visual : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		enum PrimitiveType
		{
			PT_NONE,
			PT_TRIANGLES,
			PT_TRIMESH
		};
		Visual(VertexBuffer* vBuffer, VisualPass* pass);
		inline const VertexBuffer* GetVertexBuffer()const;
		inline const VisualPass* GetVisualPass()const;
		inline const VertexFormat* GetVertexFormat()const;
		inline const PrimitiveType GetPrimitiveType()const;
	private:
		PrimitiveType mType;
		VertexBufferPtr mvBuffer;
		VisualPassPtr mPass;
		VertexFormat* vFormat;
	};
#include "Visual.inl"
}