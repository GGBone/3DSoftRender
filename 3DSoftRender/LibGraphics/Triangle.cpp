#include "GraphicsPCH.h"
#include "Triangle.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Visual, Triangles);
IMPLEMENT_RTTI(Hikari, Visual, Triangles);
Hikari::Triangles::Triangles(PrimitiveType type)
	:Visual(type)
{
}

Hikari::Triangles::Triangles(PrimitiveType type, VertexFormat * vformat, VertexBuffer * vbuffer, IndexBuffer * ibuffer)
	:Visual(type,vformat, vbuffer,ibuffer)
{

}

Hikari::Triangles::~Triangles()
{
}

bool Hikari::Triangles::GetModelTriangle(int i, APoint * modelTrangle) const
{
	int v0, v1, v2;
	VertexBufferAccessor vba(mvFormat, mvBuffer);
	if (GetTriangle(i, v0, v1, v2))
	{
		modelTrangle[0] = vba.Position<Float3>(v0);
		modelTrangle[1] = vba.Position<Float3>(v1);
		modelTrangle[2] = vba.Position<Float3>(v2);
		return true;
	}
	

	return false;
}

bool Hikari::Triangles::GetWorldTrangle(int i, APoint * worldTrangle) const
{
	APoint modelTriangle[3];
	if (GetModelTriangle(i, modelTriangle))
	{
		worldTrangle[0] = worldTransform * modelTriangle[0];
		worldTrangle[1] = worldTransform * modelTriangle[1];
		worldTrangle[2] = worldTransform * modelTriangle[2];
		return true;
	}
	return false;
}

inline int Hikari::Triangles::GetNumVertices() const
{
	return mvBuffer->GetNumElements();
}
//
//inline const Transform & Hikari::Triangles::GetWorldTransform() const
//{
//	// TODO: 在此处插入 return 语句
//	 
//}

Float3 Hikari::Triangles::GetPoistion(int v) const
{
	int index = mvFormat->GetIndex(VertexFormat::AU_POSITION);
	if (index >= 0)
	{
		char* position = (char*)mvBuffer->GetData() + mvFormat->GetOffset(index);
		int stride = mvFormat->GetStride();
		return *(Float3*)(position + v * stride);
	}
	return Float3(0.0f,0.0f,0.0f);
}

void Hikari::Triangles::UpdateModelSpace(UpdateType type)
{
	VertexBufferAccessor vba(this);
	if (vba.HasNormal())
		UpdateModelNormals(vba);

}

void Hikari::Triangles::UpdateModelNormals(VertexBufferAccessor & vba)
{
	const int numVertices = vba.GetNumVertices();
	int i;
	for (int i = 0; i < numVertices; ++i)
	{
		int v0, v1, v2;
		if (!GetTriangle(i, v0, v1, v2))
			continue;
		APoint pos0 = vba.Position<Float3>(v0);
		APoint pos1 = vba.Position<Float3>(v1);
		APoint pos2 = vba.Position<Float3>(v2);

		AVector triEdge1 = pos1 - pos0;
		AVector triEdge2 = pos2 - pos0;
		AVector triNormal = triEdge1.Cross(triEdge2);

		vba.Normal<AVector>(v0) += triNormal;
		vba.Normal<AVector>(v1) += triNormal;
		vba.Normal<AVector>(v2) += triNormal;
	}
	for (int i = 0; i < numVertices; ++i)
	{
		vba.Normal<AVector>(i).Normalize();
	}
}

void Hikari::Triangles::UpdateModelTangentsUseGeometry(VertexBufferAccessor & vba)
{
}

AVector Hikari::Triangles::ComputeTangent(const APoint & position0, const Float2 & tcoord0, const APoint & position1, const Float2 & tcoord1, const APoint & position2, const Float2 & tcoord2)
{
	return AVector();
}
