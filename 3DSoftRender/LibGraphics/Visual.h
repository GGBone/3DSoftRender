#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexFormat.h"
#include "Spatial.h"
#include "VisualEffectInstance.h"
#include "Culler.h"
namespace Hikari
{
	class VisualEffectInstance;
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
		Visual(PrimitiveType type = PT_NONE);
		Visual(PrimitiveType type,VertexFormat* vformat,VertexBuffer* vBuffer,IndexBuffer* iBuffer);
		inline const VertexBuffer* GetVertexBuffer()const;
		inline VertexBuffer* GetVertexBuffer()
		{
			return mvBuffer;
		}
		inline const IndexBuffer* GetIndexBuffer()const;
		inline IndexBuffer* GetIndexBuffer()
		{
			return miBuffer;
		}
		inline const VertexFormat* GetVertexFormat()const;
		inline VertexFormat* Visual::GetVertexFormat()
		{
			return mvFormat;
		}
		inline const PrimitiveType GetPrimitiveType()const;
		
		enum UpdateType
		{
			GU_MODEL_BOUND_ONLY = -3,
			GU_NORMALS = -2,
			GU_USE_GEOMETRY = -1,
			GU_USE_TCOORD_CHANNEL = 0
		};
		virtual void UpdateModelSpace(UpdateType type);
		inline void SetEffectInstance(VisualEffectInstance* Instance)
		{
			mEffect = Instance;
		}
	protected:
		virtual void UpdateWorldBound();
		virtual void UpdateModelBound();
		virtual void GetVisibleSet(Culler& culler, bool noCull);

		
	protected:
		PrimitiveType mType;
		VertexBufferPtr mvBuffer;
		IndexBuffer* miBuffer;
		VertexFormat* mvFormat;

		VisualEffectInstance* mEffect;
	};
#include "Visual.inl"
}