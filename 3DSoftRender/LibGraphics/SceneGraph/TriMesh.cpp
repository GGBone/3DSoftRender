#include "GraphicsPCH.h"
#include "TriMesh.h"
using namespace Hikari;

IMPLEMENT_DEFAULT_NAMES(Triangles, TriMesh);
IMPLEMENT_RTTI(Hikari,Triangles, TriMesh);

TriMesh::TriMesh()
	: Triangles(PT_TRIMESH)
{
}

TriMesh::TriMesh(VertexFormat* vformat, VertexBuffer* vbuffer, IndexBuffer* ibuffer)
	:
	Triangles(PT_TRIMESH, vformat, vbuffer, ibuffer)
{
}

TriMesh::~TriMesh()
= default;

int TriMesh::GetNumTriangles() const
{
	return miBuffer->GetNumElements() / 3;
}

bool TriMesh::GetTriangle(int i, int& v0, int& v1, int& v2) const
{
	if (0 <= i && i < GetNumTriangles())
	{
		int* indices = 3 * i + (int*)miBuffer->GetData();
		v0 = *indices++;
		v1 = *indices++;
		v2 = *indices++;
	}
	return false;
}
