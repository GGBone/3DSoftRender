#pragma once
#include "Object.h"
#include "Spatial.h"

namespace Hikari
{
	class VisualEffectInstance;
	struct BufferBinding;
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
		Visual(PrimitiveType type, VertexFormat* vformat);

		virtual void SetVertexBuffer(Buffer* buffer);
		virtual void SetIndexBuffer(Buffer* buffer);

		const Buffer* GetIndexBuffer() const
		{
			return miBuffer;
		}

		Buffer* GetIndexBuffer()
		{
			return miBuffer;
		}

		const Buffer* GetVertexBuffer() const
		{
			return mvBuffer;
		}

		Buffer* GetVertexBuffer()
		{
			return mvBuffer;
		}

		const VertexFormat* GetVertexFormat() const
		{
			return mvFormat;
		}

		VertexFormat* Visual::GetVertexFormat()
		{
			return mvFormat;
		}

		const PrimitiveType GetPrimitiveType() const
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

		void SetEffectInstance(VisualEffectInstance* Instance)
		{
			mEffect = Instance;
		}

	protected:
		void UpdateWorldBound() override;
		virtual void UpdateModelBound();
		void GetVisibleSet(Culler& culler, bool noCull) override;


	protected:
		PrimitiveType mType;

		Buffer* mvBuffer{};

		Buffer* miBuffer{};

		VertexFormat* mvFormat;

		VisualEffectInstance* mEffect;
	};
}
