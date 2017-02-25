#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexFormat.h"
#include "Spatial.h"
namespace Hikari
{
	class Visual : public Spatial
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
		Visual(VertexBuffer* vBuffer,IndexBuffer* iBuffer);
		inline const VertexBuffer* GetVertexBuffer()const;
		inline const IndexBuffer* GetIndexBuffer()const;
		inline const VertexFormat* GetVertexFormat()const;
		inline const PrimitiveType GetPrimitiveType()const;
	protected:
		virtual void UpdateWorldBound();

	private:
		PrimitiveType mType;
		VertexBufferPtr mvBuffer;
		IndexBuffer* miBuffer;
		VertexFormat* mvFormat;
	};
#include "Visual.inl"
}