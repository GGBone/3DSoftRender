#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "VertexBuffer.h"
#include "VisualPass.h"
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
		Visual(VertexBuffer* vBuffer,VisualPass* pass);
		const VertexBuffer* GetVertexBuffer()const;
		const VisualPass* GetVisualPass()const;
	private:
		PrimitiveType mType;
		VertexBufferPtr mvBuffer;
		VisualPassPtr mPass;
	};
}
