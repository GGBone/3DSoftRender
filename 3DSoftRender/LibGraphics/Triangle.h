#pragma once
#include "Graphics\GraphicsLib.h"
#include "Visual.h"
#include "Math\Base\Float2.h"
#include "Math\Algebra\APoint.h"
#include "VertexBufferAccessor.h"
#include "Math\Algebra\Vector2.h"
namespace Hikari
{
	class Triangles : public Visual
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	protected:
		Triangles(PrimitiveType type = PT_TRIANGLES);
		Triangles(PrimitiveType type, VertexFormat* vformat);

	public:
		~Triangles();
		virtual int GetNumTriangles()const = 0;
		virtual bool GetTriangle(int i, int& v0, int& v1, int& v2)const = 0;
		bool GetModelTriangle(int i, APoint* modelTrangle)const;
		bool GetWorldTrangle(int i, APoint* worldTrangle)const;

		inline int GetNumVertices()const;
		inline const Transform& GetWorldTransform()const;
		Float3 GetPoistion(int v)const;
		
		virtual void UpdateModelSpace(UpdateType type);

	private:
		void UpdateModelNormals(VertexBufferAccessor& vba);
		void UpdateModelTangentsUseGeometry(VertexBufferAccessor& vba);

		static AVector ComputeTangent(const APoint& position0, const Float2& tcoord0,
			const APoint& position1, const Float2& tcoord1,
			const APoint& position2, const Float2& tcoord2);
	};
	typedef Triangles* TrianglesPtr;
}