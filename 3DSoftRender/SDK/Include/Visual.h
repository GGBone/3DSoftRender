#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Spatial.h"
namespace Hikari
{
	class VisualEffectInstance;
	class BufferBinding;
	class VertexFormat;
	class Buffer;
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
		Visual(PrimitiveType type,VertexFormat* vformat);
		
		virtual void SetVertexBuffer(Buffer* buffer);
		virtual void SetIndexBuffer(Buffer* buffer);

		inline const Buffer* GetIndexBuffer()const
		{
			return miBuffer;
		}
		inline Buffer* GetIndexBuffer()
		{
			return miBuffer;
		}

		inline const Buffer* GetVertexBuffer()const
		{
			return mvBuffer;
		}
		inline Buffer* GetVertexBuffer()
		{
			return mvBuffer;
		}

		inline const VertexFormat* GetVertexFormat()const
		{
			return mvFormat;
		}
		inline VertexFormat* Visual::GetVertexFormat()
		{
			return mvFormat;
		}
		inline const PrimitiveType GetPrimitiveType()const
		{
			return mType;
		}
		
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
		
		Buffer* mvBuffer;

		Buffer* miBuffer;

		VertexFormat* mvFormat;

		VisualEffectInstance* mEffect;
	};


}